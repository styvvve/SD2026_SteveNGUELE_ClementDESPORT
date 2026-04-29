#include "gererAdmin.h"
#include <sys/wait.h>

#define TAILLEBUF 100

void gererAdmin(int socket,int *pipe_tcp_admin) {

    int nb_octets_admin;
    char *chaine;
    char *message = "Bjr";
    socklen_t lg;
    char buffer[TAILLEBUF]; 

    char message_recu_pipe[100];
    


    // adresse de la socket coté admin
    static struct sockaddr_in addr_admin;
    struct hostent *host_admin;
    // descripteur de la socket locale pour l'UDP admin

    lg = sizeof(struct sockaddr_in); 

    nb_octets_admin = recvfrom(socket, buffer, TAILLEBUF, 0,(struct sockaddr *)&addr_admin, &lg);
    if (nb_octets_admin == -1) {
        perror("erreur réception paquet");
        exit(1);
    }
    // récupère nom de la machine émettrice des données
    host_admin = gethostbyaddr(&(addr_admin.sin_addr), sizeof(long), AF_INET);
    if (host_admin == NULL) {
        perror("erreur gethostbyaddr");
        exit(1);
    }

    read(pipe_tcp_admin[0],message_recu_pipe,100);

    // envoi de la réponse à l'émetteur
    nb_octets_admin = sendto(socket, message_recu_pipe, strlen(message_recu_pipe)+1, 0,(struct sockaddr*)&addr_admin, lg);
    if (nb_octets_admin == -1) {
        perror("erreur envoi réponse");
        exit(1);
    }

    // affichage message reçu et coordonnées émetteur
    chaine = (char *)malloc(nb_octets_admin * sizeof(char));
    memcpy(chaine, buffer, nb_octets_admin);
    printf("recu message %s sur le port %d\n", chaine, ntohs(addr_admin.sin_port));

    free(chaine); 
}