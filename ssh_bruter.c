#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    ssh_session my_ssh_session;
    int rc;
    char *password;
    const char *hostname = "192.168.1.68";
    const char *username = "vboxuser";


    my_ssh_session = ssh_new();
    if (my_ssh_session == NULL) 
        exit(-1);


    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, hostname);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, username);


    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error connecting to host: %s\\n", ssh_get_error(my_ssh_session));
        ssh_free(my_ssh_session);
        exit(-1);
    }

    /*if (verify_knownhost(my_ssh_session) < 0) {
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }*/

    password = getpass("Password: ");
    rc = ssh_userauth_password(my_ssh_session, NULL, password);
    if (rc != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Error authenticating with password: %s\\n", ssh_get_error(my_ssh_session));
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }

    printf("Authentication successful!\\n");

    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);
    return 0;
}
