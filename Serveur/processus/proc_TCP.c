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


#include "../gererJoueur.h"

#include "proc_TCP.h"
    




void proc_TCP(int *pipe_tcp_admin){

    //TCP Joueur <-> Serveur
    
    // descripteur de la socket locale pour TCP joueur
    int socket_ecoute, socket_service;

    // adresse de la socket coté serveur (réponse joueurs)
    static struct sockaddr_in addr_joueur;
    static struct sockaddr_in addr_serveur_TCP_joueur;

    socklen_t lg;

    // port == 2001
    socket_ecoute = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *) &addr_serveur_TCP_joueur,sizeof(addr_serveur_TCP_joueur));


    addr_serveur_TCP_joueur.sin_family = AF_INET;
    addr_serveur_TCP_joueur.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serveur_TCP_joueur.sin_port = htons(2000);


    if (socket_ecoute == -1){
        perror("Création de la socket service");
        return;
    }

    if( bind(socket_ecoute,(struct sockaddr*)&addr_serveur_TCP_joueur,sizeof(addr_serveur_TCP_joueur))== -1 ) {
        perror("erreur bind socket écoute");
        return;
    }

    if (listen(socket_ecoute,5)==-1){
        perror("Erreur Listen");
        return;
    }

    signal(SIGCHLD, SIG_IGN);

    int id_joueur=0;

    while(1){
        lg = sizeof(struct sockaddr_in);
        socket_service = accept(socket_ecoute,(struct sockaddr *)&addr_joueur, &lg);
        ++id_joueur;
        if (fork()==0){
            close (socket_ecoute);
            gererJoueur(socket_service,id_joueur,pipe_tcp_admin);
            close(socket_service);
            exit(0);
        }
        close (socket_service);
    }
}



void fermeture_proc_tcp(){
}