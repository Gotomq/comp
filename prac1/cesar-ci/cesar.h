#ifndef _CESAR_H
#define _CESAR_H
#include <stdio.h>
#include <stdlib.h>

void cipher(FILE *in, FILE *out, int shift){
    printf("CIPHERING\n");
    char ch = fgetc(in);
    while (ch != EOF){
        if(!(ch == '\n' || ch == ' ' || ch == '\t'))
            fputc(ch+shift, out);
        else 
            fputc(ch, out);
        ch = fgetc(in);
    }
}
void decipher(FILE *in, FILE *out, int shift){    
    char ch = fgetc(in);
    printf("DECIPHERING\n");
    while (ch != EOF){
        if(!(ch == '\n' || ch == ' ' || ch == '\t'))
            fputc(ch-shift, out);
        else 
            fputc(ch, out);
        ch = fgetc(in);
    }
}

#endif