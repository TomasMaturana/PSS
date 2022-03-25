#include <stdio.h>
#include <pthread.h>
#include "integral.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
    int pids[p];
    double infds[p];
    double resultado_final=0;
    for (int i= 0; i<p; i++) {
        int fds[2];
        pipe(fds);
        if ((pids[i]=fork())==0){
            close(fds[0]);
            double resultado=integral(f, ptr, xi + i*((xf-xi)/p), xi +(i+1)*((xf-xi)/p), n/p);
            write(fds[1], (double*)&resultado, sizeof(resultado));
            exit(0);
        }
        else {
            close(fds[1]);
            infds[i]=fds[0];
        }
    }

    for (int i= 0; i<p; i++) {
        double res;
        read(infds[i], (double*)&res, sizeof(double));
        waitpid(pids[i], NULL, 0);
        close(infds[i]);
        resultado_final+=res;
    }
  return resultado_final;
}
