all: basicgame

CC = g++
CFLAGS = -lGL -lglfw -ldl

BIN = basicgame
OBJS = basicgame.o

$(BIN):: $(OBJS)
	$(CC) -o $(BIN) $(OBJS) glad.c $(CFLAGS)

basicgame.o::classes.h resources.h 


clean::
	/bin/rm -f *~ *.o