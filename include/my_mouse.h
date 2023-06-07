#include "maze.h"

#ifndef MY_MOUSE_H
#define MY_MOUSE_H

#define INF 100000 //infinite
#define MAX_STEPS 1000 //max steps

bool my_mouse(struct maze*, int*);

#endif

#ifndef MAZE_HANDLE_H
#define MAZE_HANDLE_H

bool handle_first_line(int, struct maze *, char[]);

//extract number of rows
int handle_num_rows(char[], struct maze*);

//extract number of cols
int handle_num_cols(char[], struct maze*, int);

bool check_chars(struct maze *);

//check same characters
bool check_same_characters(struct maze*);

//check maze characters
bool check_maze_characters(struct maze*);

bool get_maze(int, struct maze *);
void print_maze(int, int, char **);
void free_maze(int, char **);

void my_mouse_move_helper(struct maze* mz, bool** visited, int row, int col,
	struct position minPath[], int* minDistance, struct position path[], int distance);

void my_mouse_helper(struct maze* mz, bool** visited, int row, int col,
	struct position minPath[], int* minDistance, struct position path[], int distance);

int calcNumSteps(struct maze* mz, int minDistance, struct position minPath[]);

#endif

#ifndef UTILS_H
#define UTILS_H

int open_file(char *);
int close_file(int);
int my_atoi(char *);
char *my_strncpy(char *, char *, size_t);
char *my_strcpy(char *, char *);

#endif