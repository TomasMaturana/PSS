#include "t1.h"
#include "string.h"
#include "stdlib.h"

// Programe aca las 3 funciones pedidas
///////////////////////////////////////////////////////////////////////////
int largoArreglo(int nbits){
	int largo= sizeof(uint)<<3;
	return largo/nbits;				//// ocupo /
}

uint comprimir(uint *a, int nbits){
	uint *b=a;
	uint comprimido=0;
	uint aux=0;
	int contador=0;
	int largo = largoArreglo(nbits);
	int mask=~((-1)<<nbits);
	for (contador=0; contador<largo; contador++){
		aux=0;
		aux=b[contador]&mask;
		aux<<=((largo-1-contador)*nbits);  //// ocupo *
		comprimido=comprimido|aux;
	}
	return comprimido;
}


///////////////////////////////////////////////////////////////////////////////
char *insercion(char *d, char *s){
	char *Pd=d;
	char *Ps=s;
	int contadorD=0;
	int contadorS=0;
	while(*Pd){
		contadorD++;
		Pd++;
		}
	while(*Ps){
		contadorS++;
		Ps++;
		}
	char *resultado=malloc(sizeof(char)*(contadorD+contadorS+1));
	strcpy(resultado, s);
	strcat(resultado, d);
	return resultado;
}


//////////////////////////////////////////////////////////////////////////////
void insertar(char *d, char *s){
	char *Pd=d;
	char *Ps=s;
	char aux;
	int contador=0;
	int largoD=strlen(Pd);
	int largoS=strlen(Ps);
	for(contador=0; contador<=largoD; contador++){
		Pd+=largoD-contador;
		aux=*Pd;
		Pd+=largoS;
		*Pd=aux;
		Pd=d;		
	}
	
	for(contador=1; contador<=largoS; contador++){
		Pd+=largoS-contador;
		Ps+=largoS-contador;
		aux=*Ps;
		*Pd=aux;
		Pd=d;
		Ps=s;
	}
	
	
	





}
