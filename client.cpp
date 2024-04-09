#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

bool Post(int fd, char* payload, size_t payload_length, char* receive, size_t receive_length) {
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

int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        return -1;
    }

    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);

    int result = connect(sockfd, (sockaddr *)&address, sizeof(address));
    if (result == -1) {
        perror("oops: client1");
        return -1;
    }

    int payload_length = 500;
    int receive_length = 500;
    char* payload = new char[payload_length];
    char* receive = new char[receive_length];

    Post(sockfd, payload, payload_length - 1, receive, receive_length - 1);

    printf("POST message: %s\n", payload);
    printf("receive message: %s\n", receive);
    close(sockfd);
    return 0;
}