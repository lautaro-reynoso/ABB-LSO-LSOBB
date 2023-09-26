

#include "Envios.h"
#include <String.h>
#ifndef UNTITLED_LSO_H
#define UNTITLED_LSO_H
#define MAX_Envios 300
#endif //UNTITLED_LSO_H
char *Mayusculas(char string[]);
typedef struct {
    Envio envios [MAX_Envios];
    int contador;
}lsobb;

int LocalizarLSOBB(lsobb *lista, char codigo[], int *pos) {
    int inicio = 0; // L�mite inferior inclusivo
    int fin = lista->contador - 1;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        int comparacion = strcmp(lista->envios[medio].codigo, codigo);

        if (comparacion == 0) {
            *pos = medio;
            return 1; // B�squeda termin� con �xito y el c�digo es igual (indicando que es un duplicado)
        } else if (comparacion < 0) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }

    *pos = inicio; // Posici�n donde deber�a insertarse si no se encuentra el c�digo
    return 0; // La clave no se encontr� en la lista
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

