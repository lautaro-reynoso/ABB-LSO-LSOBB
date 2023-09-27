#define ABB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include "Envios.h"
#include <malloc.h>
typedef struct Nodo{
    Envio envio;
    struct Nodo *der;
    struct Nodo *izq;
}nodo;
typedef struct{
    nodo *raiz;
    nodo *pos;
    nodo *padre;
    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, celCont;
    int eExCant, eFrCant, aCant, bCant;

}arbol;
void initABB(arbol *a){
    (*a).pos=NULL;
    (*a).padre=NULL;
    (*a).raiz=NULL;
    abb->eExMax = 0;
    abb->aMax = 0;
    abb->bMax = 0;
    abb->eFrMax = 0;
    abb->bMed = 0;
    abb->bCant = 0;
    abb->eFrMed = 0;
    abb->eExCant = 0;
    abb->eFrCant = 0;
    abb->aCant = 0;
    abb->aMed = 0;
    abb->eExMed = 0;

}
int localizarABB(arbol *a,char codigo[]){
    a->celCont = 0;
    a->pos = a->raiz;
    a->padre = a->raiz;
    while((*a).pos != NULL && strcmp((*a).pos->envio.codigo, codigo)){
            a->celCont++;
        if (strcmp((*a).pos->envio.codigo, codigo) > 0){
            (*a).padre = (*a).pos;
            (*a).pos = (*a).pos->izq;
        }else{
            (*a).padre = (*a).pos;
            (*a).pos = (*a).pos->der;
        }

    }
    if ((*a).pos == NULL){
        return 0;
    }else{
        return 1;
    }
}
int bajaABB(arbol *a,char codigo[]){
    if (localizarABB(a,codigo)== 0){
        return 2;
    }else{
        int opcion,s=0;
        nodo *aux,*padre;
        padre = (*a).pos;
        aux = a->pos;

            if ((*a).pos->izq != NULL){
                if((*a).pos->der != NULL){//caso tiene los dos hijos
                    aux = (*a).pos->der;
                    while(aux->izq != NULL){
                        s++;
                        padre = aux;
                        aux = aux->izq;
                    }
                    if(s == 0 )
                    {
                        padre->der = aux->der;
                    }
                    else
                    {
                        padre->izq = aux->der;
                    }

                    (*a).pos->envio = aux->envio;
                    free(aux);
                    return 1;
                }
                else{//caso tiene hijo izq
                    aux = (*a).pos->izq;
                    if((*a).padre->izq == (*a).pos)
                        (*a).padre->izq = aux;
                    else if((*a).padre->der == (*a).pos)
                        (*a).padre->der = aux;
                    else
                        (*a).raiz = aux;
                    free(((*a).pos));
                    return 1;
                }
            }
            else if((*a).pos->der != NULL){//caso tiene hijo derecho
                aux = (*a).pos->der;
                if((*a).padre->izq == (*a).pos)
                    (*a).padre->izq = aux;
                else if((*a).padre->der == (*a).pos)
                    (*a).padre->der = aux;
                else
                    (*a).raiz = aux;

                free(((*a).pos));
                return 1;
            }
            else if((*a).padre == (*a).pos){
                (*a).raiz = NULL;
                free(aux);
                return 1;
            }
            else if((*a).padre->izq == (*a).pos){//no tiene hijos
                (*a).padre->izq = NULL;
                free(aux);
                return 1;
            }
            else{
                (*a).padre->der = NULL;
                free(aux);
                return 1;
            }


    }

}

int altaABB(arbol *a,Envio envio){

    if (localizarABB(a,envio.codigo)==0){
        nodo *nuevo_nodo;
        nuevo_nodo=(nodo*)malloc(sizeof(nodo));
        if(nuevo_nodo==NULL){
            return 2;//no hay espacio
        }else{
            nuevo_nodo->envio=envio;
            nuevo_nodo->der=NULL;
            nuevo_nodo->izq=NULL;
            if((*a).padre==NULL){
                (*a).padre=nuevo_nodo;
                (*a).pos=(*a).padre;
                (*a).raiz=(*a).padre;
                return 1;
            }else if (strcmp((*a).padre->envio.codigo, envio.codigo) < 0){

                (*a).padre->der=nuevo_nodo;
                return 1;
            }else{

                (*a).padre->izq=nuevo_nodo;
                return 1;
            }
        }
    }else{
        return 0;
    }
}

Envio evocacionABB(arbol a,char codigo[],int *exito){
    *exito=localizarABB(&a,codigo);
    if(*exito==1){
        return a.pos->envio;
    }
}


void preOrden(nodo *a){
    if( a == NULL){
    }else{
        printf("\nCodigo: %s \n", a->envio.codigo);
        printf("Dni receptor: %d\n",a->envio.dni_receptor);
        printf("Nombre y Apellido: %s\n",a->envio.nombre);
        printf("Direccion: %s\n",a->envio.direccion);
        printf("Dni remitente: %d\n",a->envio.dni_remitente);
        printf("Fecha de envio: %s\n",a->envio.fecha_envio);
        printf("Fecha recepcion: %s\n",a->envio.fecha_recepcion);
        printf("Nombre receptor: %s\n\n",a->envio.nombre_r);
        if( a->izq != NULL ){
            printf("\nEl Codigo de su hijo izquierdo es: %s",a->izq->envio.codigo);
        }else{
            printf("\nNo tiene hijo izquierdo.");
        }

        if(a->der != NULL){
            printf("\nEl Codigo de su hijo derecho es: %s",a->der->envio.codigo);
        }else
            printf("\nNo tiene hijo derecho.");
        printf("\n*********************************************\n");
        //getchar();
        preOrden(a->izq);
        preOrden(a->der);
    }
}
