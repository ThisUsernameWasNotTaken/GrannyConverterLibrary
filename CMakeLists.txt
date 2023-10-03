cmake_minimum_required(VERSION 3.14)

project(GrannyConverterLibrary LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE GrannyConverterLibrarySources
    "src/*.cpp"
    "src/*.h"
)

include(FetchContent)
FetchContent_Declare(
    Corrosion
    GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
    GIT_TAG v0.4 # Optionally specify a commit hash, version tag or branch here
)
# Set any global configuration variables such as `Rust_TOOLCHAIN` before this line!
FetchContent_MakeAvailable(Corrosion)
# Import targets defined in a package or workspace manifest `Cargo.toml` file
corrosion_import_crate(MANIFEST_PATH ../RustReadZips/Cargo.toml)
#corrosion_link_libraries(_cargo-build_ ConverterExample)
corrosion_link_libraries(sacred-zipyip ConverterExample)

add_library(GrannyConverterLibrary STATIC
  ${GrannyConverterLibrarySources}
)

target_include_directories(GrannyConverterLibrary PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(GrannyConverterLibrary PRIVATE advapi32 shell32 user32 Kernel32 Ole32)
target_compile_definitions(GrannyConverterLibrary PRIVATE GRANNYCONVERTERLIBRARY_LIBRARY)

# DevIL SDK and FBX SDK
include("${PROJECT_SOURCE_DIR}/cmake/devilsdk.cmake")
include("${PROJECT_SOURCE_DIR}/cmake/fbxsdk.cmake")
include("${PROJECT_SOURCE_DIR}/cmake/mycustomadditions.cmake")

# Add examples.
add_subdirectory(examples/converter)