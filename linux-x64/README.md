
```sh
# 配置項目
cmake -S . -B build 
# 建構項目
cmake --build build
# 執行
./build/bin/main
```

```
cd libs/onnxruntime-linux-x64-1.15.1
sudo cp ./lib/libonnxruntime.so.1.15.1 /usr/lib/
g++ ./src/iris_DNN.cpp -o main -I ./libs/onnxruntime-linux-x64-1.15.1/include -L ./libs/onnxruntime-linux-x64-1.15.1/lib -lonnxruntime -std=c++17
g++ ./src/iris_DNN.cpp -o main ./libs/onnxruntime-linux-x64-1.15.1/lib/libonnxruntime.so -I./libs/onnxruntime-linux-x64-1.15.1/include -std=c++17
```