// Moisés Fernández Zárate A01197049
// 17/05/2020
// Problem.c
// Problema Player resuelto de la página CodeChef
// https://www.codechef.com/problems/RRPLAYER

#include <stdio.h>

int main() {
    int T, i, n;
    double ans, aux;

    scanf("%d", &T);

    while(T--) {
        scanf("%d", &n);

        ans = 0;
        aux = n;

        for(i = 1; i <= n; i++) {
            ans = ans + aux / i;
        }
        
        printf("%.1f\n", ans);
    }

    return 0;
} 