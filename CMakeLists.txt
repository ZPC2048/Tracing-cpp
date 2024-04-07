cmake_minimum_required(VERSION 3.0)

project(Tracing)

add_library(Tracing SHARED "Tracing.cpp")

find_package(DynamoRIO)
configure_DynamoRIO_client(Tracing)

use_DynamoRIO_extension(Tracing drmgr)
use_DynamoRIO_extension(Tracing drwrap)
use_DynamoRIO_extension(Tracing drsyms)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(api/include)
add_subdirectory(api)

include_directories(sdk/include)
add_subdirectory(sdk)

include_directories(exporters/zipkin/include)
add_subdirectory(exporters)

target_link_libraries(
  Tracing
  tracing_api
  tracing_checker
  tracing_instrumentation
  tracing_trace
  tracing_exporter_zipkin
)