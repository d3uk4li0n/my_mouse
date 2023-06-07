#include "../include/my_mouse.h"

bool my_mouse_move_valid(struct maze* mz, bool** visited, int row, int col) {
	
	return row >= 0 && row < mz->rows && col >= 0 && col < mz->columns &&
		visited[row][col] == false &&
		(mz->maze[row][col] == mz->empty_char || 
			mz->maze[row][col] == mz->exit);
}

void my_mouse_move_helper(struct maze* mz, bool** visited, int row, int col,
	struct position minPath[], int* minDistance, struct position path[], int distance) {

	//move up
	if (my_mouse_move_valid(mz, visited, row - 1, col)) {
		path[distance].x = row - 1;
		path[distance].y = col;
		my_mouse_helper(mz, visited, row - 1, col, minPath, minDistance, path, distance + 1);
	}
	//move left
	if (my_mouse_move_valid(mz, visited, row, col - 1)) {
		path[distance].x = row;
		path[distance].y = col - 1;
		my_mouse_helper(mz, visited, row, col - 1, minPath, minDistance, path, distance + 1);
	}
	//move right
	if (my_mouse_move_valid(mz, visited, row, col + 1)) {
		path[distance].x = row;
		path[distance].y = col + 1;
		my_mouse_helper(mz, visited, row, col + 1, minPath, minDistance, path, distance + 1);
	}
	//move down
	if (my_mouse_move_valid(mz, visited, row + 1, col)) {
		path[distance].x = row + 1;
		path[distance].y = col;
		my_mouse_helper(mz, visited, row + 1, col, minPath, minDistance, path, distance + 1);
	}

}

void my_mouse_helper(struct maze* mz, bool** visited, int row,  int col, 
	struct position minPath[], int* minDistance, struct position path[], int distance) {

	//go to exit cell
	if (row == mz->exitRow && col == mz->exitCol) {
		if (*minDistance == 0 || *minDistance > distance) {

			*minDistance = distance;

			//copy path
			for (int i = 0; i < distance; i++)
			{
				minPath[i] = path[i];
			}
		}
	}
	else {

		//should not go further
		if (*minDistance > 0  && *minDistance <= distance)
		{
			return;
		}

		// visit it
		visited[row][col] = true;

		// move
		my_mouse_move_helper(mz, visited, row, col, minPath, minDistance, path, distance);

		//backtrack
		visited[row][col] = false;
	}
}

bool my_mouse(struct maze* mz, int* numSteps) {

	bool found = true;

	//create visited array
	bool** visited = malloc(sizeof(bool*) * mz->rows);
	for (int i = 0; i < mz->rows; i++){
		visited[i] = malloc(sizeof(bool) * mz->columns);
	}
	for (int i = 0; i < mz->rows; i++) {
		for (int n = 0; n < mz->columns; n++) {
			if (mz->maze[i][n] == mz->empty_char || mz->maze[i][n] == mz->exit) {
				visited[i][n] = false;
			}
			else {
				visited[i][n] = true;
			}
		}
	}

	int minDistance = 0;
	struct position minPath[MAX_STEPS];

	int distance = 0;
	struct position path[MAX_STEPS];
	
	my_mouse_helper(mz, visited, mz->enterRow, mz->enterCol, minPath,
		&minDistance, path, distance);

	if (minDistance == 0){ //solution not found
		found = false;
	}
	else {

		*numSteps = calcNumSteps(mz, minDistance, minPath);

		found = true;
	}

	//free resource
	for (int i = 0; i < mz->rows; i++) free(visited[i]);
	free(visited);

	return found;
}

int calcNumSteps(struct maze* mz, int minDistance, struct position minPath[]) {

	int steps = 0;

	//set path
	for (int i = 0; i < minDistance; i++){
		if (mz->maze[minPath[i].x][minPath[i].y] != mz->exit){
			mz->maze[minPath[i].x][minPath[i].y] = mz->step_char;

			steps += 1;
		}
	}
	return steps;
}
