#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "printMatrix.h"
#include "QR_RM.h"

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

int main(void) {
    int n, res, inputMode;
    double* a = NULL;
    double* x = NULL;
    FILE* fin = NULL;
    FILE* fout = NULL;
    clock_t t;
    
    printf("Input mode : 1 - from file \"%s\".\n", INPUT_FILE_NAME);
    printf("             2 - from formula.\n");
    printf("-> ");
    scanf("%d", &inputMode);
    
    switch (inputMode) {
        case 1:
            fin = fopen(INPUT_FILE_NAME, "r");
            
            if (!fin) {
                printf("Can't open file!\n");
                return -1;
            }
            
            if (fscanf(fin, "%d", &n) != 1) {
                printf("Can't read from file!\n");
                fclose(fin);
                return -2;
            }
            
            break;
        case 2:
            printf("Please, enter n: ");
            scanf("%d", &n);
            
            break;
        default:
            printf("Incorrect mode!\n");
            return -3;
    }
    
    if (n < 1) {
        printf("n is less or zero!\n");
        
        if (inputMode == 1)
            fclose(fin);
        
        return -4;
    }
    
    a = (double*)malloc(n * n * sizeof(double));
    x = (double*)malloc(n * n * sizeof(double));
    
    if (!(a && x)) {
        printf("Not enough memory!\n");
        
        if (a)
            free(a);
        if (x)
            free(x);
        if (inputMode == 1)
            fclose(fin);
        
        return -5;
    }
    
    res = InputMatrix(n, a, inputMode, fin);
    
    if (inputMode == 1)
        fclose(fin);
    
    if (res == -1)
    {
        printf("Error in reading from file!\n");
        
        free(a);
        free(x);
        
        return -6;
    }
    
    fout = fopen(OUTPUT_FILE_NAME, "w");
    fprintf(fout, "Matrix A:\n");
    PrintMatrix(n, a, fout);
    fprintf(fout, "\n");
    
    t = clock();
    res = InvertMatrix(n, a, x);
    t = clock() - t;
    
    switch (res) {
        case -1:
            printf("Can't invert matrix!\n");
            
            break;
        case 0:
            fprintf(fout, "\nMatrix A^{-1}:\n");
            PrintMatrix(n, x, fout);
            fprintf(fout, "\n");
            
            fprintf(fout, "Inversion time = %.2f sec.\n\n", (double)t / CLOCKS_PER_SEC);
            
            if (inputMode == 1) {
                fin = fopen(INPUT_FILE_NAME, "r");
                fscanf(fin, "%d", &n);
            }
            
            InputMatrix(n, a, inputMode, fin);
            
            if (inputMode == 1)
                fclose(fin);
            
            //fprintf(fout, "Solution ||A * A^{-1} - b||\t= %e\n", SolutionError(n, a, x));
            
            break;
        default:
            printf("Unknown error!\n");
            
            break;
    }
    
    free(a);
    free(x);
    fclose(fout);
    
    return 0;
}
