#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>


#define TAILLEBUF 1024


/**
 * codes clients 
 * Faire passer nom machine serveur et port distant
 */
int main(int argc, char *argv[]) {

    static struct sockaddr_in server_addr; 

    struct hostent *server_host; 

    int sock; 

    char *tesst = "Hello, World"; 

    char reponse[TAILLEBUF]; 

    int nb_octets; 

    sock = socket(AF_INET, SOCK_STREAM, 0); 

    if (sock == -1) {
        perror("ERROR during socket creation"); 
        exit(1); 
    } 

    server_host = gethostbyname("scinfe173"); 
    if (server_host == NULL) {
        perror("Error : server adress recovering\n"); 
        exit(1); 
    }

    bzero((char *) &server_addr, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(2001); 

    memcpy(&server_addr.sin_addr.s_addr,
            server_host->h_addr, 
            server_host->h_length); 

    
    //connexion 
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1) {
        perror("error server connection"); 
        exit(1); 
    }

    nb_octets = write(sock, tesst, strlen(tesst)+1); 

    nb_octets = read(sock, reponse, TAILLEBUF); 

    printf("reponse recue : %s\n", reponse); 

    char test[100]; 
    while (strcmp(test, "q") != 0) {
        printf("communiction tjrs en cours\n"); 
        scanf("%s", test);
        
        write(sock, test, strlen(test)+1); 
        
        if (strcmp(test, "q") != 0) printf("message envoye\n"); 
    }

    close(sock);

}