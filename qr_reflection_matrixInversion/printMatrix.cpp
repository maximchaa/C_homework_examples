#include <stdio.h>
#include <math.h>

#include "printMatrix.h"

#define MAX_OUTPUT_SIZE 5

static double f(int i, int j) {
    return (i + j) / 2.0;
}

int InputMatrix(int n, double* a, int inputMode, FILE* fin) {
    if (inputMode == 1) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (fscanf(fin, "%lf", &a[i * n + j]) != 1)
                    return -1;
    }
    else {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i * n + j] = f(i, j);
    }
    
    return 0;
}

void PrintMatrix(int n, double* a, FILE* fout)  {
    //int nPrint;
    
    //nPrint = (n > MAX_OUTPUT_SIZE) ? MAX_OUTPUT_SIZE : n;
    
    for (int i = 0; i < n; i++) {
        fprintf(fout, "|");
        for (int j = 0; j < n; j++)
            fprintf(fout, "%5.3g ", a[i * n + j]);
        fprintf(fout, "|\n");
    }
}

/*
double SolutionError(int n, double* a, double* x) {
    double tmp, res;
    
    res = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tmp = 0.0;
            for (int k = 0; k < n; k++)
                tmp += a[i * n + k] * x[k * n + j];
            
            if (i == j)
                tmp -= 1.0;
            
            res += tmp * tmp;
        }
    }
    
    return sqrt(res);
}
*/
