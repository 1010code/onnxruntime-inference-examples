SET(CMAKE_CXX_STANDARD 17)
ADD_EXECUTABLE(main iris_DNN.cpp)

# 建立 onnxruntime target
add_library(onnxruntime SHARED IMPORTED)
# 設定 onnxruntime lib & include
set_target_properties(onnxruntime PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/libs/onnxruntime-win-x64-1.15.1/include"
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/onnxruntime-win-x64-1.15.1/lib/onnxruntime.dll"
        IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/libs/onnxruntime-win-x64-1.15.1/lib/onnxruntime.lib"
)
# PdmWapper 相依 onnxruntime
target_link_libraries(main PUBLIC onnxruntime)


# 複製檔案到指定位置
add_custom_command(
  TARGET main
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_SOURCE_DIR}/data"
          "$<TARGET_FILE_DIR:main>/data"
  COMMAND ${CMAKE_COMMAND} -E copy 
          "${CMAKE_SOURCE_DIR}/libs/onnxruntime-win-x64-1.15.1/lib/onnxruntime.dll"
          "$<TARGET_FILE_DIR:main>/onnxruntime.dll"
)