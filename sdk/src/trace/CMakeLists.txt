add_library(
  tracing_trace
  tracer_context.cpp
  tracer_provider.cpp
  tracer.cpp
  span.cpp
  simply_span_processor.cpp
  samplers/always_off_sampler.cpp
  samplers/always_on_sampler.cpp
  random_id_generator.cpp)

target_include_directories(
  tracing_trace PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/sdk/include>"
)