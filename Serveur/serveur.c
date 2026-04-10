#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include "socket.c"
#include "gererJoueur.c"

#define TAILLEBUF 100


int main(int argc, char* argv[]) {
    // adresse de la socket locale
    static struct sockaddr_in addr_serveur_TCP_joueur;
    // adresse de la socket coté serveur (réponse admin)
    static struct sockaddr_in addr_admin;
    // identifiant de l'admin
    struct hostent *host_admin;
    // descripteur de la socket locale pour l'UDP admin
    int socket_admin;


    //Creation socket.. Multicast UDP
    struct in_addr ip;
    static struct sockaddr_in ad_multicast, adresse;
    struct ip_mreq gr_multicast;
    int socket_multicast_joueur;

    // création de la socket UDP
    socket_multicast_joueur = socket(AF_INET, SOCK_DGRAM, 0);
    // récupération adresse ip du groupe
    inet_aton("226.1.2.3",&ip);

    // création identificateur du groupe
    gr_multicast.imr_multiaddr.s_addr = ip.s_addr;
    gr_multicast.imr_interface.s_addr = htonl(INADDR_ANY);



    // abonnement de la socket au groupe multicast
    setsockopt(socket_multicast_joueur, IPPROTO_IP, IP_ADD_MEMBERSHIP,
    &gr_multicast, sizeof(struct ip_mreq));

    // autorise de lier plusieurs sockets sur le port utilisé par cette socket, c'est-à-dire sur le port du groupe multicast
    int reuse = 1;


    // liaison de la socket au port du groupe multicast
    bzero((char *) &adresse, sizeof(adresse));
    ad_multicast.sin_family = AF_INET;
    ad_multicast.sin_addr.s_addr = htonl(INADDR_ANY);
    ad_multicast.sin_port = htons(1234);
    bind(socket_multicast_joueur, (struct sockaddr *)&adresse, sizeof(struct sockaddr_in));


    // buffer de réception
    char buffer[TAILLEBUF];
    // chaine reçue
    char *chaine;
    // nombre d'octets lus ou envoyés
    int nb_octets;

    // descripteur de la socket locale pour TCP joueur
    int socket_ecoute, socket_service;

    // adresse de la socket coté serveur (réponse joueurs)
    static struct sockaddr_in addr_joueur;

    int lg;

    // port == 2001
    socket_ecoute = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *) &addr_serveur_TCP_joueur,sizeof(addr_serveur_TCP_joueur));


    addr_serveur_TCP_joueur.sin_family = AF_INET;
    addr_serveur_TCP_joueur.sin_port = htons(2001);

    if( bind(socket_ecoute,(struct sockaddr*)&addr_serveur_TCP_joueur,sizeof(addr_serveur_TCP_joueur))== -1 ) {
        perror("erreur bind socket écoute");
        exit(1);
    }


    if (socket_ecoute == -1){
        perror("Création de la socket service");
        exit (1);
    }

    if (listen(socket_ecoute,0)==-1){
        perror("Erreur Listen");
        exit (1);
    }

    signal(SIGCHLD, SIG_IGN);


    int id_joueur=0;

    char messages[100];
    snprintf(messages, sizeof(messages)/sizeof(char),"Test multicast");
    bzero((char *) &adresse, sizeof(adresse));
    adresse.sin_family = AF_INET;
    adresse.sin_addr.s_addr = ip.s_addr;
    adresse.sin_port = htons(1234);
    int longueur_adresse = sizeof(struct sockaddr_in);
    while(1){
        lg = sizeof(struct sockaddr_in);
        socket_service = accept(socket_ecoute,(struct sockaddr *)&addr_joueur, &lg);
        ++id_joueur;
        sendto(socket_multicast_joueur,messages, 100 , 0, (struct sockaddr*)&adresse, longueur_adresse);
        if (fork()==0){
            close (socket_ecoute);
            gererJoueur(socket_service,id_joueur);
            close(socket_service);
            exit(0);
        }
        close (socket_service);
    }



    // Crée la socket pour relié l'administrateur et le serveur en UDP pour configuration partie via le port mis en paramètres dans l'execution du prog. (argv[1])
    
    
/*    
    socket_admin = creerSocketUDP_Administrateur(atoi(argv[1]));

    // Vérifie si la socket à une erreur
    if (socket_admin == -1) {
        perror("erreur création socket");
        exit(1);
    }

    ToDo : Relier avec admin et configurer partie par rapport aux "messages" reçu par l'admin
    ToDo : Réfléchir à la façon dont l'admin configure la partie (exemple :  1- choisir mode, 2- choisir temps, 3-...)
    ToDo : Envoie en temps réelle l'évolution de la partie (score,connexion/deconnexion...)



    
    close(socket_admin);


    */


}