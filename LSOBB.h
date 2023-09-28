

#include "Envios.h"
#include <String.h>
#ifndef UNTITLED_LSO_H
#define UNTITLED_LSO_H
#define MAX_Envios 300
#endif //UNTITLED_LSO_H

//  float eExMax=0.0, eExMed=0.0, eFrMax=0.0, eFrMed=0.0, aMax=0.0, aMed=0.0, bMax=0.0, bMed=0.0, celCont=0.0;
 //   int eExCant=0,eFrCant=0,aCant=0,bCant=0;

char *Mayusculas(char string[]);
typedef struct {
    Envio envios [MAX_Envios];
    int contador;
  float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, celCont,tempa,tempb, eExCant,eFrCant,aCant,bCant,costo,costoEvoE,costoEvoF,tempe,tempef;
}lsobb;


void initLSOBB(lso *lista) {
    lista->eExMax = 0.0;
    lista->eExMed = 0.0;
    lista->eFrMax = 0.0;
    lista->eFrMed = 0.0;
    lista->aMax = 0.0;
    lista->aMed = 0.0;
    lista->bMax = 0.0;
    lista->bMed = 0.0;
    lista->celCont = 0.0;
    lista->eExCant = 0;
    lista->eFrCant = 0;
    lista->aCant = 0.0;
    lista->bCant = 0.0;
    lista->tempa = 0.0;
      lista->tempb = 0.0;
      lista->tempe= 0.0;
      lista->tempef= 0.0;
}


int LocalizarLSOBB(lsobb *lista, char codigo[], int *pos, int p) {


    lista->costoEvoE=0.0;
lista->costoEvoF=0.0;
    float temp =0.0;
    int inicio = -1;  // Limite inferior exclusivo
    int fin = lista->contador - 1;  // Limite superior inclusivo

    while (inicio < fin) {
            temp++;

        int medio = (inicio + fin + 1) / 2;

        int comparacion = strcmp(lista->envios[medio].codigo, codigo);

        if (comparacion == 0) {

                  if(p==0){

            if(lista->eExMax<temp){
                lista->eExMax = temp;
      }
       lista->eExCant++;
       lista->costoEvoE+=temp;
       lista->tempe+=lista->costoEvoE;
       lista->eExMed = lista->tempe/(lista->eExCant+1);

       }



            *pos = medio;
            return 1; // Encontrado
        } else if (comparacion < 0) {


              if(p==0){
      if(lista->eFrMax<temp){
                lista->eFrMax = temp;
      }

       lista->eFrCant++;
       lista->costoEvoF+=temp;
        lista->tempef+=lista->costoEvoF;
       lista->eFrMed = lista->tempef/(lista->eFrCant+1);

    }


            inicio = medio;
        } else {
            fin = medio - 1;
        }
    }

    *pos = inicio + 1;
    return 0;
}





int AltaLSOBB(lsobb *lista, Envio envio) {


       lista->costo =0.0;
    int pos;

    if (lista->contador == MAX_Envios) {
        return 2; // Lista llena
    }

    if (LocalizarLSOBB(lista, envio.codigo, &pos,1)==0) {

        for (int i = lista->contador - 1; i >= pos; i--) {
                   lista->costo++; //corrimiento


            lista->envios[i + 1] = lista->envios[i];
        }
        lista->envios[pos] = envio;
        lista->contador++;



if (lista->costo > lista->aMax) {

    lista->aMax = lista->costo; //maximo

   // printf("%f\n",lista->aMax);

}


  lista->tempa+=lista->costo; //promedio

 lista->aMed=lista->tempa/(lista->aCant+1);

lista->aCant++; //cantidad de altas

        return 0;
    } else {
    //    printf("envio repetido\n");
        return 1;
    }
}


int BajaLSOBB(lsobb *lista, Envio envio) {
       lista->costo =0.0;
    int pos, i;
    int encontrado = LocalizarLSOBB(lista, envio.codigo, &pos,1);

    if( (strcmp(lista->envios[pos].direccion , envio.direccion)==0) && (lista->envios[pos].dni_receptor == envio.dni_receptor)
           && (lista->envios[pos].dni_remitente == envio.dni_remitente) && (strcmp(lista->envios[pos].fecha_envio,envio.fecha_envio)==0)
           && (strcmp(lista->envios[pos].fecha_recepcion,envio.fecha_recepcion)==0) && (strcmp(lista->envios[pos].nombre,envio.nombre)==0)
           && (strcmp(lista->envios[pos].nombre_r,envio.nombre_r)==0)){

    if (encontrado) {
        for (i = pos; i < lista->contador - 1; i++) {
                   lista->costo++; //corrimiento
            lista->envios[i] = lista->envios[i + 1];
        }

           pos--;
        lista->contador--;



     if (lista->costo > lista->bMax) {

    lista->bMax = lista->costo; //maximo

}

  lista->tempb+=lista->costo; //promedio


 lista->bMed=lista->tempb/(lista->bCant+1);


lista->bCant++; //cantidad de bajas
        return 0;
    } else {
        return 1;
    }
           }
           return 0;
}





int evocarLSOBB(lsobb *lista, char codigo[], Envio *envio) {
    int pos;
    int encontrado = LocalizarLSOBB(lista, codigo, &pos,0);
    if (encontrado) {
        *envio = lista->envios[pos];
        return 1;
    } else {
        return 0;
    }
}

