#pragma once

#include <map>
#include <string>

#include "drinstrumentation/defines.h"

namespace drinstrumentation {
namespace exporter {
namespace zipkin {

struct ZipkinExporterOptions {
  std::string zipkin_addr = "127.0.0.1";
  uint16 zipkin_port = 9411;
  std::string zipkin_api = "/api/v2/spans";
  std::string service_name = "default-service";
  std::string service_addr = "127.0.0.1";
  std::map<std::string, std::string> headers = {
      {"Content-type", "application/json"}};
};

}  // namespace zipkin
}  // namespace exporter
}  // namespace drinstrumentation