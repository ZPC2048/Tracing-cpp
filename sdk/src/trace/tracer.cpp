#include "sdk/drinstrumentation/trace/tracer.h"

#include "sdk/drinstrumentation/trace/span.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

Tracer::Tracer(std::shared_ptr<TracerContext> context) : context_(context) {}

std::shared_ptr<drinstrumentation::trace::Span> Tracer::startSpan(
    std::string name,
    const drinstrumentation::trace::SpanContext& parent_span) {
      
  auto current_span = getCurrentSpan();

  bool should_sample = false;
  bool is_parent_span_valid = false;

  if (parent_span)

  if (current_span != nullptr) {
    should_sample = current_span->getContext().isSampled();
    is_parent_span_valid = true;
  } else {
    should_sample = context_->getSampler().shouldSample(
        drinstrumentation::trace::SpanContext::getInvalid());
  }

  IdGenerator& generator = getIdGenerator();
  drinstrumentation::trace::TraceId trace_id;
  drinstrumentation::trace::SpanId span_id = generator.generateSpanId();

  if (is_parent_span_valid) {
    trace_id = current_span->getContext().getTraceId();
  } else {
    trace_id = generator.generateTraceId();
  }

  auto span_context = std::unique_ptr<drinstrumentation::trace::SpanContext>(
      new drinstrumentation::trace::SpanContext{
          trace_id, span_id, should_sample,
          is_parent_span_valid
              ? current_span->getContext().getTraceState()
              : drinstrumentation::trace::TraceState::getDefault()});

  return std::shared_ptr<drinstrumentation::trace::Span>{
      new Span{shared_from_this(), name,
               is_parent_span_valid ? current_span->getContext().getSpanId()
                                    : drinstrumentation::trace::SpanId{},
               std::move(span_context)}};
}

SpanProcessor& Tracer::getProcessor() { return context_->getProcessor(); }

IdGenerator& Tracer::getIdGenerator() const {
  return context_->getIdGenerator();
}

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation