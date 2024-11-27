#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>

int initialize_socket_address(struct sockaddr_in *addr, const char *hostname) {
    if (isdigit(hostname[0])) {
        addr->sin_addr.s_addr = inet_addr(hostname);
    } else {
        struct hostent *host = gethostbyname(hostname);
        if (host == NULL) {
            perror(hostname);
            return -1;
        }

        // Use h_addr_list to access IP addresses
        for (int i = 0; host->h_addr_list[i] != NULL; i++) {
            memcpy(&addr->sin_addr, host->h_addr_list[i], host->h_length);
            printf("IP address: %s\n", inet_ntoa(addr->sin_addr));
            // You can break after the first IP address or continue to scan all of them
            break; // Uncomment to scan only the first IP address
        }

        //freeaddrinfo(host);
    }
    addr->sin_family = AF_INET;
    return 0;
}

void port_scan(struct sockaddr_in *addr, int start_port, int end_port) {
    printf("Starting the portscan loop:\n");
    for (int port = start_port; port <= end_port; ++port) {
        addr->sin_port = htons(port);
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
