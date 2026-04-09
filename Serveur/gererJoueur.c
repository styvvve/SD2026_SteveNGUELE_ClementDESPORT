#include "gererJoueur.h"

#define TAILLEBUF 100

void gererJoueur(int socket,int id_joueur) {
    int nb_octets;
    char *chaine_recue;


    char messages[100]; 
    snprintf(messages, sizeof(messages)/sizeof(char),"Bien connecté, Votre ID: %d",id_joueur);

    write(socket, messages, sizeof(messages)/sizeof(char)); 
    // la connexion est établie, on attend les données envoyées par le client
    nb_octets = read(socket, messages, TAILLEBUF);
    // affichage du message reçu
    chaine_recue = (char *)malloc(nb_octets * sizeof(char));
    memcpy(chaine_recue, messages, nb_octets);
    printf("ID:%d Message recu:%s\n", id_joueur,chaine_recue);

    while(strcmp(chaine_recue,"q")!=0){
        nb_octets = read(socket, messages, TAILLEBUF);
        chaine_recue = (char *)malloc(nb_octets * sizeof(char));
        memcpy(chaine_recue, messages, nb_octets);
        printf("ID[%d] : %s\n",id_joueur,chaine_recue);
    }

    printf("ID:%d C'est déconnecté.", id_joueur);
}