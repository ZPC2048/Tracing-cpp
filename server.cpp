#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

constexpr int MAX_CONNECTIONS = 5;
constexpr int BUFFER_SIZE = 4096;

int main(int argc, char* argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // 创建socket文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 为socket文件描述符设置选项
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    address.sin_port = htons(8080);

    // 绑定socket到地址
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 开始监听请求
    if (listen(server_fd, MAX_CONNECTIONS) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        std::cout << "Listening for connections on port 8080..." << std::endl;

        // 接受连接
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE] = {0};
        long valread = read(new_socket, buffer, BUFFER_SIZE);
        std::string request(buffer);

        // 打印收到的请求内容（可选）
        // std::cout << request << std::endl;

        // 简单判断是否为POST请求
        if (valread > 0 && request.find("POST") != std::string::npos) {
            // 发送HTTP响应
            std::string http_response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
            send(new_socket, http_response.c_str(), http_response.length(), 0);
        }
        
        close(new_socket);
    }

    // 关闭server socket（理论上应该永远不会执行到这里）
    close(server_fd);
    return 0;
}