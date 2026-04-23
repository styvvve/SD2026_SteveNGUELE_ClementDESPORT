#include "gererAdmin.h"

#define TAILLEBUF 100

void gererAdmin(int socket) {
    int nb_octets_admin;
    char *chaine;
    char *message = "Bjr";
    socklen_t lg;

    // adresse de la socket coté serveur (réponse admin)
    static struct sockaddr_in addr_admin;
    struct hostent *host_admin;
    // descripteur de la socket locale pour l'UDP admin

    nb_octets_admin = recvfrom(socket, setbuffer, TAILLEBUF, 0,(struct sockaddr *)&addr_admin, &lg);
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

    // envoi de la réponse à l'émetteur
    nb_octets_admin = sendto(socket, message, strlen(message)+1, 0,(struct sockaddr*)&addr_admin, lg);
    if (nb_octets_admin == -1) {
        perror("erreur envoi réponse");
        exit(1);
    }

    // affichage message reçu et coordonnées émetteur
    chaine = (char *)malloc(nb_octets_admin * sizeof(char));
    memcpy(chaine, setbuffer, nb_octets_admin);
    printf("recu message %s sur le port %d\n", chaine, ntohs(addr_admin.sin_port));
}