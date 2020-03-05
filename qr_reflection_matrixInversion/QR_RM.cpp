#include <math.h>

#include "QR_RM.h"

int InvertMatrix(int n, double* a, double* x) {
    double tmp1, tmp2;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            x[i * n + j] = (double)(i == j);
    
    for (int i = 0; i < n; i++) {
        tmp1 = 0.0;
        for (int j = i + 1; j < n; j++)
            tmp1 += a[j * n + i] * a[j * n + i];
        
        tmp2 = sqrt(tmp1 + a[i * n + i] * a[i * n + i]);
        
        if (tmp2 < 1e-100)
            return -1;
        
        a[i * n + i] -= tmp2;
        
        tmp1 = sqrt(tmp1 + a[i * n + i] * a[i * n + i]);
        
        if (tmp1 < 1e-100) {
            a[i * n + i] += tmp2;
            continue;
        }
        
        tmp1 = 1.0 / tmp1;
        for (int j = i; j < n; j++)
            a[j * n + i] *= tmp1;
        
        for (int k = i + 1; k < n; k++) {
            tmp1 = 0.0;
            for (int j = i; j < n; j++)
                tmp1 += a[j * n + i] * a[j * n + k];
            
            tmp1 *= 2.0;
            for (int j = i; j < n; j++)
                a[j * n + k] -= tmp1 * a[j * n + i];
        }
        
        for (int k = 0; k < n; k++) {
            tmp1 = 0.0;
            for (int j = i; j < n; j++)
                tmp1 += a[j * n + i] * x[k * n + j];
            
            tmp1 *= 2.0;
            for (int j = i; j < n; j++)
                x[k * n + j] -= tmp1 * a[j * n + i];
        }
        
        a[i * n + i] = tmp2;
    }
    
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            tmp1 = x[i * n + j];
            x[i * n + j] = x[j * n + i];
            x[j * n + i] = tmp1;
        }
    
    for (int k = 0; k < n; k++)
        for (int i = n - 1; i >= 0; i--) {
            tmp1 = x[i * n + k];
            for (int j = i + 1; j < n; j++)
                tmp1 -= a[i * n + j] * x[j * n + k];
            x[i * n + k] = tmp1 / a[i * n + i];
        }
    
    return 0;
}
