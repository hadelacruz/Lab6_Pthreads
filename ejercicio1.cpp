/*
- Jose Gerardo Ruiz García - 23719
- Humberto Alexander de la Cruz Chanchavac - 23735

Desarrolle un programa que utilice Pthreads de C++, que permita calcular/determinar los
números divisibles dentro de 2, 3 y 5, para un número entre 0 y un valor máximo ingresado
desde teclado. El usuario también deberá ingresar la cantidad de hilos a utilizar en el programa.
Cada hilo verificará n valores, donde n es:

Debe implementar paso de parámetros por medio de estructuras, de ser necesario

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Estructura para pasar múltiples parámetros a los hilos
struct ThreadData {
    int threadID;
    int numMax;
    int start;
    int end;
};

// Función que ejecutarán los hilos
void *calculoDivisibilidad(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int threadID = data->threadID;
    int numMax = data->numMax;
    int start = data->start;
    int end = data->end;

    // Imprimir el rango que está procesando el hilo
    printf("Hilo %d procesando el rango de %d a %d\n", threadID, start, end);

    // Números divisibles entre 2
    printf("Numeros divisibles por 2 en el rango de %d a %d: ", start, end);
    for (int i = start; i <= end; i++) {
        if (i % 2 == 0) {
            printf("%d, ", i);
        }
    }
    printf("\n");

    // Números divisibles entre 3
    printf("Numeros divisibles por 3 en el rango de %d a %d: ", start, end);
    for (int i = start; i <= end; i++) {
        if (i % 3 == 0) {
            printf("%d, ", i);
        }
    }
    printf("\n");

    // Números divisibles entre 5
    printf("Numeros divisibles por 5 en el rango de %d a %d: ", start, end);
    for (int i = start; i <= end; i++) {
        if (i % 5 == 0) {
            printf("%d, ", i);
        }
    }
    printf("\n");

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Solicitud del número de hilos
    cout << "Ingrese el número de hilos con el que desea trabajar: ";
    int NUM_THREADS;
    cin >> NUM_THREADS;

    // Solicitud del valor máximo
    cout << "Ingrese el valor máximo: ";
    int numMax;
    cin >> numMax;

    // Creación del arreglo para almacenar los IDs de los hilos
    pthread_t threadsID[NUM_THREADS];
    
    // Arreglo para los datos de cada hilo
    ThreadData threadData[NUM_THREADS];

    // División del trabajo entre los hilos
    int rangePerThread = numMax / NUM_THREADS;
    int remaining = numMax % NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        // Asignar los rangos para cada hilo
        threadData[i].threadID = i;
        threadData[i].numMax = numMax;
        threadData[i].start = i * rangePerThread;
        threadData[i].end = (i == NUM_THREADS - 1) ? (i + 1) * rangePerThread + remaining : (i + 1) * rangePerThread - 1;

        // Crear el hilo
        int rc = pthread_create(&threadsID[i], NULL, calculoDivisibilidad, (void *)&threadData[i]);
        
        // Verificar si el hilo se creó correctamente
        if (rc) {
            cout << "ERROR: Código retornado desde pthread_create() " << rc << endl;
            exit(-1);
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threadsID[i], NULL);
    }

    cout << "Todos los hilos han finalizado." << endl;

    return 0;
}