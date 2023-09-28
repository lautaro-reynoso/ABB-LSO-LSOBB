

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
}lsobb;

int LocalizarLSOBB(lsobb *lista, char codigo[], int *pos) {
    int inicio = 0;
    int fin = lista->contador - 1;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        int comparacion = strcmp(lista->envios[medio].codigo, codigo);

        if (comparacion == 0) {
            *pos = medio;
            return 1;
        } else if (comparacion < 0) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }

    *pos = inicio;
    return 0;
}





int AltaLSOBB(lsobb *lista, Envio envio) {
    int pos;

    if (lista->contador == MAX_Envios) {
        return 2; // Lista llena
    }

    if (LocalizarLSOBB(lista, envio.codigo, &pos)==0) {

        for (int i = lista->contador - 1; i >= pos; i--) {
            lista->envios[i + 1] = lista->envios[i];
        }
        lista->envios[pos] = envio;
        lista->contador++;

        return 0;
    } else {
    //    printf("envio repetido\n");
        return 1;
    }
}


int BajaLSOBB(lsobb *lista, char eliminar_codigo[]) {
    int pos, i;
    int encontrado = LocalizarLSOBB(lista, eliminar_codigo, &pos);
    if (encontrado) {
        for (i = pos; i < lista->contador - 1; i++) {
            lista->envios[i] = lista->envios[i + 1];
        }
        lista->contador--;
        pos--;
        return 0;
    } else {
        return 1;
    }
}





int evocarLSOBB(lsobb *lista, char codigo[], Envio *envio) {
    int pos;
    int encontrado = LocalizarLSOBB(lista, codigo, &pos);
    if (encontrado) {
        *envio = lista->envios[pos];
        return 1;
    } else {
        return 0;
    }
}

