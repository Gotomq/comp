/*
gcc eg-C.c -o bin
./bin <filename> <action> <shifts>
----------------------------------
Ivan B. UNSA
*/

#include "cesar-ci/cesar.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// #define LMAX 255

int isNumber(char *str) {
    if (!str[0]) return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int main(int argc, char **argv){

    if (argc < 4){
        fprintf (stderr, "error: insufficient input, usage is: %s <filename> <'cipher' or 'decipher'> <shifts '0-9'>", argv[0]);
        return 0;
    }
    FILE *fp = NULL;            /* file pointer                     */
    FILE *out = NULL;           /* file pointer                     */
    int shift;                  /* shifts                           */
    char *action = NULL;        /* serves as a temporal             */
    

    if (!(fp = fopen (argv[1], "r"))) { /* open file for reading    */
        fprintf (stderr, "error: file open failed '%s'.\n", argv[1]);
        return 1;
    }
    if (!(!strcmp(argv[2],"cipher")  || !strcmp(argv[2],"decipher"))){
        fprintf (stderr, "error: not valid action '%s'.\n", argv[2]);
        return 1;
    }
    if (!isNumber(argv[3])){
        fprintf (stderr, "error: not valid shift number '%s'.\n", argv[3]);
        return 1;
    }
    action = (char*)calloc(10, sizeof(char)); //tmp variable for file.txt
    strcpy(action, argv[2]);

    sscanf(argv[3], "%d", &shift);
    printf("SHIFTs %d\n", shift);

    strcat(action, ".txt");
    out = fopen(action, "w"); /*creating output file*/

    if(strcmp(argv[2],"cipher") == 0){
        cipher(fp, out, shift);
    } else{
        decipher(fp, out, shift);
    }

    if (fp) fclose(fp);
    if (out) fclose(out);
    free(action);
    return 0;
}