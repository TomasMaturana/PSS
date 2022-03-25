#include <stdio.h>
#include <stdlib.h>
#include "t2.h"

int calzar(Nodo *a, Nodo **ppat){
	Nodo *pat= *ppat;
	Nodo *A=a;
	int xa;
	int xpat;
	
	if(pat==NULL){
		*ppat=a;
		return 1;
	}
	
	if(A==NULL){
		return 0;
	}
	
	xa=A->x;
	xpat=(pat)->x;
	if(xa < xpat){
		return 0;
	}
	
	if(xa==xpat){
		if(calzar(A->der, &pat->der)){
			return calzar(A->izq, &pat->izq);
		}
		else {
			calzar(A->izq, &pat->izq);
			return 0;
		}
	}
	else{
		return 0;
	}
}
