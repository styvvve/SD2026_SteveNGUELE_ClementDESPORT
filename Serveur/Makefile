CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =
LIBS = 



SRC = Joueur/gererJoueur.c \
	  Admin/gererAdmin.c \
	  serveur.c \
	  Socket/socket.c \
	  Processus/proc_Admin_UDP.c \
	  Processus/proc_TCP.c \
	  Processus/proc_Multicast_UDP.c 


OBJ = $(SRC:.c=.o)

TARGET = server

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
