#ifndef PROC_TCP_H
#define PROC_TCP_H

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

#include "../structure_partage.h"


void proc_TCP(int *pipe_tcp_admin, struct_partage *variablePartage, char *argv[]);

#endif