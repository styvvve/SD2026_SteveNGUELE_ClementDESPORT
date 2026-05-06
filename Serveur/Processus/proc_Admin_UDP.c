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
#include <stdbool.h>


#include "../Socket/socket.h"

#include "../Admin/gererAdmin.h"

#include "proc_Admin_UDP.h"


void proc_Admin_UDP(int *pipe_tcp_admin, bool *joueurconnecte,char *argv[]){
    // UDP Unicast ADMINISTRATEUR

    // descripteur de la socket locale pour l'UDP admin
    int socket_admin;

    socket_admin = creerSocketUDP_Administrateur(atoi(argv[2])); //Port a changer 

    // Vérifie si la socket à une erreur
    if (socket_admin == -1) {
        perror("erreur création socket");
        exit(1);
    }


    //Dans fichier : "gererAdmin.c"
    gererAdmin(socket_admin,pipe_tcp_admin,joueurconnecte);

    // fermeture la socket
    close(socket_admin);
    exit(0); 


    close(socket_admin); 

}

void fermeture_proc_admin(){}