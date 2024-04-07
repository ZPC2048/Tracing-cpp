add_library(tracing_checker checker.cpp)

target_include_directories(
  tracing_checker
  PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/sdk/include>")