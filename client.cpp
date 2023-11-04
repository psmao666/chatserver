#include <iostream>
#include <winsock.h>

#define SERVER_PORT 5208
#define SERVER_IP "127.0.0.1"
struct sockaddr_in srv_addr;

void error_output(const std::string& err);

int main() {
    std::cout << "Input your name: \n";
    std::string client_name;
    std::cin >> client_name;

    WSADATA ws;
    if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
        error_output("Failed to set up the WSA variables.");
    }
    int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket < 0) {
        error_output("Failed to open the socket");
    }
    srv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    srv_addr.sin_port = htons(SERVER_PORT);
    srv_addr.sin_family = AF_INET;
    memset(&(srv_addr.sin_zero), 0, 8);

    if (connect(nSocket, (sockaddr*)&srv_addr, sizeof(sockaddr)) < 0) {
        error_output("Failed to connect to the server!");
    }
    std::cout << "Successfully connected to the server\n";
    std::string msg = "New client " + client_name;
    send(nSocket, msg.c_str(), msg.size() + 1, 0);


    return 0;
}

void error_output(const std::string& err) {
    std::cout << err << std::endl;
    exit(0);
}
