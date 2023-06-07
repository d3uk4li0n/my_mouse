#include "../include/my_mouse.h"

int open_file(char *fname){
    int fd = open(fname, O_RDONLY);
    if(fd == -1){
        return -1;
    }
    return fd;
}

int close_file(int fd){
    if(close(fd) == -1){
        printf("error closing maze file\n");
        return -1;
    }
    return 0;
}

int my_strlen(char *s){
    int i = 0;
    if(s == NULL) return -1;

    while(s[i] != '\0') i++;

    return i;
}

char *my_strncpy(char *dst, char *src, size_t n){
    size_t i;

    for(i=0;i<n && src[i] != '\0';i++) dst[i] = src[i];
    
    dst[i] = '\0';
    return dst;
}

char *my_strcpy(char *src, char *dst){
    return my_strncpy(dst, src, (size_t)my_strlen(src));
}

int my_atoi(char *string){
    int conv = 0, sign = 1;

    if(*string == '-'){ //can be negative
        sign = -1;
        string++;
    }else if (*string == '+'){ //can contain +         
        string++;
    }

    while(*string != '\0'){
        conv = conv * 10 + (*string - '0');
        string++;
    }
    return conv * sign;
}