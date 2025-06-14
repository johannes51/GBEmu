rm -rf build/
mkdir build
cd build

mkdir Debug
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
cd ..

mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ../..
cd ..

mkdir RelWithDebInfo
cd RelWithDebInfo
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ../..
cd ..

mkdir Sanitizer
cd Sanitizer
cmake -DCMAKE_BUILD_TYPE=Sanitizer ../..
cd ..

mkdir Coverage
cd Coverage
cmake -DCMAKE_BUILD_TYPE=Coverage ../..

