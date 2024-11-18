#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

void scan_ssh_port_range(const char* start_ip, const char* end_ip, int port);
char* custom_inet_ntoa(uint32_t ip_int);
uint32_t inet_addr(const char* ip_string);

void scan_ssh_port_range(const char* start_ip, const char* end_ip, int port) {
    uint32_t start = inet_addr(start_ip);

    //free(ip_str);

    uint32_t end = inet_addr(end_ip);
    
    for (uint32_t ip = start; ip <= end; ip++) {
        char* ip_str = custom_inet_ntoa(ip);
        
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = ip;
        
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            perror("Socket creation failed");
            continue;
        }
        
        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
            printf("Port %d is open on IP address %s\n", port, ip_str);
            fflush(stdout);
            free(ip_str); // Free the allocated string
            close(sock);
        } else {
            printf("Port %d is closed on IP address %s\n", port, ip_str);
            fflush(stdout);
            free(ip_str); // Free the allocated string
            close(sock);
        }
    }
}

uint32_t inet_addr(const char* ip_string) {
    struct in_addr addr;
    if (inet_pton(AF_INET, ip_string, &addr) <= 0) {
        perror("Invalid IP address");
        exit(1);
    }
    return ntohl(addr.s_addr);
}

char* custom_inet_ntoa(uint32_t ip_int) {
    struct in_addr addr;
    inet_ntop(AF_INET, &ip_int, &addr, sizeof(addr));
    char* buffer = malloc(16);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    inet_ntop(AF_INET, &addr, buffer, 16);
    return buffer;
}


int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <start_IP> <end_IP> <port>\n", argv[0]);
        exit(1);
    }

    const char* start_ip = argv[1];
    const char* end_ip = argv[2];
    int port = atoi(argv[3]);

    scan_ssh_port_range(start_ip, end_ip, port);

    return 0;
}
