add_library(tracing_api INTERFACE)

target_include_directories(tracing_api
  INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>")