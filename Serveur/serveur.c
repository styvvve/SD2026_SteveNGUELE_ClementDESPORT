#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include "socket.c"
#define TAILLEBUF 20


int main(int argc, char* argv[]) {
    // adresse de la socket locale
    static struct sockaddr_in addr_local;
    // adresse de la socket coté serveur (réponse admin)
    static struct sockaddr_in addr_admin;
    // identifiant de l'admin
    struct hostent *host_admin;
    // taille de l'addresse socket
    socklen_t lg;
    // descripteur de la socket locale pour l'UDP admin
    int socket_admin;
    // chaine à envoyer en réponse
    char *reponse = "bien recu";
    // buffer de réception
    char buffer[TAILLEBUF];
    // chaine reçue
    char *chaine;
    // nombre d'octets lus ou envoyés
    int nb_octets;

    // Crée la socket pour relié l'administrateur et le serveur en UDP pour configuration partie via le port mis en paramètres dans l'execution du prog. (argv[1])
    socket_admin = creerSocketUDP_Administrateur(atoi(argv[1]));

    // Vérifie si la socket à une erreur
    if (socket_admin == -1) {
        perror("erreur création socket");
        exit(1);
    }

    /*ToDo : Relier avec admin et configurer partie par rapport aux "messages" reçu par l'admin*/
    /*ToDo : Réfléchir à la façon dont l'admin configure la partie (exemple :  1- choisir mode, 2- choisir temps, 3-...)*/
    /*ToDo : Envoie en temps réelle l'évolution de la partie (score,connexion/deconnexion...)*/
    close(socket_admin);


    /*
    TP1 pour s'aider

    // attente de données venant d'un client
    lg = sizeof(struct sockaddr_in);
    nb_octets = recvfrom(sock, buffer, TAILLEBUF, 0,(struct sockaddr *)&addr_client, &lg);
    if (nb_octets == -1) {
        perror("erreur réception paquet");
        exit(1);
    }
    // récupère nom de la machine émettrice des données
    host_client = gethostbyaddr(&(addr_client.sin_addr), sizeof(long), AF_INET);
    if (host_client == NULL) {
        perror("erreur gethostbyaddr");
        exit(1);
    }
    // affichage message reçu et coordonnées émetteur
    chaine = (char *)malloc(nb_octets * sizeof(char));
    memcpy(chaine, buffer, nb_octets);
    printf("recu message %s de la part de %s sur le port %d\n", chaine, host_client->h_name, ntohs(addr_client.sin_port));
    
    // envoi de la réponse à l'émetteur
    nb_octets = sendto(sock, reponse, strlen(reponse)+1, 0,(struct sockaddr*)&addr_client, lg);
    if (nb_octets == -1) {
        perror("erreur envoi réponse");
        exit(1);
    }
    // fermeture la socket
    close(sock); 
    
    */
}