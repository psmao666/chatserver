#include <iostream>
#include <winsock.h>
#include <atomic>
#include <thread>

constexpr int SERVER_PORT = 5208;
constexpr int MAX_CLIENT = 256;

// variables we gonna use
struct sockaddr_in srv;
struct sockaddr_in client_addr;
std::atomic<int> n_client(0);

// functions we gonna use
void error_output(const std::string& err);

int main() {
    // initialize the WSA variables
    WSADATA ws;
    if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
        error_output("Failed to set up the WSA variables.");
    }
    // initialize the socket
    int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket < 0) {
        error_output("Failed to initialize the socket!");
    } else {
        std::cout << "Successfully initialized the socket\n";
    }
    // setup the socket
    srv.sin_family = AF_INET;
    srv.sin_port = htons(SERVER_PORT);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(srv.sin_zero), 0, 8);

    // bind the socket
    int nRet = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));
    if (nRet < 0) {
        error_output("Failed to bind the socket to local port!");
    } else {
        std::cout << "Successfully binded to the local port.\n";
    }
    std::string ipAddress = inet_ntoa(srv.sin_addr);
    std::cout << "Server is running on IP address: " << ipAddress << ", port number #" << SERVER_PORT << std::endl;
    // listen the socket
    nRet = listen(nSocket, MAX_CLIENT);
    if (nRet < 0) {
        error_output("Failed to listen to local port.");
    }
    // accepting requests
    while (1) {
        int client_addr_size = sizeof(client_addr);
        int clientSocket = accept(nSocket, (sockaddr*)&client_addr, &client_addr_size);
        if (clientSocket == -1) {
            error_output("Failed to accept a message from clients.");
        }
        n_client ++;
        std::cout << "A new client joined, its IP is " << inet_ntoa(client_addr.sin_addr) << std::endl;

    }
    return 0;
}


void error_output(const std::string& err) {
    std::cout << err << std::endl;
    exit(0);
}
