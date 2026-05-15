#include "gererJoueur.h"

#define TAILLEBUF 100


void gererJoueur(int socket,int id_joueur, int *pipe_tcp_admin) {

    //gestion pipe
    close(pipe_tcp_admin[0]);

    char messages[100]; 


    
    char message_pipe_connexion[100];
    snprintf(message_pipe_connexion,sizeof(message_pipe_connexion)/sizeof(char),"addPlayer|%d",id_joueur);

    write(pipe_tcp_admin[1],message_pipe_connexion,strlen(message_pipe_connexion));

    write(socket, messages, sizeof(messages)/sizeof(char)); 
    // la connexion est établie, on attend les données envoyées par le client

    
    int nb_octets;

    char message[100];
    char message_recu_client[100];
    while(1){
        nb_octets = read(socket, message_recu_client, TAILLEBUF);
        if (nb_octets > 0){
            printf("Message reçu du client :%s\n", message_recu_client);
            char *p = strtok(message_recu_client,"|");
            if (p && strcmp(p,"quit")==0){
                printf("TEST DECO\n");
                char message_pipe_deconnexion[100];
                snprintf(message_pipe_deconnexion,sizeof(message_pipe_deconnexion)/sizeof(char),"removePlayer|%d",id_joueur);
                write(pipe_tcp_admin[1],message_pipe_deconnexion,strlen(message_pipe_deconnexion));
                break;
            }
            if (p && strcmp(p,"test")==0){
                snprintf(message,sizeof(message)/sizeof(char),"OK");
                write(socket, message, sizeof(message)/sizeof(char));
            }else{
                printf("%s\n",p);
            }
        }
        if (nb_octets==0){
            printf("Joueur deco\n");
            char message_pipe_deconnexion[100];
            snprintf(message_pipe_deconnexion,sizeof(message_pipe_deconnexion)/sizeof(char),"removePlayer|%d",id_joueur);
            write(pipe_tcp_admin[1],message_pipe_deconnexion,strlen(message_pipe_deconnexion));
            break;
        }
    }
}