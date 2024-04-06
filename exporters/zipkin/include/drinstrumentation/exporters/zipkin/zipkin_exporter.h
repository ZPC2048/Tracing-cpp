#pragma once

#include "drinstrumentation/exporters/zipkin/zipkin_exporter_options.h"
#include "drinstrumentation/trace/exporter.h"

namespace drinstrumentation {
namespace exporter {
namespace zipkin {

class ZipkinExporter final
    : public drinstrumentation::sdk::trace::SpanExporter {
 public:
  ZipkinExporter(const ZipkinExporterOptions& options);
  void Export(const drinstrumentation::trace::Span& span) override;

 private:
  ZipkinExporterOptions options_;
};

}  // namespace zipkin
}  // namespace exporter
}  // namespace drinstrumentation