SET(CMAKE_CXX_STANDARD 17)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
ADD_EXECUTABLE(main iris_DNN.cpp)
TARGET_LINK_LIBRARIES(main libonnxruntime.so)

add_custom_command(
  TARGET main
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${PROJECT_SOURCE_DIR}/data"
          "$<TARGET_FILE_DIR:main>/data"
)