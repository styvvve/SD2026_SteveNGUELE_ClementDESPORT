#include "gererJoueur.h"

#define TAILLEBUF 101


void test_connexion(int id_joueur,int socket){
    char *chaine_recue = "";
    int nb_octets;
    char *reponse ="";
    while (1)
    {
        chaine_recue = (char *)malloc(TAILLEBUF * sizeof(char));
        nb_octets = read(socket, chaine_recue, TAILLEBUF);
        if (strcmp(chaine_recue,"test")==0){
            reponse = "testOK";
            write(socket, reponse, strlen(reponse)+1);
        }
    }
    

}


void gererJoueur(int socket,int id_joueur, int *pipe_tcp_admin) {

    //gestion pipe
    close(pipe_tcp_admin[0]);

    //int nb_octets;
    int nb_octets;

    char *chaine_recue = "";


    char messages[100]; 
    snprintf(messages, sizeof(messages)/sizeof(char),"Bien connecté, Votre ID: %d",id_joueur);

    
    char message_pipe_connexion[100];
    snprintf(message_pipe_connexion,sizeof(message_pipe_connexion)/sizeof(char),"addPlayer|%d",id_joueur);

    write(pipe_tcp_admin[1],message_pipe_connexion,strlen(message_pipe_connexion));

    write(socket, messages, sizeof(messages)/sizeof(char)); 
    // la connexion est établie, on attend les données envoyées par le client


    printf("Joueur connecter");
    test_connexion(id_joueur,socket);
    while(strcmp(chaine_recue,"q")!=0){
        chaine_recue = (char *)malloc(TAILLEBUF * sizeof(char));
        nb_octets = read(socket, chaine_recue, TAILLEBUF);
        //memcpy(chaine_recue, messages, nb_octets);
        printf("ID[%d] : %s\n",id_joueur,chaine_recue);
    }




    char message_pipe_deconnexion[100];

    snprintf(message_pipe_deconnexion,sizeof(message_pipe_deconnexion)/sizeof(char),"removePlayer|%d",id_joueur);

    write(pipe_tcp_admin[1],message_pipe_deconnexion,strlen(message_pipe_deconnexion));
}