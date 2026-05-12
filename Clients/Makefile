CC = gcc
CFLAGS = -Wall -g
LDFLAGS =
LIBS = 



SRC = connexionTCP.c \
	connexionMulticastUDP.c \
	main.c 


OBJ = $(SRC:.c=.o)

TARGET = player

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

