/*
gcc eg-D.c data-structures/vector.c -o bin
./bin <filename>
------------------------------------------
Ivan B. UNSA
*/
#include "analyzer/analize-scipt.h"
#include "data-structures/vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LMAX 255

int main(int argc, char **argv){

    if (argc < 2){
        fprintf (stderr, "error: insufficient input, usage is: %s <filename>", argv[0]);
        return 0;
    }

    FILE *fp = NULL;            /* file pointer                     */
    FILE *out = NULL;           /* file pointer                     */
    char *str = NULL;           
    int lmax = LMAX;            
    
    if (!(fp = fopen (argv[1], "r"))) { /* open file for reading    */
        fprintf (stderr, "error: file open failed '%s'.\n", argv[1]);
        return 1;
    }
    out = fopen("out-file-D.txt", "w");
    str = (char*)malloc(lmax*sizeof(char));
    vector v;
    vector_init(&v);
    analizeFile(fp, &str, lmax, &v);

    char* tmpstr = (char*) calloc (lmax, sizeof(char));
    
    for (int i = 0; i < vector_total(&v); i++){
        strcpy(tmpstr, (char *) vector_get(&v, i));
        if (i+1 != vector_total(&v)) strcat(tmpstr, "\n");
        printf("%s", tmpstr);
        fputs(tmpstr, out);
    }
    printf("\n");
    free(tmpstr);
    if (fp) fclose(fp);
    if (out) fclose(out);
    free(str);
    vector_free(&v);
    return 0;
}