
```sh
# 配置項目
cmake -S . -B build 
# 建構項目
cmake --build build
# 執行
./build/bin/main
```

```
cd onnxruntime-linux-aarch64-1.12.1
sudo cp ./lib/libonnxruntime.so /usr/lib/
g++ ./src/iris_DNN.cpp -o main -I ./include -L ./lib -lonnxruntime -std=c++17
g++ ./src/iris_DNN.cpp -o main ./lib/libonnxruntime.so -I./include -std=c++17
```