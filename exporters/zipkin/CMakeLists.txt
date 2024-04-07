add_library(tracing_exporter_zipkin src/zipkin_exporter.cpp)

target_include_directories(tracing_exporter_zipkin 
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>")