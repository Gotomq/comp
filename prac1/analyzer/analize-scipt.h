#ifndef ANALIZE_SCRIPT_H
#define ANALIZE_SCRIPT_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include "../data-structures/vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isNumber(char *str) {
    if (!str[0]) return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}
int isSpecial(char *str) {
    if (!str[0]) return 0;
    for (int i = 0; str[i]!='\0'; i++) {
        if (str[i] == '+' || 
            str[i] == '-' ||  
            str[i] == '*' ||
            str[i] == '/' )
            return 1;
    }
    return 0;
}
int isWord(char *str) {
    if (!str[0]) return 0;
    for (int i = 0; str[i]!='\0'; i++) {
        if (!(('a'<=str[i] && str[i]<='z') || 
            ('A'<=str[i] && str[i]<='Z'))) return 0;
    }
    return 1;
}

void printInfo(char *str){
    printf("INFO " ANSI_COLOR_YELLOW "'%s'" ANSI_COLOR_RESET " length: %u\n", str, strlen(str));
    printf("NUMBER  : %s\n", isNumber(str) ? ANSI_COLOR_GREEN "yes" ANSI_COLOR_RESET: 
                                             ANSI_COLOR_RED "no" ANSI_COLOR_RESET);
    printf("SPECIAL : %s\n", isSpecial(str) ? ANSI_COLOR_GREEN "yes" ANSI_COLOR_RESET : 
                                              ANSI_COLOR_RED "no" ANSI_COLOR_RESET);
    printf("WORD    : %s\n", isWord(str) ? ANSI_COLOR_GREEN "yes" ANSI_COLOR_RESET: 
                                           ANSI_COLOR_RED "no" ANSI_COLOR_RESET);
}

char* allocStr(char *str) {
    char *tmp = (char*) malloc( strlen(str) * sizeof(*str));
    strcpy(tmp, str);
    return tmp;  
}

void analizeFile(FILE* in, char** str, int maxsize, vector* info_vec){
    printf("ANALIZING ...\n");
    char ch = fgetc(in);
    int sc = 0;
    char *vecElem = NULL;
    while (ch != EOF) {
        if(!(ch == '\n' ||
            ch == '\t'  ||
            ch == ' ')){
            if (sc < maxsize){
                (*str)[sc] = ch;
                sc++;
            } else {
                *str = (char*) realloc (*str, maxsize * 2 * sizeof(**str) );
                maxsize*=2;
            }
        } else {      
            if ((*str)[0] != 0) {
                printInfo(*str); //special case null
                vecElem = allocStr(*str);
                vector_add(info_vec, vecElem);
            }
            memset(*str, 0, strlen(*str));
            sc = 0;
        }
        ch = fgetc(in);
    }
    if((*str)[0] != 0) {
        printf("%s\n", *str);
        vecElem = allocStr(*str);
        printInfo(*str);
        vector_add(info_vec, vecElem);
    }
}

#endif