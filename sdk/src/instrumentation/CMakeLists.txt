add_library(tracing_instrumentation instrumentation.cpp)

find_package(DynamoRIO)
configure_DynamoRIO_client(tracing_instrumentation)
use_DynamoRIO_extension(tracing_instrumentation drwrap)

target_include_directories(
  tracing_instrumentation
  PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/sdk/include>")