#include <stdio.h>
#include <pthread.h>
#include "integral.h"
#include <stdlib.h>

typedef struct {
    Funcion f;
    int n, p;
    double xi, xf;
    pthread_t pid;
    void* ptr;
    double resultado;
} Args;

void *integral_thread(void *ptr) {
    Args *args= (Args*)ptr;
    args->resultado=integral(args->f, args->ptr, args->xi, args->xf, args->n);
    return NULL;
}

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
    double resultado_final=0;
    Args *args_a= (Args*)malloc(p*sizeof(Args));
    for (int i= 0; i<p; i++) {
        Args *args= &args_a[i];
        args->n= n/p;
        args->xi= xi + i*((xf-xi)/p);
        args->xf= xi +(i+1)*((xf-xi)/p);
        args->f= f;
        args->ptr=ptr;
        pthread_create(&args->pid, NULL, integral_thread, args);
    }

    for (int i= 0; i<p; i++) {
        Args *args= &args_a[i];
        pthread_join(args->pid, NULL);
        resultado_final=resultado_final+args->resultado;
    }
    free(args_a);
  return resultado_final;
}
