#ifndef PROC_ADMIN_UDP_H
#define PROC_ADMIN_UDP_H

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


void proc_Admin_UDP(int *pipe_tcp_admin, bool *joueurconnecte,char *argv[]);
void fermeture_proc_admin();

#endif