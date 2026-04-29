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
#include <sys/wait.h>
#include <netinet/ip.h>


#include "proc_Multicast_UDP.h"


void proc_Multicast_UDP(){

    /*MULTICAST Joueur <-> Serveur*/
    
    // création de la socket UDP Multicast
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

    // autorisation de réutiliser le port (pour le fonctionnement multicast)
    int reuse = 1;
    setsockopt(socket_multicast_joueur, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // adresse locale du multicast
    bzero((char *) &ad_multicast, sizeof(ad_multicast));
    ad_multicast.sin_family = AF_INET;
    ad_multicast.sin_addr.s_addr = htonl(INADDR_ANY);
    ad_multicast.sin_port = htons(1234);

        
    if (bind(socket_multicast_joueur, (struct sockaddr *)&ad_multicast,sizeof(struct sockaddr_in)) < 0) {
        perror("bind multicast serveur");
        return;
    }

    // abonnement de la socket au groupe multicast
    setsockopt(socket_multicast_joueur, IPPROTO_IP, IP_ADD_MEMBERSHIP,&gr_multicast, sizeof(struct ip_mreq));





    // configuration pour l'envoie de messages : serveur --> clients (multicast)
    bzero((char *) &adresse, sizeof(adresse));
    adresse.sin_family = AF_INET;
    adresse.sin_addr.s_addr = ip.s_addr;
    adresse.sin_port = htons(1234);



    //Envoie de messages à jusqu'a que le message == 'q'
    char message_multicast[100] = "";
    while (strcmp(message_multicast, "q") != 0) {
        scanf("%s",message_multicast);
        sendto(socket_multicast_joueur, message_multicast, strlen(message_multicast), 0,(struct sockaddr*)&adresse, sizeof(adresse));
        if (strcmp(message_multicast, "q") == 0) printf("ARRET DU MULTICAST (SERVEUR)\n"); 
    }
}

void fermeture_proc_multi(){
}