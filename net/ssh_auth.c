#include <libssh/libssh.h>
#include <libssh/callbacks.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void freeChannel(ssh_channel channel) {
    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);
}

void freeSession(ssh_session session) {
    ssh_disconnect(session);
    ssh_free(session);
}

void error(ssh_session session) {
    fprintf(stderr, "Error: %s\n", ssh_get_error(session));
    free_session(session);
    exit(-1);
}

void auth(int rc, ssh_session session) {
    if (rc != SSH_AUTH_SUCCESS) {

	fprintf(stderr, "Authentication failed: %s\n", ssh_get_error(session));

	ssh_disconnect(session);

	ssh_free(session);

	exit(-1);

    }
}

void createChannel(int rc, ssh_channel channel, ssh_session session) {
    if (channel == NULL) {

        fprintf(stderr, "Error creating channel: %s\n", ssh_get_error(session));

        ssh_disconnect(session);

        ssh_free(session);

        exit(-1);

    }
}

void openChannel(int rc, ssh_channel channel, ssh_session session) {
    if (rc != SSH_OK) {

        fprintf(stderr, "Error opening channel: %s\n", ssh_get_error(session));

        ssh_channel_free(channel);

        ssh_disconnect(session);

        ssh_free(session);

        exit(-1);

    }
}

void requestPty(int rc, ssh_channel channel, ssh_session session) {
    if (rc != SSH_OK) {

        fprintf(stderr, "Error requesting pty: %s\n", ssh_get_error(session));

        ssh_channel_free(channel);

        ssh_disconnect(session);

        ssh_free(session);

        exit(-1);

    }
}

void requestShell(int rc, ssh_channel channel, ssh_session session) {
    if (rc != SSH_OK) {

        fprintf(stderr, "Error requesting shell: %s\n", ssh_get_error(session));

        ssh_channel_free(channel);

        ssh_disconnect(session);

        ssh_free(session);

        exit(-1);

    }
}

void sshExecBash(unsigned int nbytes, int rc, ssh_channel channel, ssh_session session, char buffer[]) {	
    printf("Executing remote command...\n");
    rc = ssh_channel_request_exec(channel, "/bin/bash -i");
    
    if (rc != SSH_OK) error(session);

    printf("Received:\n");
    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    while (nbytes > 0) {
        fwrite(buffer, 1, nbytes, stdout);
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    }
}

void sshOptSet(ssh_session session, char *hostname, char *username, int port) {

    ssh_options_set(session, SSH_OPTIONS_HOST, hostname);
    ssh_options_set(session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(session, SSH_OPTIONS_USER, username);
}
