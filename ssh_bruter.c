#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ATTEMPTS 3
#define SLEEP_TIME 5

#define MAX_USERS 100
#define MAX_PASSWORDS 1000


int shell_session(ssh_session session)
{
  ssh_channel channel;
  int rc;
 
  channel = ssh_channel_new(session);
  if (channel == NULL)
    return SSH_ERROR;
 
  rc = ssh_channel_open_session(channel);
  if (rc != SSH_OK)
  {
    ssh_channel_free(channel);
    return rc;
  }
 
  ssh_channel_close(channel);
  ssh_channel_send_eof(channel);
  ssh_channel_free(channel);
 
  return SSH_OK;
}

int interactive_shell_session(ssh_channel channel)
{
  int rc;
 
  rc = ssh_channel_request_pty(channel);
  if (rc != SSH_OK) return rc;
 
  rc = ssh_channel_change_pty_size(channel, 80, 24);
  if (rc != SSH_OK) return rc;
 
  rc = ssh_channel_request_shell(channel);
  if (rc != SSH_OK) return rc;
 
  return rc;
}

int automatic_shell_session(ssh_session session, const char *username, const char *password) {
    ssh_channel channel = NULL;
    
   
    channel = ssh_channel_new(session);
    if (channel == NULL) {
        fprintf(stderr, "Failed to allocate channel\n");
        return SSH_ERROR;
    }

    
    if (ssh_channel_open_session(channel) != SSH_OK) {
        fprintf(stderr, "Failed to open channel session\n");
        ssh_channel_free(channel);
        return SSH_ERROR;
    }

    
    if (ssh_userauth_password(session, username, password) != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Authentication failed: %s\n", ssh_get_error(session));
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return SSH_ERROR;
    }

    
    if (ssh_channel_request_pty(channel) != SSH_OK) {
        fprintf(stderr, "Failed to request pseudo-terminal\n");
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return SSH_ERROR;
    }

    
    if (ssh_channel_change_pty_size(channel, 80, 24) != SSH_OK) {
        fprintf(stderr, "Failed to change pty size\n");
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return SSH_ERROR;
    }

   
    if (ssh_channel_request_shell(channel) != SSH_OK) {
        fprintf(stderr, "Failed to start shell\n");
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return SSH_ERROR;
    }

    
    char buffer[256];
    int nbytes;
    
    while (ssh_channel_is_open(channel) &&
           !ssh_channel_is_eof(channel)) {
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        if (nbytes < 0) {
            fprintf(stderr, "Error reading channel\n");
            ssh_channel_close(channel);
            ssh_channel_free(channel);
            return SSH_ERROR;
        }
        
        if (nbytes > 0) {
            write(1, buffer, nbytes);
        }
    }

    
    ssh_channel_close(channel);
    ssh_channel_free(channel);

    return SSH_OK;
}

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
    /*if (argc != 4) {
        fprintf(stderr, "Использование: %s <host> <port> <users_file>\n", argv[0]);
        return 1;
    }*/
    
    int result = authSSH(MAX_ATTEMPTS);
    /*ssh_session my_ssh_session;
    my_ssh_session = ssh_new();*/
    if (result == 0) {
        printf("Authentication successful. Exiting...\n");
        exit(0);
    } else {
        printf("Authentication failed. Exiting with error code %d\n", result);
        exit(1);
    }
   
    return 0;
}
