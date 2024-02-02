CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -pthread
DEBUG_FLAGS = -g

SRC = threadpool.c main.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = my_threadpool

# 默认编译规则
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# 调试编译规则
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

# 清理规则
clean:
	rm -f $(OBJ) $(EXECUTABLE)

# 隐含规则，用于生成 .o 文件
%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: all debug clean
