#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para llenar el arreglo con valores aleatorios
void llenarArreglo(int *arr, int tam) {
    for (int i = 0; i < tam; i++) {
        arr[i] = rand() % 10000; // Valores entre 0 y 9999
    }
}

// Versión 1: Dos ciclos anidados
int rangoV1(int *arr, int tam) {
    int maxDif = 0;
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            int dif = abs(arr[i] - arr[j]);
            if (dif > maxDif)
                maxDif = dif;
        }
    }
    return maxDif;
}

// Versión 2: Dos ciclos anidados con cambio en el límite inferior del interno
int rangoV2(int *arr, int tam) {
    int maxDif = 0;
    for (int i = 0; i < tam; i++) {
        for (int j = i + 1; j < tam; j++) {
            int dif = abs(arr[i] - arr[j]);
            if (dif > maxDif)
                maxDif = dif;
        }
    }
    return maxDif;
}

// Versión 3: Un solo ciclo
int rangoV3(int *arr, int tam) {
    int max = arr[0], min = arr[0];
    for (int i = 1; i < tam; i++) {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }
    return max - min;
}

int main() {
    srand(time(NULL));
    int tamanos[] = {100, 1000, 10000, 100000, 1000000, 10000000};
    int numTamanos = sizeof(tamanos) / sizeof(tamanos[0]);

    for (int t = 0; t < numTamanos; t++) {
        int tam = tamanos[t];
        int *arr = (int *)malloc(tam * sizeof(int));
        if (!arr) {
            printf("Error al asignar memoria para tamaño %d\n", tam);
            continue;
        }
        llenarArreglo(arr, tam);

        clock_t inicio, fin;
        double tiempo;
        
        printf("\nTamaño del arreglo: %d\n", tam);
        
        inicio = clock();
        rangoV1(arr, tam);
        fin = clock();
        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo V1: %.6f segundos\n", tiempo);

        inicio = clock();
        rangoV2(arr, tam);
        fin = clock();
        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo V2: %.6f segundos\n", tiempo);

        inicio = clock();
        rangoV3(arr, tam);
        fin = clock();
        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo V3: %.6f segundos\n", tiempo);

        free(arr);
    }
    return 0;
}
