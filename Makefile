SOURCE_FILES = main.c

OUT	= journyShell 
CC	 = gcc
FLAGS	 = -ansi

all: $(OBJS)
	$(CC) $(FLAGS) -o $(OUT) $(SOURCE_FILES)

clean:
	rm -f $(OBJS) $(OUT)
