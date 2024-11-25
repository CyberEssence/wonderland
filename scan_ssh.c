#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4 // Number of threads to use

char* custom_inet_ntoa(uint32_t ip_int);

typedef struct {
    uint32_t start;
    uint32_t end;
    int port;
} scan_data_t;

void* scan_ssh_port_range_thread(void* arg) {
    scan_data_t* data = (scan_data_t*)arg;
    
    for(uint32_t ip = data->start; ip <= data->end; ip++) {
        char* ip_str = custom_inet_ntoa(ip);
        
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(data->port);
        addr.sin_addr.s_addr = ip;
        
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            perror("Socket creation failed");
            continue;
        }
        
        int result = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        if (result < 0) {
            printf("Error connecting to IP address %s: %s\n", ip_str, strerror(errno));
            free(ip_str);
            close(sock);
            continue;
        }
        
        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
            printf("Port %d is open on IP address %s\n", data->port, ip_str);
            fflush(stdout);
            free(ip_str); // Free the allocated string
            close(sock);
        } else {
            printf("Port %d is closed on IP address %s\n", data->port, ip_str);
            fflush(stdout);
            free(ip_str); // Free the allocated string
            close(sock);
        }
    }
    
    pthread_exit(NULL);
}

void scan_ssh_port_range(const char* start_ip, const char* end_ip, int port) {
    uint32_t start = inet_addr(start_ip);
    uint32_t end = inet_addr(end_ip);
    
    pthread_t threads[NUM_THREADS];
    scan_data_t thread_args[NUM_THREADS];

    // Initialize thread arguments
    uint32_t chunk_size = (end - start + NUM_THREADS - 1) / NUM_THREADS;
    for(int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].start = start + i * chunk_size;
        thread_args[i].end = (i == NUM_THREADS - 1) ? end : start + (i + 1) * chunk_size - 1;
        thread_args[i].port = port;
    }

    // Create threads
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, scan_ssh_port_range_thread, &thread_args[i]);
    }

    // Wait for all threads to complete
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
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
