set -e

rm -rf build
mkdir -p build
pushd build
cmake .. -DSOURCE_PATH=../src/main.cpp -DCMAKE_BUILD_TYPE=Release
cmake --build .
popd
build/ps.cpp < test/in