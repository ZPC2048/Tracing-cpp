#include "drinstrumentation/exporters/zipkin/zipkin_exporter.h"
#include "drinstrumentation/init.h"
#include "sdk/drinstrumentation/checker/checker.h"
#include "sdk/drinstrumentation/instrumentation/instrumentation.h"
#include "sdk/drinstrumentation/trace/random_id_generator.h"
#include "sdk/drinstrumentation/trace/samplers/always_on_sampler.h"
#include "sdk/drinstrumentation/trace/simply_span_processor.h"
#include "sdk/drinstrumentation/trace/tracer_provider.h"

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {
  std::unique_ptr<drinstrumentation::sdk::trace::SpanExporter> exporter{
      new drinstrumentation::exporter::zipkin::ZipkinExporter};

  std::unique_ptr<drinstrumentation::sdk::trace::SpanProcessor> processor{
      new drinstrumentation::sdk::trace::SimplySpanProcessor{
          std::move(exporter)}};

  std::shared_ptr<drinstrumentation::sdk::trace::TracerContext> context{
      new drinstrumentation::sdk::trace::TracerContext{
          std::move(std::unique_ptr<drinstrumentation::sdk::trace::Sampler>(
              new drinstrumentation::sdk::trace::AlwaysOnSampler)),
          std::move(std::unique_ptr<drinstrumentation::sdk::trace::IdGenerator>(
              new drinstrumentation::sdk::trace::RandomIdGenerator)),
          std::move(processor)}};

  std::shared_ptr<drinstrumentation::sdk::trace::TracerProvider> provider{
      new drinstrumentation::sdk::trace::TracerProvider{context}};

  drinstrumentation::trace::Provider().setTracerProvider(provider);

  std::shared_ptr<drinstrumentation::checker::Checker> checker{
      new drinstrumentation::sdk::checker::Checker{}};
  std::shared_ptr<drinstrumentation::instrumentation::Instrumentation> instr{
      new drinstrumentation::sdk::instrumentation::Instrumentation(checker)};
  drinstrumentation::init_client(instr);
}