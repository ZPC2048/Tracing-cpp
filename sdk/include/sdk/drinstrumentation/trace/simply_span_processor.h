#pragma once

#include <memory>

#include "sdk/drinstrumentation/trace/exporter.h"
#include "sdk/drinstrumentation/trace/span_processor.h"

namespace drinstrumentation {
namespace sdk {
namespace trace {

class SimplySpanProcessor : public SpanProcessor {
 public:
  void onStart() override;
  void onEnd(drinstrumentation::trace::SpanContext context) override;

 private:
  std::unique_ptr<SpanExporter> exporter_;
};

}  // namespace trace
}  // namespace sdk
}  // namespace drinstrumentation