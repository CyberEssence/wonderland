#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void scan_ssh_port(const char* ip_address, int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip_address, &addr.sin_addr);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
        printf("Port %d is open on IP address %s\n", port, ip_address);
        close(sock);
    } else {
        printf("Port %d is closed on IP address %s\n", port, ip_address);
        close(sock);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP_address> <port>\n", argv[0]);
        exit(1);
    }

    const char* ip_address = argv[1];
    int port = atoi(argv[2]);

    scan_ssh_port(ip_address, port);

    return 0;
}
