#include <stdio.h>
#include <math.h>

void printArr(double *arr, int n, FILE *out);
double det(double *arr, int n, FILE *out);
void swapLines(double *arr, int n, int str1, int str2);
int getMaxValueIndex(double *arr, int n, int str);
void subLine(double *arr, int n, int str);

void printArr(double *arr, int n, FILE *out)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            fprintf(out, "%lf ", arr[i * n + j]);
        fprintf(out, "\n");
    }
}


double det(double *arr, int n, FILE *out)
{
    if (n == 1)
        return arr[0];
    else
        if (n == 2)
            return (arr[0] * arr[n + 1] - arr[1] * arr[n]);
        else
        {
            int max, i;
            double d = 1.0;
            
            for(i = 0; i < n - 1; i++)
            {
                max = getMaxValueIndex(arr, n, i);
                if (max == -1)
                    continue;
                if (max != i)
                {
                    swapLines(arr, n, i, max);
                    if( (max - i) % 2 == 1)
                        d *= -1;
                }
                subLine(arr, n, i);
            }
            for(i = 0; i < n; i++)
                d *= arr[i * n + i];
            
            fprintf(out, "\nComputed array:\n");
            printArr(arr, n, out);
            
            return d;
        }
}


void swapLines(double *arr, int n, int str1, int str2)
{
    int j;
    double tmp;
    
    for (j = 0; j < n; j++)
    {
        tmp = arr[str1 * n + j];
        arr[str1 * n + j] = arr[str2 * n + j];
        arr[str2 * n + j] = tmp;
    }
}


int getMaxValueIndex(double *arr, int n, int str)
{
    int i;
    
    for (i = str; i < n; i++)
        if (arr[i * n + str] != 0)
            return i;
    
    return -1;
}


void subLine(double *arr, int n, int str)
{
    int i, j;
    double c;
    
    for (i = str + 1; i < n; i++)
    {
        if (arr[i * n + str] == 0)
            continue;
        
        c = arr[i * n + str] / arr[str * n + str];
        for (j = str; j < n; j++)
            arr[i * n + j] -= c * arr[str * n + j];
    }
}



int main(int argc, const char * argv[])
{
    int n;
    double *arr;
    FILE *in, *out;
    
    if ( (in = fopen("__path__/input.txt", "r")) == NULL )
    {
        printf("Can not open the file input.txt!\n");
        return -7;
    }
    if (fscanf(in, "%d", &n) != 1)
    {
        printf("Could not scan n!\n");
        fclose(in);
        return -5;
    }
    if (n <= 0)
    {
        printf("Number of elements less or zero!\n");
        fclose(in);
        return -5;
    }
    
    if ( (arr = (double*)malloc(sizeof(double) * n * n)) == NULL )
    {
        printf("Could not create array!\n");
        fclose(in);
        return -3;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (fscanf(in, "%lf", &arr[i * n + j]) != 1)
            {
                printf("Could not read the element!\n");
                fclose(in);
                return -1;
            }
    fclose(in);
    
    if ( (out = fopen("__path__/output.txt", "w")) == NULL )
    {
        printf("Can not open the file output.txt!\n");
        return -7;
    }
    
    fprintf(out, "Source array:\n");
    printArr(arr, n, out);
    
    fprintf(out, "\nDeterminant = %lf", det(arr, n, out));
    
    fclose(out);
    
    return 0;
}
