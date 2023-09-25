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
    int inicio = 0;
    int fin = lista->contador - 1;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        int comparacion = strcmp(lista->envios[medio].codigo, codigo);
  //printf("Comparacion de codigos: %s vs. %s -> Resultado: %d\n", lista->envios[medio].codigo, codigo, comparacion);

        if (comparacion == 0) {
            *pos = medio;
            return 1;
        } else if (comparacion < 0) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }

    return 0;
}



int AltaLSOBB(lsobb *lista, Envio envio) {
    int pos;

    if (lista->contador == MAX_Envios) {
        return 2; // Lista llena
    }

    if (!LocalizarLSOBB(lista, envio.codigo, &pos)) {
        for (int i = lista->contador - 1; i >= pos; i--) {
            lista->envios[i + 1] = lista->envios[i];
        }
        lista->envios[pos] = envio;
        lista->contador++;
        return 0;
    } else {
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
        return 0;
    } else {
        return 1;
    }
}





int ModificarLSOBB(lsobb *lista) {
    char codigo_a_m[7];
    printf("Ingrese el codigo para modificar: ");
    scanf("%s", codigo_a_m);

    int pos;
    int localizar = LocalizarLSOBB(lista, Mayusculas(codigo_a_m), &pos);

    if (localizar == 1) {
        printf("Envio encontrado. Seleccione el campo a modificar:\n");
        printf("1. DNI Receptor\n");
        printf("2. Nombre y apellido del receptor:\n");
        printf("3. Direccion\n");
        printf("4. DNI Remitente\n");
        printf("5. Nombre y apellido del Remitente\n");
        printf("6. Fecha de Envio\n");
        printf("7. Fecha de Recepcion\n");
        printf("8. Salir sin hacer cambios\n");

        int opcion;
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el nuevo DNI receptor: ");
                scanf("%d", &lista->envios[pos].dni_receptor);
                break;
            case 2:
                printf("Ingrese el nuevo nombre: ");
                scanf(" %[^\n]", lista->envios[pos].nombre);
                break;
            case 3:
                printf("Ingrese la nueva direccion: ");
                scanf(" %[^\n]", lista->envios[pos].direccion);
                break;
            case 4:
                printf("Ingrese el nuevo DNI remitente: ");
                scanf("%d", &lista->envios[pos].dni_remitente);
                break;
            case 5:
                printf("Ingrese el nuevo nombre del remitente: ");
                scanf(" %[^\n]", lista->envios[pos].nombre_r);
                break;
            case 6:
                printf("Ingrese la nueva fecha de envio: ");
                scanf(" %[^\n]", lista->envios[pos].fecha_envio);
                break;
            case 7:
                printf("Ingrese la nueva fecha de recepcion: ");
                scanf(" %[^\n]", lista->envios[pos].fecha_recepcion);
                break;
            case 8:
                printf("No se realizaron cambios.\n");
                return 1;
            default:
                printf("Opcion no valida.\n");
                return 1;
        }
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


