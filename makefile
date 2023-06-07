CC=gcc
OBJ+=src/my_mouse.o src/main.o src/maze_handle.o src/utils.o
DEPS+=include/maze.h\
		include/my_mouse.h
CFLAGS+=-Wall -Werror -Wextra -g3 -fsanitize=address
TARGET=my_mouse

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

.PHONY: all clean re fclean
clean:
	rm -f src/*.o 

fclean: clean
	rm $(TARGET)

re: fclean all