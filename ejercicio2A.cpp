/*
- Jose Gerardo Ruiz García - 23719
- Humberto Alexander de la Cruz Chanchavac - 23735
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#define NUM_THREADS 10

void *PrintHello(void *paramID){
    //Convertir de punt. a void --- de puntero a void
    int *id;                //Guarda un valor de puntero a entero
    id = (int *)paramID;    //Cast explicita de void* a int*
    printf("Hello World thread No. %d\n", *id);
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char const *argv[])
{
    //Identificar hilos
    pthread_t threadID[NUM_THREADS];

    int rc, t, param[NUM_THREADS];

    // Declarar tambien un atributo tipo pthread_attr_t
    pthread_attr_t attr;

	// Al usar atributos, inicializar el objeto
    pthread_attr_init(&attr);

    // Modificar el atributo especifico
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //Creación de hilos
    for (t = 0; t < NUM_THREADS; t++){
        //Asignar valor al parametro que pasara subrutina
        param[t]=t;
        rc = pthread_create(&threadID[t], &attr, PrintHello, (void*)&param[t]);

        //Verificar
        if(rc){
            printf("Error: codigo reotornado desde pthread_create() %d", rc);
            exit(-1);
        }
    }

    //Join
    for (t = 0; t < NUM_THREADS; t++){
        pthread_join(threadID[t], NULL);
    }

    pthread_exit(NULL);
}

