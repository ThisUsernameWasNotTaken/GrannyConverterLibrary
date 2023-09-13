#include "gcl/exporter/fbxexporter.h"
#include "gcl/exporter/fbxexportoptions.h"
#include "gcl/grannyconverterlibrary.h"
#include "gcl/importer/grannyimporter.h"
#include "gcl/importer/grannyimportoptions.h"
#include "gcl/utilities/logging.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#include <direct.h>
#define GetCurrentDir _getcwd

int main()
{
	char cCurrentPath[FILENAME_MAX];

	auto x = GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
	GCL::Utilities::Logging::info("%s", x);
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
	importer.importFromFile("i_kleintempel01-01_col.GR2");
	//    importer.importFromFile("character_animation.gr2");

	GCL::Exporter::FbxExportOptions exporterOptions;

	// Export all skeletons.
	exporterOptions.exportSkeleton = true;

	// Export all materials and textures.
	exporterOptions.exportMaterials = false;

	// Export animations.
	exporterOptions.exportAnimation = false;

	// Create exporter instance with the scene to be exported.
	GCL::Exporter::FbxExporter exporter(exporterOptions, importer.getScene());

	// Export the fbx scene to a fbx file.
	exporter.exportToFile("character_with_animation.fbx");

	return 0;
}
