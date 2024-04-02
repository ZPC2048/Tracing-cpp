#pragma once

#include "drinstrumentation/exporters/zipkin/zipkin_exporter_options.h"
#include "drinstrumentation/trace/exporter.h"

namespace drinstrumentation {
namespace exporter {

class ZipkinExporter final
    : public drinstrumentation::sdk::trace::SpanExporter {
 private:
  ZipkinExporterOptions options_;
};

}  // namespace exporter
}  // namespace drinstrumentation