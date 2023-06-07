#include "../include/my_mouse.h"

//check same characters
bool check_same_characters(struct maze* mz) {

	if (mz->wall_char == mz->empty_char || mz->wall_char == mz->step_char ||
		mz->wall_char == mz->enter || mz->wall_char == mz->exit ||

		mz->empty_char == mz->step_char || mz->empty_char == mz->enter ||
		mz->empty_char == mz->exit ||

		mz->step_char == mz->enter || mz->step_char == mz->exit ||

		mz->enter == mz->exit)
	{
		return false;
	}

	return true;
}

//check maze characters
bool check_maze_characters(struct maze* mz) {

	int  countEnter = 0, countExit = 0;

	//check maze
	for (int i = 0; i < mz->rows; i++) {
		for (int n = 0; n < mz->columns; n++) {
			if (mz->maze[i][n] != mz->wall_char && mz->maze[i][n] != mz->empty_char &&
				mz->maze[i][n] != mz->step_char && mz->maze[i][n] != mz->enter && mz->maze[i][n] != mz->exit) {
				return false;
			}

			if (mz->maze[i][n] == mz->enter)
			{
				countEnter += 1;
			}

			if (mz->maze[i][n] == mz->exit)
			{
				countExit += 1;
			}
		}
	}

	return countEnter == 1 && countExit == 1; //no enter or no exit or many enters, many exits
	
}

//TODO check that entry and exit characters differ
//from each other, as well as from all other characters
//also, check for null characters
bool check_chars(struct maze* mz) {

	//check null
	if (mz->wall_char == '\0' || mz->step_char == '\0' ||
		mz->empty_char == '\0' || mz->enter == '\0' ||
		mz->exit == '\0')
	{
		return false;
	}

	//check same characters
	if (!check_same_characters(mz))
	{
		return false;
	}

	//check maze characters
	return check_maze_characters(mz);
}

//extract number of rows
int handle_num_rows(char line[], struct maze* mz) {

	char rows[5];
	int i = 0;

	while (i < 4 && line[i] != 'x' && line[i] != '\0' && (line[i] >= '0' && line[i] <= '9')) {
		rows[i] = line[i];
		i++;
	}
	rows[i] = '\0';

	if (line[i] != 'x')
	{
		return false;
	}
	i += 1; // skip 'x'
	mz->rows = my_atoi(rows);

	return i;
}

//extract number of cols
int handle_num_cols(char line[], struct maze* mz, int pos) {

	char columns[5];

	int n = 0;
	while ((line[pos] >= '0' && line[pos] <= '9') && pos < 9) {
		columns[n] = line[pos];
		pos++; n++;
	}
	columns[n] = '\0';
	mz->columns = my_atoi(columns);

	return pos;
}

//TODO implement function to check that labyrinth doesn't have missing chars
//that all the walls are there, basically, but also, 
//enter and exit chars are there, and there's only one of them respectively
//iterate through the exterior of the maze, check that every char is labyrinth char, or entrance, or exit
//keep counter for entrance and exit, if it's more than 1 each, return error


//sends maze struct pointer to be allocated
//draws data from map file
bool handle_first_line(int fd, struct maze* mz, char firstLine[]) {
	
	char line[14]; //maximum chars allowed for first line
	int i = 0;

	//empty line
	int j;
	for (j = 0; j < 14; j++)
	{
		line[i] = '\0';
	}
	read(fd, &line, sizeof(line));	
	
	i = handle_num_rows(line, mz); //extract rows
	i = handle_num_cols(line, mz, i);  //extract cols

	if (mz->rows <= 0 || mz->columns <= 0 || 
		mz->rows * mz->columns > 1000) {

		return false;
	}

	mz->wall_char = line[i++];
	mz->empty_char = line[i++];
	mz->step_char = line[i++];
	mz->enter = line[i++];
	mz->exit = line[i++];

	//copy fist line
	my_strncpy(firstLine, line, i);

	return true;
}

//writes maze into char **array, and puts it in the maze struct
bool get_maze(int fd, struct maze* mz) {
	char c = '\0';
	while (c != '\n') read(fd, &c, 1); //skip the first line
	int rows = mz->rows;
	int columns = mz->columns;

	char** maze = (char**)malloc(rows * sizeof(char*));

	for (int i = 0; i < rows; i++) {
		maze[i] = malloc(columns * sizeof(char));
	}

	for (int i = 0; i < rows; i++) {
		for (int n = 0; n < columns; n++) {
			if (read(fd, &c, 1) != 1) {
				return false;
			}
			maze[i][n] = c;

			if (mz->enter == c)
			{
				mz->enterRow = i;
				mz->enterCol = n;
			}
			if (mz->exit == c)
			{
				mz->exitRow = i;
				mz->exitCol = n;
			}
		}

		//read \n
		read(fd, &c, 1);
	}

	mz->maze = maze;

	return true;
}

//print maze
void print_maze(int rows, int columns, char** maze) {
	for (int i = 0; i < rows; i++) {
		for (int n = 0; n < columns; n++) {
			printf("%c", maze[i][n]);
		}
		printf("\n");
	}
}

//free maze
void free_maze(int size, char** maze) {
	
	for (int i = 0; i < size; i++) {
		free(maze[i]);
	}

	free(maze);
}