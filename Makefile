CC = gcc
CFLAGS = -std=c11 -pthread
DEBUG_FLAGS = -g

SRC = threadpool.c main.c
OBJ = $(SRC:.c=.c)
EXECUTABLE = my_threadpool

# default compile rule
all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# debug compile rule
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

# clean rule
clean:
	rm -f $(EXECUTABLE)
