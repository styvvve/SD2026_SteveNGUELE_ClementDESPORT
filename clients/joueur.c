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
#include <signal.h>


#define TAILLEBUF 1024

//Fonction pour fermer la socket multicast (pour pas recevoir les message multicast si on c'est déco)
/*
void fermeture_socket_multicast(){

}
*/

/**
 * codes clients 
 * Faire passer nom machine serveur et port distant
 */

int main(int argc, char *argv[]) {

    int TEST_multi=0;

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

    pid_t pid_multicast = fork();

    //TODO : FAIRE LE LIEN AVEC TCP (parce que pour l'instant si on quitte le tcp, le multicast fonctionne encore)
    if (pid_multicast == 0) {
        //Reception des messages MULTICAST du serveur
        char message_multicast[100];
        
        while (strcmp(message_multicast, "q") != 0) {
            int n = recvfrom(sock_udp, message_multicast, sizeof(message_multicast), 0, NULL, 0);
            if (n > 0) {
                message_multicast[n] = '\0';
                printf("%s\n", message_multicast);
                if (strcmp(message_multicast, "q") == 0){
                    printf("ARRET DU MULTICAST PAR LE SERVEUR");
                    break;
                }
            }
        }
        //quitte le groupe multicast
        printf("Fin du multicast.");
        setsockopt(sock_udp, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
        close(sock_udp);
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

    server_host = gethostbyname("STPDUBINF2623"); 
    if (server_host == NULL) {
        perror("Error : server adress recovering\n"); 
        exit(1); 
    }

    bzero((char *) &server_addr, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(2001); 

    memcpy(&server_addr.sin_addr.s_addr,server_host->h_addr, server_host->h_length); 

    
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
        printf("communication tjrs en cours\n"); 
        scanf("%s", test);
        
        write(sock, test, strlen(test)+1); 
        
        if (strcmp(test, "q") == 0){
            printf("message de fin envoye\n");
            kill(pid_multicast, SIGTERM);
        }
    }

    close(sock);
}
