
```sh
# 配置項目
cmake -S . -B build 
# 建構項目
cmake --build build
# 執行
./build/bin/main
```

```
sudo cp ./lib/libonnxruntime.1.12.1.dylib /usr/local/lib/
g++ ./src/iris_DNN.cpp -o main -I ./include -L ./lib -lonnxruntime -std=c++17
g++ ./src/iris_DNN.cpp -o main ./lib/libonnxruntime.1.12.1.dylib -I./include -std=c++17
```