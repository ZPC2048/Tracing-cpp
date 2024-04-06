#include "sdk/drinstrumentation/trace/simply_span_processor.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

SimplySpanProcessor::SimplySpanProcessor(
    std::unique_ptr<SpanExporter>&& exporter)
    : exporter_(std::move(exporter)) {}

SimplySpanProcessor::~SimplySpanProcessor() {}

void SimplySpanProcessor::onEnd(const drinstrumentation::trace::Span& span) {
  exporter_->Export(span);
}

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation