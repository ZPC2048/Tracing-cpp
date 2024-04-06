#pragma once

#include <map>
#include <string>

namespace drinstrumentation {
namespace exporter {
namespace zipkin {

struct ZipkinExporterOptions {
  std::string endpoint = "http://localhost:9411/api/v2/spans";
  std::string service_name = "default-service";
  std::map<std::string, std::string> headers = {
      {"content-type", "application/json"}};
};

}  // namespace zipkin
}  // namespace exporter
}  // namespace drinstrumentation