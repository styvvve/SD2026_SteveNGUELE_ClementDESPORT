#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>


#define TAILLEBUF 1024


/**
 * codes clients 
 * Faire passer nom machine serveur et port distant
 */
int main(int argc, char *argv[]) {

    /*MULTICAST*/

    // creation socket UDP pour le multicast
    int sock_udp = socket(AF_INET, SOCK_DGRAM, 0);

    // adresse locale
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(1234);

    // autorisation de réutiliser le port (pour le fonctionnement multicast)
    int reuse = 1;
    if (setsockopt(sock_udp, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("SO_REUSEADDR joueur client");
        exit(1);
    }

    if (bind(sock_udp, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind multicast joueur ");
        exit(1);
    }   

    // abonnement au groupe du multicast
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr("226.1.2.3");
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sock_udp, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        perror("Erreur abonnement multicast");
        exit(1);
    }

    if (fork() == 0) {
        // creation d'une boucle "infini" pour recevoir messages du serveur (multicast)
        char message[100];
        while (strcmp(message_multicast, "q") != 0) {
            int n = recvfrom(sock_udp, message, sizeof(message), 0, NULL, 0);
            if (n > 0) {
                message[n] = '\0';
                printf("%s\n", message);
                if (strcmp(message_multicast, "q") = 0){
                    printf("ARRET DU MULTICAST PAR LE SERVEUR");
                }
            }
        }
        exit(0);
    }

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

    server_host = gethostbyname("10.0.2.15"); 
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