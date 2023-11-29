del out -Recurse -Force
mkdir out
cmake -S . -B out
cmake --build out