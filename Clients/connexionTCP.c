#include "connexionTCP.h"


int socket_TCP() {
    int sock = socket(AF_INET, SOCK_STREAM, 0); 

    if (sock == -1) {
        perror("Error during socket creation\n"); 
        printf("Error description : %s\n", strerror(errno)); 
        return sock; 
    }
    return sock; 
}

int connexion_TCP(int socket, char* server_name, int server_port) {
    static struct sockaddr_in server_addr; 
    struct hostent *server_host; 
    server_host = gethostbyname(server_name); 

    if (server_host == NULL) {
        perror("Error during server address recovering\n"); 
        printf("Error description : %s\n", strerror(errno)); 
        return 1; 
    }

    bzero((char *) &server_addr, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(server_port); 
    memcpy(&server_addr.sin_addr.s_addr, server_host->h_addr, server_host->h_length);

    //connexion
    if (connect(socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1) {
        perror("Server connection error\n"); 
        printf("Error description : %s\n", strerror(errno)); 
        return 1; 
    }

    return 0; 
}
