#include "gcl/exporter/fbxexporter.h"
#include "gcl/exporter/fbxexportoptions.h"
#include "gcl/grannyconverterlibrary.h"
#include "gcl/importer/grannyimporter.h"
#include "gcl/importer/grannyimportoptions.h"
#include "gcl/utilities/logging.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#include <string>
#include <iostream>
#include <filesystem>
#include <direct.h>
#include "main.h"
#define GetCurrentDir _getcwd

bool has_suffix(const std::string& str, const std::string& suffix)
{
	bool x = str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
	return x;
}

int main()
{
	char cCurrentPath[FILENAME_MAX];

	auto folderPath = GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
	GCL::Utilities::Logging::info("%s", folderPath);

	for (const auto& entry : filesystem::directory_iterator(folderPath))
	{
		auto filePath = entry.path().string();
		if (has_suffix(filePath, ".gr2") || has_suffix(filePath, ".GR2"))
			extractFBX(filePath);
	}
	return 0;
}


int extractFBX(std::string& filename)
{
	// Initialize library.
	GCL::GrannyConverterLibrary grannyConverterLibrary;

	GCL::Importer::GrannyImportOptions options;

	// Use deboor animation importer.
	// The importer is able to import animations with bones are being mis-positioned.
	// However the resulted animation is might be changed in comparison to its original.
	// options.importAnimationDeboor = true;

	// Initialize importer.
	GCL::Importer::GrannyImporter importer(options);

	// Load a character and a animation.
	importer.importFromFile(filename.c_str());
	// todo test if this is indeed what it looks like:
	//    importer.importFromFile("character_animation.gr2"); 
	// // if i can import multiple .gr2 file "on top of each other" like layers and then export all into one .fbx then the animations would be solved.
	// (although i still dont know how converting back to .gr2 will play out...)

	GCL::Exporter::FbxExportOptions exporterOptions;

	// Export all skeletons.
	exporterOptions.exportSkeleton = true;

	// Export all materials and textures.
	exporterOptions.exportMaterials = false;

	// Export animations.
	exporterOptions.exportAnimation = true;

	// Create exporter instance with the scene to be exported.
	GCL::Exporter::FbxExporter exporter(exporterOptions, importer.getScene());

	// Export the fbx scene to a fbx file.
	exporter.exportToFile(filename + ".fbx");

	return 0;
}
