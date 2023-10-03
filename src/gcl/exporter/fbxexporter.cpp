#include "gcl/exporter/fbxexporter.h"

#include "gcl/utilities/fbxsdkcommon.h"

namespace GCL::Exporter {

	using namespace GCL::Utilities;

	FbxExporter::FbxExporter(Scene::SharedPtr scene)
		: m_scene(scene)
	{
		initialize();
	}

	FbxExporter::FbxExporter(FbxExportOptions options, Scene::SharedPtr scene)
		: m_options(options)
		, m_scene(scene)
	{
		initialize();
	}

	FbxExporter::FbxExporter(ExporterModuleFactoryInterface* exportModuleFactory, FbxExportOptions options, Scene::SharedPtr scene)
		: m_options(options)
		, m_scene(scene)
	{
		m_exporterModuleFactory = exportModuleFactory;
		initialize();
	}

	FbxExporter::~FbxExporter()
	{
		FbxSdkCommon::DestroySdkObjects(m_fbxManager);

		if (m_exporterModuleFactory) {
			delete m_exporterModuleFactory;
		}

		delete m_exporterMaterial;
		delete m_exporterSkeleton;
		delete m_exporterAnimation;
	}

	void FbxExporter::initialize()
	{
		// Initialize the fbx sdk.
		FbxSdkCommon::InitializeSdkObjects(m_fbxManager, m_fbxScene);

		// Convert the axis coordinate system.
		FbxAxisSystem axisSystem;
		FbxAxisSystem::ParseAxisSystem(m_options.convertAxis.c_str(), axisSystem);
		axisSystem.ConvertScene(m_fbxScene);

		if (!m_exporterModuleFactory) {
			m_exporterModuleFactory = new FbxExporterModuleFactory();
		}

		m_exporterMaterial = m_exporterModuleFactory->createExporterModuleMaterial(m_scene, m_fbxScene);
		m_exporterMesh = m_exporterModuleFactory->createExporterModuleMesh(m_scene, m_fbxScene);
		m_exporterSkeleton = m_exporterModuleFactory->createExporterModuleSkeleton(m_scene, m_fbxScene);
		m_exporterAnimation = m_exporterModuleFactory->createExporterModuleAnimation(m_scene, m_fbxScene);
	}

	void FbxExporter::exportToFile(string outputFilepath)
	{
		exportModels(outputFilepath);

		FbxSdkCommon::SaveScene(m_fbxManager, m_fbxScene, outputFilepath.c_str(), false, false);
	}

	void FbxExporter::exportModels(string outputFilepath)
	{
		if (m_options.exportMaterials) {
			m_exporterMaterial->exportMaterials(outputFilepath);
		}

		vector<GCL::Bindings::Model::SharedPtr> modelListThatHaveNodes;
		vector<size_t> modelListIndexFoundBone;
		vector<GCL::Bindings::Model::SharedPtr> modelList = m_scene->getModels();
		for (size_t i = 0; i < modelList.size(); i++)
		{
			auto modelCurrent = modelList.at(i);
			auto modelCurrentBones = modelCurrent->getBones();
			try
			{
				// Export skeleton if enabled.
				if (m_options.exportSkeleton && modelCurrentBones.size() > 0) {
					FbxNode* exist = m_fbxScene->GetRootNode()->FindChild(modelCurrentBones[0]->getData().Name);
					////////// HIER WERDEN DIE BONES ZU NODES ZUGEORDNET ///////////
					if (!exist)
					{
						/// wenn noch keine childs in der export fbx-scene mit dem namen unseres bone childs zu finden sind, exportieren wir es erstmalig.
						m_exporterSkeleton->exportBones(modelCurrent);
					}
					else
					{
						/// ansonsten: wenn doch schon ein gleichnamiges child vorhanden ist, werden alle bones aller anderen models in das aktuelle model überschreiben
						for (auto otherModel : m_scene->getModels()) {
							if (otherModel != modelCurrent && otherModel->getBones()[0]->getNode() == exist) {
								modelCurrent->setBones(otherModel->getBones());
							}
						}
					}
				}

				if (modelCurrent->isExcluded()) {
					continue;
				}

				if (m_options.exportMeshes) {
					m_exporterMesh->exportMeshes(modelCurrent, m_options.exportSkeleton);
				}

				for (size_t ii = 0; ii < modelCurrentBones.size(); ii++)
				{
					fbxsdk::FbxNode* modelBoneNode = modelCurrentBones.at(ii)->getNode();
					if (modelBoneNode != nullptr)
					{
						modelListThatHaveNodes.push_back(modelCurrent);
						modelListIndexFoundBone.push_back(ii);
					}
				}

				if (m_options.exportSkeleton && modelCurrentBones.size() > 1) {
					m_exporterSkeleton->exportPoses(modelCurrent);
				}
			}
			catch (const std::exception&)
			{

			}
		}

		if (m_options.exportAnimation) {
			m_exporterAnimation->exportAnimations();
		}
	}

} // namespace GCL::Exporter
