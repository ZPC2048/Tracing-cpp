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
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == -1) {
    return;
  }
  // addrinfo hints;
  // memset(&hints, 0, sizeof(hints));
  // hints.ai_family = AF_INET;
  // hints.ai_socktype = SOCK_STREAM;
  // hints.ai_protocol = IPPROTO_TCP;

  // addrinfo* res;

  // if (getaddrinfo("localhost", "9411", &hints, &res) != 0) {
  //   return;
  // }

  // bool connect_success = false;
  // for (addrinfo* cur = res; cur != nullptr; cur = cur->ai_next){
  //   if (connect(sock, cur->ai_addr, cur->ai_addrlen) != -1){
  //     connect_success = true;
  //     break;
  //   }
  // }
  // if (!connect_success) {
  //   return;
  // }

  sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(options_.zipkin_port);
  inet_aton(options_.zipkin_addr.data(), &server_addr.sin_addr);

  if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    return;
  }

  std::string payload = span.getSpanJson();

  std::string post_request = "POST " + options_.zipkin_api +
                             " HTTP/1.1\r\n"
                             "Host: " +
                             options_.zipkin_addr + ":" +
                             std::to_string(options_.zipkin_port) + "\r\n";
  for (auto header : options_.headers) {
    post_request += header.first + ":" + header.second + "\r\n";
  }
  post_request += "Content-Length: " + std::to_string(payload.length()) +
                  "\r\n\r\n" + payload;

  send(sock, post_request.c_str(), post_request.length(), 0);

  // freeaddrinfo(res);
  close(sock);
}

}  // namespace zipkin
}  // namespace exporter
}  // namespace drinstrumentation