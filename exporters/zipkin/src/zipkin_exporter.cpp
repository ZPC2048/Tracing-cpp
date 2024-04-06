#include "drinstrumentation/exporters/zipkin/zipkin_exporter.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

namespace drinstrumentation {
namespace exporter {
namespace zipkin {

ZipkinExporter::ZipkinExporter(const ZipkinExporterOptions& options)
    : options_(options) {}

void ZipkinExporter::Export(const drinstrumentation::trace::Span& span) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    return;
  }

  hostent* host = gethostbyname("localhost");
  if (host == nullptr) {
    return;
  }

  sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(9411);
  inet_aton(host->h_addr_list[0], &server_addr.sin_addr);

  if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    return;
  }

  std::string payload = span.getSpanJson();

  std::string post_request =
      "POST /api/v2/spans HTTP/1.1\r\n"
      "Host: localhost:9411\r\n"
      "Content-Type: application/json\r\n"
      "Content-Length: " +
      std::to_string(payload.length()) + "\r\n\r\n" + payload;

  if (send(sock, post_request.c_str(), post_request.length(), 0) == -1) {
    return;
  }

  close(sock);
}

}  // namespace zipkin
}  // namespace exporter
}  // namespace drinstrumentation