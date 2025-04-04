# README

## Build and Run Instructions

`cmake -S . -B build`  
`cmake --build build`  
`./build/src/src`

### Configure build type:

`cmake -DCMAKE_BUILD_TYPE=Release -S . -B build`  
`cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build`

### Build in parallel:
`cmake --build build -j`  
