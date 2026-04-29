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

#include "gererAdmin.h"
#include "socket.h"
#include "gererJoueur.h"

#include "processus/proc_Multicast_UDP.h"
#include "processus/proc_Admin_UDP.h"
#include "processus/proc_TCP.h"


#define TAILLEBUF 100


void fermeture_processus(){
    fermeture_proc_admin();
    fermeture_proc_multi();
    fermeture_proc_tcp();
}

int main() {

    /*Creation Pipe*/
    int pipe_tcp_admin[2];

    if (pipe(pipe_tcp_admin) == -1){
        perror("Erreur durant la création de pipe");
        exit(1);
    }

    /*signaux pour fermer les sockets lors de l'arret d'un programme pr qu'ils restent pas ouverts et occupent un processus*/
    //signal -> func qui ferme toutes les sockets ouvertes

    pid_t pid_proc_Admin_UDP = fork();
    if (pid_proc_Admin_UDP==0){
        proc_Admin_UDP(pipe_tcp_admin);
        exit(0);
    }


    pid_t pid_proc_TCP = fork();
    if (pid_proc_TCP==0){
        proc_TCP(pipe_tcp_admin);
        exit(0);
    }

    pid_t pid_proc_Multicast_UDP = fork();
    if (pid_proc_Multicast_UDP==0){
        proc_Multicast_UDP();
        exit(0);
    }


    while(1){}

}