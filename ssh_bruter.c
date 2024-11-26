#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "net/ssh.c"

#define MAX_ATTEMPTS 3
#define SLEEP_TIME 5

#define MAX_USERS 100
#define MAX_PASSWORDS 1000

int authSSH(int maxAttempts) {
    ssh_session my_ssh_session;
    int rc;
    char *password;
    const char *hostname = "";
    const char *username = "";
    
    ssh_channel channel;

    int attempts = 0;

    while (attempts < maxAttempts) {

    	my_ssh_session = ssh_new();
    	if (my_ssh_session == NULL) {
        	return -1;
	}


    	ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, hostname);
    	ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, username);


    	rc = ssh_connect(my_ssh_session);
    	if (rc != SSH_OK) {
    	    	fprintf(stderr, "Error connecting to host: %s\\n", ssh_get_error(my_ssh_session));
        	ssh_free(my_ssh_session);
        	return -1;
    	}
	
    	password = getpass("Password: ");
    	rc = ssh_userauth_password(my_ssh_session, NULL, password);
    	if (rc == SSH_AUTH_SUCCESS) {
        	printf("Authentication successful!\n");
		ssh_free(my_ssh_session);
		// automatic_shell_session(my_ssh_session);
		//interactive_shell_session(my_ssh_session);
		//system("/bin/bash");
            	return 0;
    	} else {
		fprintf(stderr, "Error authenticating with password: %s\\n", ssh_get_error(my_ssh_session));
        	ssh_disconnect(my_ssh_session);
        	ssh_free(my_ssh_session);
		attempts++;
		printf("Attempt %d failed. Retrying in %d seconds...\n", attempts, SLEEP_TIME);
        	sleep(SLEEP_TIME);
    	}
    }
    
    fprintf(stderr, "Max attempts reached. Authentication failed.");
    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);
    
    return -1;
}


int main(int argc, char *argv[]) {
    
    ssh_session session;
    ssh_channel channel;
    int rc, port = 22;
    char buffer[1024];
    unsigned int nbytes;

    char hostname[256];
    char username[256];
    char *password;
    
    printf("Enter hostname and username: ");
    scanf("%s %s", &hostname, &username);
    
    printf("Session...\n");
    session = ssh_new();
    if (session == NULL) exit(-1);

    ssh_options_set(session, SSH_OPTIONS_HOST, hostname);
    ssh_options_set(session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(session, SSH_OPTIONS_USER, username);

    printf("Connecting...\n");
    rc = ssh_connect(session);
    if (rc != SSH_OK) error(session);

    printf("Password Autentication...\n");
    password = getpass("Password: ");
    rc = ssh_userauth_password(session, NULL, password);
    if (rc != SSH_AUTH_SUCCESS) error(session);

    printf("Channel...\n");
    channel = ssh_channel_new(session);
    if (channel == NULL) exit(-1);

    printf("Opening...\n");
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) error(session);

    printf("Executing remote command...\n");
    rc = ssh_channel_request_exec(channel, "/bin/bash -i");
    
    if (rc != SSH_OK) error(session);

    printf("Received:\n");
    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    while (nbytes > 0) {
        fwrite(buffer, 1, nbytes, stdout);
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    }

    free_channel(channel);
    free_session(session);
   
    return 0;
}
