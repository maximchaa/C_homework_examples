/*
 Мне дается текст, например
 "klmdkmdm #define tmp 50 wqeqwe define re 49 weqwe undef tmp erq"
 
 я иду по тексту, ничего не делаю,
 встречаю #define tmp 50,
 как-то в коде закрепляю за tmp 50,
 иду по тексту, ничего не делаю,
 встречаю undef tmp,
 как-то в коде открепляю за tmp 50
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR 4000

void getWord(char whspace[], int* wh_len, char word[], int* word_len, int* next, FILE* in);

void getWord(char whspace[], int* wh_len, char word[], int* word_len, int* next, FILE* in)
/*
 Считывает все пробельные символы до слова в массив whspace, их длинну в wh_len,
 само слово в массив word, его длину в массив word_len,
 следующий символ в переменную next.
 */
{
    int c, old_vid = 0, vid, s_len = 0, w_len = 0;
    
    while (1 == 1)
    {
        c = fgetc(in);
        
        if (c == EOF || c == '\n')
            break;
        if ( (c == ' ') || (c == '\n') || (c == '\t') )
            vid = 0;
        else
            vid = 1;
        
        if (old_vid == 0 && vid == 0)
            whspace[s_len++] = c;
        if (old_vid == 0 && vid == 1)
            word[w_len++] = c;
        if (old_vid == 1 && vid == 1)
            word[w_len++] = c;
        if (old_vid == 1 && vid == 0)
        {
            *next = c;
            break;
        }
        old_vid = vid;
    }
    
    if (c == EOF || c == '\n')
        *next = c;
    whspace[s_len] = 0;
    word[w_len] = 0;
    *wh_len = s_len;
    *word_len = w_len;
}

struct defne
{
    char **name, **value;
};


int main(int argc, const char * argv[])
{
    int wh_len, word_len, next = 0, i, l;
    char *whspace, *word;
    struct defne define;
    FILE *in, *out;
    
    if ( (in = fopen("__path__/input.txt", "r")) == NULL )
    {
        printf("Can not open the file input.txt!\n");
        return -1;
    }
    if ( (out = fopen("__path__/output.txt", "w")) == NULL )
    {
        printf("Can not open the file output.txt!\n");
        fclose(in);
        return -1;
    }
    
    if ( (whspace = (char*)malloc( MAX_CHAR * sizeof(char) )) == NULL )
    {
        printf("Can not create the string whspace!\n");
        fclose(in);
        fclose(out);
        return -1;
    }
    if ( (word = (char*)malloc( MAX_CHAR * sizeof(char) )) == NULL )
    {
        printf("Can not create the string word!\n");
        free(whspace);
        fclose(in);
        fclose(out);
        return -1;
    }
    
    if ( (define.name = (char**)malloc(sizeof(char) * MAX_CHAR)) == NULL )
    {
        printf("Can not create the string define.name!\n");
        free(whspace);
        free(word);
        fclose(in);
        fclose(out);
        return -1;
    }
    if ( (define.value = (char**)malloc(sizeof(char) * MAX_CHAR)) == NULL )
    {
        printf("Can not create the string define.value!\n");
        free(whspace);
        free(word);
        free(define.name);
        fclose(in);
        fclose(out);
        return -1;
    }
    for (i = 0; i < MAX_CHAR; i++)
    {
        if ( (define.name[i] = (char*)malloc(sizeof(char) * MAX_CHAR)) == NULL )
        {
            printf("Can not create the string define.name[i]!\n");
            free(whspace);
            free(word);
            free(define.name);
            fclose(in);
            fclose(out);
            return -1;
        }
        if ( (define.value[i] = (char*)malloc(sizeof(char) * MAX_CHAR)) == NULL )
        {
            printf("Can not create the string value[i]!\n");
            free(whspace);
            free(word);
            free(define.name[i]);
            free(define.value);
            fclose(in);
            fclose(out);
            return -1;
        }
    }
    
    
    i = 0;
    
    while (next != -1 || i < MAX_CHAR)
    {
        getWord(whspace, &wh_len, word, &word_len, &next, in);
        if ( (wh_len == word_len) && (word_len == 0) && (next != 10) )
            break;
        
        
         for (l = 0; l < MAX_CHAR; l++)
            if (word == define.name[l])
                strcpy(word, define.value[l]);
        
        fprintf(out, "%s", whspace);
        fprintf(out, "%s", word);
        fprintf(out, "%c", next);
        
        
        if ( strcmp("#define", word) == NULL )
        {
            getWord(whspace, &wh_len, word, &word_len, &next, in);
            if ( (wh_len == word_len) && (word_len == 0) && (next != 10) )
                break;
            
            strcpy(define.name[i], word);
            fprintf(out, "%s", whspace);
            fprintf(out, "%s", define.name[i]);
            fprintf(out, "%c", next);
            
            
            getWord(whspace, &wh_len, word, &word_len, &next, in);
            if ( (wh_len == word_len) && (word_len == 0) && (next != 10) )
                break;
            
            strcpy(define.value[i], word);
            fprintf(out, "%s", whspace);
            fprintf(out, "%s", define.value[i]);
            fprintf(out, "%c", next);
            
            //printf("define.name[%d] = %s    define.value[%d] = %s\n", i, define.name[i], i, define.value[i]);
            i++;
        }
        
        
        if ( strcmp("#undef", word) == NULL )
        {
            getWord(whspace, &wh_len, word, &word_len, &next, in);
            if ( (wh_len == word_len) && (word_len == 0) && (next != 10) )
                break;
            
            fprintf(out, "%s", whspace);
            fprintf(out, "%s", word);
            fprintf(out, "%c", next);
            
            for (l = 0; l < MAX_CHAR; l++)
                if (word == define.name[l])
                {
                    define.name[l] = "";
                    define.value[l] = "";
                }
        }
    }
    
    
    /*free(whspace);
    free(word);
    for (i = 0; i < MAX_CHAR; i++)
    {
        free(define.name[i]);
        free(define.value[i]);
    }
    free(define.name);
    free(define.value);*/
    fclose(in);
    fclose(out);
    
    return 0;
}
