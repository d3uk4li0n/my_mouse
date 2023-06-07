#include "../include/my_mouse.h"

int main(int argc, char **argv){
    if(argc < 2){
        printf("maze file needed\n");
        return -1;
    }

    struct maze mz;
    int fd = open_file(argv[1]);
    if (fd == -1) {
        printf("MAP ERROR\n");
        return -1;
    }

    char line[14]; //maximum chars allowed for first line

    if (!handle_first_line(fd, &mz, line)) {
        printf("MAP ERROR\n");
        //close file
        close_file(fd);
        return 0;
    }

    //close file
    close_file(fd);

    //open again
    fd = open_file(argv[1]);
    if (fd == -1) return -1;

    //read maze
    if (!get_maze(fd, &mz)) {
        printf("MAP ERROR\n");
    }
    else {

        int numSteps = 0; //number of steps

        if (!check_chars(&mz)) //check error characters 
        {
            printf("MAP ERROR\n");
        }
        else  if (!my_mouse(&mz, &numSteps)) //find path
        {
            printf("MAP ERROR\n");
        }
        else {
            printf("%s\n", line);
            print_maze(mz.rows, mz.columns, mz.maze);
            printf("%d STEPS!\n", numSteps);
        }
    }

    //free matrix
    free_maze(mz.rows, mz.maze);

    //close file
    close_file(fd);

    return 0;
}