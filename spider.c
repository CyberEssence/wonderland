#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>

void get_user_input(char *hostname, int *start_port, int *end_port) {
    printf("Enter hostname or IP: ");
    scanf("%s", hostname);

    printf("Enter start port number: ");
    scanf("%d", start_port);

    printf("Enter end port number: ");
    scanf("%d", end_port);
}

int initialize_socket_address(struct sockaddr_in *addr, const char *hostname) {
    if (isdigit(hostname[0])) {
        addr->sin_addr.s_addr = inet_addr(hostname);
    } else {
        struct hostent *host = gethostbyname(hostname);
        if (host == NULL) {
            herror(hostname);
            return -1;
        }
        memcpy(&addr->sin_addr, host->h_addr, host->h_length);
    }
    addr->sin_family = AF_INET;
    return 0;
}

void port_scan(struct sockaddr_in *addr, int start_port, int end_port) {
    struct sockaddr_in addr_copy = *addr;
    printf("Starting the portscan loop:\n");
    for (int port = start_port; port <= end_port; ++port) {
    	addr_copy.sin_port = htons(port);
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("socket");
            exit(1);
        }

        addr->sin_port = htons(port);
        if (connect(sock, (struct sockaddr *)addr, sizeof(*addr)) == 0) {
            printf("%-5d open\n", port);
        }
        close(sock);
    }
    printf("\r");
    fflush(stdout);
}

int main() {
    char hostname[256];
    int start_port, end_port;

    get_user_input(hostname, &start_port, &end_port);

    struct sockaddr_in addr;
    if (initialize_socket_address(&addr, hostname) != 0) {
        exit(2);
    }

    port_scan(&addr, start_port, end_port);

    return 0;
}

