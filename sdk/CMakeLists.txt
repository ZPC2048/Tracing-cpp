add_library(tracing_sdk INTERFACE)
target_include_directories(tracing_sdk
  INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>")

add_subdirectory(src)