SOURCE_FILES = main.c myls.c

CC	 = gcc
FLAGS	 = -ansi

all: $(OBJS)
	$(CC) $(FLAGS) -o journyShell main.c

myls: $(OBJS)
	$(CC) $(FLAGS) -o myls myls.c

clean:
	rm -f myls journyShell
