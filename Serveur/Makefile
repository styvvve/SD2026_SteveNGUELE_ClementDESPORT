CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =
LIBS = 



SRC = gererJoueur.c \
	  gererAdmin.c \
	  serveur.c \
	  socket.c \
	  processus/proc_Admin_UDP.c \
	  processus/proc_TCP.c \
	  processus/proc_Multicast_UDP.c 


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
