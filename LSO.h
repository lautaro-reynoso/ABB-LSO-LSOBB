//
// Created by lautaro on 19/8/2023.
//
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
}lso;

int Localizar(lso *lista, char codigo[], int *pos) {
    int i = 0;


    while (i < lista->contador && strcmp(lista->envios[i].codigo, codigo) < 0) {

        i++;
    }

    *pos = i;
    if (i < lista->contador && strcmp(lista->envios[i].codigo, codigo) == 0) {
        return 1; // es igual al c�digo buscado
    } else {
        return 0; // es diferente}

    }
}


int AltaLSO(lso *lista, Envio envio) {
    int pos;

    int i;
    if(lista->contador == MAX_Envios){
        return 2;
    }
    int res = Localizar(lista, envio.codigo, &pos);

    if (res == 0) {

        for (i = lista->contador-1; i >= pos; i--) {
            lista->envios[i + 1] = lista->envios[i];
        }
        lista->envios[pos] = envio;

        lista->contador++;
        return 0;
    } else {


        return 1;
    }

}

int BajaLSO(lso *lista, char eliminar_codigo[]) {


    int conf;



    int pos, i;

    int localizar_resultado = Localizar(lista, eliminar_codigo, &pos);
    if (localizar_resultado) {
        //   printf("El envio a eliminar es: \n");
        //     mostrarenvio(lista->envios[pos]);



//printf("Desea eliminar el envio seleccionado? 1-Si, 2-No:\n");
// scanf("%d",&conf);


        // if(conf==1){

        for (i = pos; i <= lista->contador-1; i++) {
            lista->envios[i] = lista->envios[i + 1];
        }

        // Actualiza pos para reflejar el cambio despu�s de la eliminaci�n
        pos = pos - 1;

        lista->contador--; // Decrementa el contador

        return 0; // �xito en la eliminaci�n


        //  }   else{


    }else {
        return 1; // Env�o no encontrado
    }



}




int Modificar(lso *lista) {
    char codigo_a_m[7];
    printf("Ingrese el codigo para modificar: ");
    scanf("%s", codigo_a_m);

    int pos;
    int localizar = Localizar(lista, Mayusculas(codigo_a_m), &pos);

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
                printf("Opci�n no v�lida.\n");
                return 1;
        }
        return 0;
    } else {
        return 1;
    }
}
int evocarLSO (lso *lista, char codigo[], Envio *envio){

    int pos;
    int res = Localizar(lista,codigo,&pos);
    if (res == 1){
        (*envio)= lista->envios[pos];
        return 1;// se
        // econtro
    }else
        return 0;
}
