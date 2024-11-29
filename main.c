#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>
#include <libssh/callbacks.h>
#include "net/spider.c"
#include "net/ssh_auth.c"

int main(int argc, char *argv[]) {
    /*if (argc != 4) {
        fprintf(stderr, "Usage: %s <hostname> <start_port> <end_port>\n", argv[0]);
        return 1;
    }*/
    
    
    
    char hostname[256];
    char username[256];
    int start_port;
    int end_port;
    
    printf("Enter hostname and username: ");
    scanf("%s %s", &hostname, &username);
    
    printf("Enter start port number: ");
    scanf("%d", &start_port);

    printf("Enter end port number: ");
    scanf("%d", &end_port);
    

    struct sockaddr_in addr;
    if (initializeSocketAddress(&addr, hostname) != 0) {
        fprintf(stderr, "Failed to initialize socket address.\n");
        exit(2);
    }
     
    portScan(&addr, start_port, end_port);

    ssh_session session;
    ssh_channel channel;
    int rc;
    char *buffer = malloc(sizeof(char) * 1024); // Allocate memory for buffer
    unsigned int nbytes;
    char *password;

    printf("Session...\n");
    printf("Session...\n");
    session = ssh_new();
    if (session == NULL) exit(-1);

    ssh_options_set(session, SSH_OPTIONS_HOST, hostname);
    ssh_options_set(session, SSH_OPTIONS_PORT, &start_port);
    ssh_options_set(session, SSH_OPTIONS_USER, username);

    printf("Connecting...\n");
    rc = ssh_connect(session);
    
    if (rc != SSH_OK) error(session);

    printf("Password Autentication...\n");
    password = getpass("Password: ");
    rc = ssh_userauth_password(session, NULL, password);
    
    
    auth(rc, session);


    // Create channel

    channel = ssh_channel_new(session);

    create_channel(rc, channel, session);


    // Open channel

    rc = ssh_channel_open_session(channel);

    open_channel(rc, channel, session);



    rc = ssh_channel_request_pty(channel);

    request_pty(rc, channel, session);

    

    rc = ssh_channel_request_shell(channel);

    request_shell(rc, channel, session);

    while (1) {

        int nchars = ssh_channel_read(channel, buffer, sizeof(buffer), 0);

        if (nchars > 0) {

            fwrite(buffer, 1, nchars, stdout);

        }
    }



    ssh_channel_close(channel);

    ssh_channel_free(channel);

    ssh_disconnect(session);

    ssh_free(session);
    
    ssh_exec_bash(nbytes, rc, channel, session, buffer);

    free_channel(channel);
    free_session(session);
    
    return 0;
}
