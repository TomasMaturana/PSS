#include <stdio.h>
#include <stdlib.h>

void extraer(char *in){
    FILE *cola;
    cola=fopen(in, "r+");
    if (getc(cola)=='0'){
        perror("error: cola.txt esta vacia");
        exit(1);
    }
    fseek(cola, -1, SEEK_CUR);
    char buf[5];
    fread(buf, sizeof(char), 4, cola);
    int n=atoi(buf);
    char prioridadN[6];
    char nombre[11];
    char ultimo[17];
    int prioridadFinal;
    int posicion;
    fseek(cola, 10, SEEK_CUR);
    fread(prioridadN, sizeof(char), 6, cola);
    prioridadFinal=atoi(prioridadN);
    posicion=ftell(cola)-15;
    fseek(cola, 1, SEEK_CUR);
    for(int i=0; i<(n-1); i++){
        fseek(cola, 10, SEEK_CUR);
        fread(prioridadN, sizeof(char), 6, cola);
        if(atoi(prioridadN)<prioridadFinal){
            prioridadFinal=atoi(prioridadN);
            posicion=ftell(cola)-15;
        }
        if(i==n-2){
            fseek(cola, -15, SEEK_CUR);
            fread(ultimo, sizeof(char), 17,cola);
            fseek(cola, -1, SEEK_CUR);
        }
        fseek(cola, 1, SEEK_CUR);
    }
    fseek(cola, posicion, SEEK_SET);
    fread(nombre, sizeof(char), 10, cola);
    nombre[10]='\0';
    printf("%s\n",nombre);
    fseek(cola, -10, SEEK_CUR);
    if(n!=1){
        for(int i=0; i<17; i++){
            putc(ultimo[i], cola);
        }
    }
    //modificar n
    n=n-1;
    sprintf(buf,"%-4d", n);
    fseek(cola, 0, SEEK_SET);
    for(int i=0; i<4; i++){
        putc(buf[i], cola);
    }

    fclose(cola);
}

int main(int argc, char *argv[]) {
    extraer(argv[1]);
    return 0;
}