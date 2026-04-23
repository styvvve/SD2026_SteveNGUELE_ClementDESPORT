#include "gererAdmin.h"

#define TAILLEBUF 100

void gererJoueur(int socket) {
    // affichage message reçu et coordonnées émetteur
    chaine = (char *)malloc(nb_octets_admin * sizeof(char));
    memcpy(chaine, buffer, nb_octets_admin);
    printf("recu message %s de la part de %s sur le port %d\n", chaine, host_client->h_name, ntohs(addr_client.sin_port));
    
    // envoi de la réponse à l'émetteur
    nb_octets_admin = sendto(sock, reponse, strlen(reponse)+1, 0,(struct sockaddr*)&addr_client, lg);
    if (nb_octets == -1) {
        perror("erreur envoi réponse");
        exit(1);
    }
}