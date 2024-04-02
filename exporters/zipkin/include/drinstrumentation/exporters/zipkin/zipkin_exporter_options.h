#pragma once

#include <map>
#include <string>

struct ZipkinExporterOptions {
  // The endpoint to export to. By default the OpenTelemetry Collector's default
  // endpoint.
  std::string endpoint = "";  // GetDefaultZipkinEndpoint();
  std::string service_name = "default-service";
  std::string ipv4;
  std::string ipv6;
  std::map<std::string, std::string> headers = {
      {"content-type", "application/json"}};
};