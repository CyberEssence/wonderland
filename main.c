#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>
#include <libssh/callbacks.h>
#include "net/spider.c"
#include "net/ssh_auth.c"

int main(int argc, char *argv[]) {
    
    char hostname[256];
    char username[256];
    int startPort;
    int endPort;
    
    printf("Enter hostname and username: ");
    scanf("%s %s", &hostname, &username);
    
    printf("Enter start port number: ");
    scanf("%d", &startPort);

    printf("Enter end port number: ");
    scanf("%d", &endPort);
    

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

    createChannel(rc, channel, session);


    // Open channel

    rc = ssh_channel_open_session(channel);

    openChannel(rc, channel, session);

    rc = ssh_channel_request_pty(channel);

    requestPty(rc, channel, session);

    rc = ssh_channel_request_shell(channel);

    requestShell(rc, channel, session);

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
    
    sshExecBash(nbytes, rc, channel, session, buffer);

    freeChannel(channel);
    freeSession(session);
    
    return 0;
}
