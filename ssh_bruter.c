#include <libssh/libssh.h>
#include <libssh/callbacks.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "net/ssh.c"
#include "net/auth.c"

int main(int argc, char *argv[]) {
    
    ssh_session session;
    ssh_channel channel;
    int rc, port = 22;
    char buffer[1024];
    unsigned int nbytes;

    char *password;
    
    
    
    printf("Session...\n");
    session = ssh_new();
    if (session == NULL) exit(-1);

    ssh_opt_set(session, port);

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
    
    ssh_exec_bash(nbytes, rc, channel, session, session);

    free_channel(channel);
    free_session(session);
   
    return 0;
}
