#include "socket.h"

/* 
    *** 
    Créé socket UDP pour liaison entre: Serveur <---> Administrateur.
    Serveur(port) == Administrateur(port).
    Configuration avec (int argc, char* argv[]).
    Connexion Unicast.
    ***
*/
int creerSocketUDP_Administrateur (int port){
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    static struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr)); // initialise zone mémoire
    addr.sin_family = AF_INET; // IPv4
    addr.sin_port = htons(port); // port à lier à la socket ; 0 = n’importe quel port libre
    // N’importe quelle IP de la machine (si plusieurs) ; évite de connaître l’adresse IP locale
    addr.sin_addr.s_addr = INADDR_ANY;
    // Liaison du socket à l'adresse
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("Erreur lors de la liaison du socket à l'adresse");
        close(sockfd);
        return -1;
    }
    return sockfd;
}

