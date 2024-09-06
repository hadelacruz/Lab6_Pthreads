/*
- Jose Gerardo Ruiz García - 23719
- Humberto Alexander de la Cruz Chanchavac - 23735
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct ThreadData {
    int n;
    double result;
};

void* calculate_term(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int n = data->n;
    data->result = 1.0 / (n * (n + 1));
    pthread_exit(NULL);
}

int main() {
    // Solicitar el valor máximo de n al usuario
    printf("Ingrese el valor máximo de n: ");
    int N;
    cin >> N;

    if (N <= 0) {
        printf("El valor máximo de n debe ser mayor que 0.\n");
        return -1;
    }

    // Crear un array de hilos
    pthread_t threads[N];
    ThreadData thread_data[N];
    int rc;

    // Crear hilos para calcular cada término
    for (int i = 0; i < N; ++i) {
        thread_data[i].n = i + 1;
        rc = pthread_create(&threads[i], NULL, calculate_term, (void*)&thread_data[i]);
        if (rc) {
            printf("Error creando el hilo %d\n", i);
            exit(-1);
        }
    }

    // Esperar a que todos los hilos terminen y sumar los resultados
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
        sum += thread_data[i].result;
    }

    // Imprimir el resultado
    printf("La suma de la serie hasta n=%d es: %f\n", N, sum);

    return 0;
}