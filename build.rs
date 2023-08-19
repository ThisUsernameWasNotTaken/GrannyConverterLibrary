use std::fs;
use cmake;
fn main() {
    // cmake::Config::
    let dst = cmake::build("out");

    // let mut build = cc::Build::new();
    // add_directory(&mut build, "src");
    // add_directory(&mut build, "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.1/include");
    // add_directory(&mut build, "external/devilsdk/include");
    // build
    //     .std("c++17")
    //     // .cpp(true)
    //     // .static_crt(true)
    //
    //     // +verbatim means that rustc itself won't add any target-specified library prefixes or suffixes (like lib or .a) to the library name,
    //     // and will try its best to ask for the same thing from the linker.
    //     // .link_lib_modifier("+verbatim")
    //     .compile("granny2converter");
    //
    // // println!("cargo:rerun-if-changed={}/src/main.cpp", source_folder.to_owned());
    // // println!("cargo:rustc-link-search={}", "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.1/lib/vs2019/x86");
    // println!("cargo:rustc-link-search={}", "lib");
    // // println!("cargo:rustc-link-lib={}", "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.1/lib/vs2019/x86/debug/libfbxsdk.lib");
}
fn add_directory(build: &mut cc::Build, dir: &str) {
    for line in fs::read_dir(dir).unwrap() {
        let path = line.unwrap().path();
        if path.is_file() {
            if path.ends_with(".h") {
                build.include(path.to_owned());
            }
            if path.ends_with(".cpp") {
                build.file(path.to_owned());
            }
        } else if path.is_dir() {
            add_directory(build, path.to_str().unwrap());
        }
    }
}