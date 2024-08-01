mkdir -p bin;
mkdir -p build;
mkdir -p logs/access;
mkdir -p logs/info;
mkdir -p logs/trace;
mkdir -p public;

cmake -B build -DCMAKE_CXX_FLAGS="-std=c++17" -DCMAKE_CXX_STANDARD=17 -DCMAKE_BUILD_TYPE=Debug;
cmake --build build --config Debug;
