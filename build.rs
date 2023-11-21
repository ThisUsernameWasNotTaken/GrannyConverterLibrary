fn main() {
    let source_files =
        "/src/gcl/bindings/bonebinding.cpp
/src/gcl/bindings/animation.cpp
/src/gcl/bindings/abstractcurvekey.cpp
/src/gcl/bindings/skeleton.cpp
/src/gcl/bindings/model.cpp
/src/gcl/bindings/mesh.cpp
/src/gcl/bindings/bone.cpp
/src/gcl/bindings/curvescalekey.cpp
/src/gcl/bindings/curvepositionkey.cpp
/src/gcl/bindings/track.cpp
/src/gcl/bindings/scene.cpp
/src/gcl/bindings/material.cpp
/src/gcl/exporter/fbxexporter.cpp
/src/gcl/bindings/curverotationkey.cpp
/src/gcl/importer/grannyformat.cpp
/src/gcl/importer/grannyimportermaterial.cpp
/src/gcl/exporter/fbxexporteranimation.cpp
/src/gcl/importer/deboor.cpp
/src/gcl/exporter/fbxexporterskeleton.cpp
/src/gcl/exporter/fbxexportermodulefactory.cpp
/src/gcl/grannyconverterlibrary.cpp
/src/gcl/exporter/fbxexportermodule.cpp
/src/gcl/importer/grannyimporteranimation.cpp
/src/gcl/exporter/fbxexportermesh.cpp
/src/gcl/importer/grannyimporteranimation_deboor.cpp
/src/gcl/importer/grannyimporter.cpp
/src/gcl/exporter/fbxexportermaterial.cpp
/src/gcl/utilities/materialutility.cpp
/src/gcl/utilities/devilimageutility.cpp
/src/gcl/importer/grannyimportermodel.cpp
/src/gcl/utilities/filestreamutility.cpp
/src/gcl/utilities/stringutility.cpp
/src/gcl/utilities/datetime.cpp
/src/gcl/utilities/logging.cpp
/src/gcl/utilities/textureutility.cpp
/src/gcl/importer/grannyimporterskeleton.cpp
/src/gcl/utilities/fbxsdkcommon.cpp";

    let mut build = cc::Build::new();
    let source_folder = ".";// use a relative path  // "E:\\root\\Dateien\\Sacred\\GrannyConverterLibrary";
    // for line in source_files.lines() {
    //     build.file(source_folder.to_owned() + line);
    // }
    build
        // .file(source_folder.to_owned() + "/src/main.h")
        .file(source_folder.to_owned() + "/src/main.cpp")
        // .include("C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.1/include")
        // .include(source_folder.to_owned() + "/external/devilsdk/include")
        // .include(source_folder.to_owned() + "/out/build/x86-Debug")
        // .include(source_folder)
        // .include(source_folder.to_owned() + "/src")
        // .include(source_folder.to_owned() + "/bindings")
        // .include(source_folder.to_owned() + "/exporter")
        // .include(source_folder.to_owned() + "/importer")
        // .include(source_folder.to_owned() + "/utilities")

        .std("c++17")
        // .cpp(true)
        // .static_crt(true)

        // +verbatim means that rustc itself won't add any target-specified library prefixes or suffixes (like lib or .a) to the library name,
        // and will try its best to ask for the same thing from the linker.
        // .link_lib_modifier("+verbatim")
        .compile("granny2converter");

    println!("cargo:rerun-if-changed={}/src/main.cpp", source_folder.to_owned());
    // println!("cargo:rustc-link-search=lib");
    // println!("cargo:rustc-link-lib=/lib/libfbxsdk.dll");
}
