#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <string>

bool Post(int fd, const char* payload, size_t payload_length, char* receive,
          size_t receive_length) {
  size_t offset = 0;
  while (offset < payload_length) {
    int result = send(fd, payload + offset, payload_length - offset, 0);
    if (result == -1) {
      return false;
    }
    offset += result;
  }
  offset = 0;
  while (offset < receive_length) {
    int result = read(fd, receive + offset, receive_length - offset);
    if (result == 0) {
      break;
    } else if (result == -1) {
      receive[offset] = '\0';
      return false;
    }
    offset += result;
  }
  receive[offset] = '\0';
  return true;
}

int main(int argc, char* argv[]) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    return -1;
  }

  sockaddr_in address;
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(8080);

  int result = connect(sockfd, (sockaddr*)&address, sizeof(address));
  if (result == -1) {
    perror("oops: client1");
    return -1;
  }

  std::string payload =
      "POST / HTTP/1.0\r\n"
      "Host: 127.0.0.1:8080\r\n"
      "Content-type: application/json\r\n"
      "Content-Length: 18\r\n\r\n"
      R"(["Hello", "World"])";
  int receive_length = 500;
  char* receive = new char[receive_length];

  Post(sockfd, payload.data(), payload.length(), receive, receive_length - 1);

  printf("POST message: %s\n", payload.data());
  printf("receive message: %s\n", receive);
  close(sockfd);
  return 0;
}