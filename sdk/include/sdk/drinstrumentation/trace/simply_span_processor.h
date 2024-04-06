#pragma once

#include <memory>

#include "sdk/drinstrumentation/trace/exporter.h"
#include "sdk/drinstrumentation/trace/span_processor.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class SimplySpanProcessor : public SpanProcessor {
 public:
  SimplySpanProcessor(std::unique_ptr<SpanExporter>&& exporter);
  ~SimplySpanProcessor() override;
  void onEnd(const drinstrumentation::trace::Span& span) override;

 private:
  std::unique_ptr<SpanExporter> exporter_;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation