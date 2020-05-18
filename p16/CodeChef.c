// Moisés Fernández Zárate A01197049
// 17/05/2020
// CodeChef.c 
// Archivo Problem.c convertido para crear un servicio en linux.

#include <stdio.h>

int mainCodeChef() {
    int T, i, n;
    double ans, aux;

    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    fscanf(in, "%d", &T);

    while(T--) {
        fscanf(in, "%d", &n);

        ans = 0;
        aux = n;

        for(i = 1; i <= n; i++) {
            ans = ans + aux / i;
        }
        
        fprintf(out, "%.1f\n", ans);
    }

    fclose(in);
    fclose(out);

    return 0;
} 