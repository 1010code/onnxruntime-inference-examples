SET(CMAKE_CXX_STANDARD 17)
ADD_EXECUTABLE(main iris_DNN.cpp)

# 建立 onnxruntime target
add_library(onnxruntime SHARED IMPORTED)
# 設定 onnxruntime lib & include
set_target_properties(onnxruntime PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/libs/onnxruntime-linux-x64-1.15.1/include"
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/onnxruntime-linux-x64-1.15.1/lib/libonnxruntime.so"
)
# PdmWapper 相依 onnxruntime
target_link_libraries(main PUBLIC onnxruntime)


add_custom_command(
  TARGET main
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${PROJECT_SOURCE_DIR}/data"
          "$<TARGET_FILE_DIR:main>/data"
)


# SET(CMAKE_CXX_STANDARD 17)
# INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/onnxruntime-linux-x64-1.15.1/include)
# LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/onnxruntime-linux-x64-1.15.1/lib)
# ADD_EXECUTABLE(main iris_DNN.cpp)
# TARGET_LINK_LIBRARIES(main libonnxruntime.so)

# add_custom_command(
#   TARGET main
#   POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#           "${PROJECT_SOURCE_DIR}/data"
#           "$<TARGET_FILE_DIR:main>/data"
# )