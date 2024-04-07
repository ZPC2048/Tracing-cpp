cmake_minimum_required(VERSION 3.0)

project(Tracing)

add_library(Tracing SHARED "Tracing.cpp")

find_package(DynamoRIO)
configure_DynamoRIO_client(Tracing)

use_DynamoRIO_extension(Tracing drmgr)
use_DynamoRIO_extension(Tracing drwrap)
use_DynamoRIO_extension(Tracing drsyms)

include_directories(api/include)
add_subdirectory(api)

include_directories(sdk/include)
add_subdirectory(sdk)
add_subdirectory(exporters)

target_link_libraries(
  Tracing 
  tracing_api
  tracing_sdk
  tracing_exporter_zipkin)