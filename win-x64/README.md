
```sh
cmake -B build -S .
cmake --build build
./build/bin/Debug/main.exe
```


編譯完成後，必須要把 data 資料夾和 onnxruntime.dll 複製到 build/Debug 資料夾中。這樣執行 main.exe 才能正確被連動。

