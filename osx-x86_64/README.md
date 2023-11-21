
```sh
# 配置項目
cmake -S . -B build 
# 建構項目
cmake --build build
# 執行
./build/bin/main
```

```
sudo cp ./libs/onnxruntime-osx-x86_64-1.15.1/lib/libonnxruntime.1.15.1.dylib /usr/local/lib/
g++ ./src/iris_DNN.cpp -o main -I ./libs/onnxruntime-osx-x86_64-1.15.1/include -L ./libs/onnxruntime-osx-x86_64-1.15.1/lib -lonnxruntime -std=c++17
g++ ./src/iris_DNN.cpp -o main ./libs/onnxruntime-osx-x86_64-1.15.1/lib/libonnxruntime.1.15.1.dylib -I./libs/onnxruntime-osx-x86_64-1.15.1/include -std=c++17
```