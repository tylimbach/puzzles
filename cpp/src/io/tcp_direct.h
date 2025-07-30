#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <tcpdirect/tcpdirect.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define PORT 8080

int main() {
    struct tcpdirect_stack* stack;
    struct tcpdirect_socket* sock;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Initialize TCPDirect stack
    stack = tcpdirect_stack_alloc();
    if (!stack) {
        fprintf(stderr, "Failed to allocate TCPDirect stack\n");
        return EXIT_FAILURE;
    }

    // Create a TCPDirect socket
    sock = tcpdirect_socket_alloc(stack);
    if (!sock) {
        fprintf(stderr, "Failed to allocate TCPDirect socket\n");
        tcpdirect_stack_free(stack);
        return EXIT_FAILURE;
    }

    // Connect to the server
    if (tcpdirect_connect(sock, "127.0.0.1", 8080) < 0) {
        fprintf(stderr, "Failed to connect to server\n");
        tcpdirect_socket_free(sock);
        tcpdirect_stack_free(stack);
        return EXIT_FAILURE;
    }

    printf("Connected to server.\n");

    // Read data into buffer
    while ((bytes_read = tcpdirect_recv(sock, buffer, BUFFER_SIZE)) > 0) {
        printf("Received %d bytes: %.*s\n", bytes_read, bytes_read, buffer);
    }

    if (bytes_read < 0) {
        fprintf(stderr, "Error reading data\n");
    }

    tcpdirect_socket_free(sock);
    tcpdirect_stack_free(stack);
    printf("Connection closed.\n");

    return 0;
}
