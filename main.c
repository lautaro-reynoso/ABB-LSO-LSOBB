#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Envios.h"
#include "LSO.h"
#include "ABB.h"
#include "LSOBB.h"
int LecturaOperaciones();
char* Mayusculas();
void mostrarestructura();
void mostrarSubmenu()
{
    printf("--Submenu--\n");
    printf("1. Mostrar Lista Secuencial Ordenada (LSO)\n");
    printf("2. Mostrar Lista Secuencial con Busqueda Binaria (LSOBB)\n");
    printf("3. Mostrar Arbol Binario de Busqueda (ABB)\n");
    printf("4. Volver al Menu Principal\n");
}
char *Mayusculas(char string[])
{
    int i;
    for(i=0; string[i]!='\0'; i++)
    {
        string[i]= toupper(string[i]);
    }
    return  string;
}
void mostrarestructuraLSO(lso *lista)
{
    int i;

    for(i = 0 ; i < lista->contador; i++)
    {
        mostrarenvio(lista->envios[i]);
        getchar();
    }
    printf("Total de %d envios\n", lista->contador);

}
void mostrarestructuraLSOBB(lsobb *lista)
{
    int i;

    for(i = 0 ; i < lista->contador; i++)
    {
        mostrarenvio(lista->envios[i]);
        getchar();
    }
    printf("Total de %d envios\n", lista->contador);

}





int main()
{
    // Crea las estructuras de datos (LSO, ABB) aquí

    int opcion, submenu_opcion;

    lso lso;
    lso.contador=0;
    initLSO(&lso);

    arbol a;
    initABB(&a);


    lsobb lsobb;
    lsobb.contador=0;




    do
    {
        // Menú principal

        printf("1. Comparacion de estructuras\n");
        printf("2. Mostrar Estructura\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            system("cls");
            LecturaOperaciones(&lso, &a, &lsobb);


        printf("%f , %f , %f , %f , %f, %f, %f , %f\n",lso.aMax, lso.aMed , lso.bMax, lso.bMed, lso.eExMax , lso.eExMed, lso.eFrMax, lso.eFrMed);
        printf("xd : %f\n , %f , %f , %f , %f, %f, %f , %f\n",a.aMax, a.aMed , lso.bMax, lso.bMed, lso.eExMax , lso.eExMed, lso.eFrMax, lso.eFrMed);


            break;
        case 2:


            system("cls");
            do
            {
                mostrarSubmenu();
                printf("Seleccione una opcion: ");
                scanf("%d", &submenu_opcion);
                switch (submenu_opcion)
                {
                case 1:
                    system("cls");

                    printf("Lista Secuencial Ordenada:\n");
                    mostrarestructuraLSO(&lso);
                    break;
                case 2:
                    system("cls");
                    printf("Lista Secuencial Ordenada con Busqueda Binaria (LSOBB):\n");
                    mostrarestructuraLSOBB(&lsobb);

                    break;
                case 3:
                    system("cls");
                    printf("Arbol Binario de Busqueda (orden ascendente):\n");
                    preOrden(a.raiz);
                    break;
                case 4:
                    system("cls");
                    // Volver
                    break;
                default:
                    printf("Opcion no valida. Intente de nuevo.\n");
                }
            }
            while (submenu_opcion != 4);

            break;
        case 3:
            system("cls");
            printf("Saliendo de la aplicacion.\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
    while (opcion != 3);


    return 0;
}
int LecturaOperaciones(lso *lso,arbol *arbol, lsobb *lsobb)
{

    // Declaraciones e inicializaciones
    int respuesta = 2,resLSOBB,resABB, alta=0,baja=0,evocar=0;
    Envio aux;
    FILE* fp;

    if ((fp = fopen("Operaciones-Envios.txt", "r")) == NULL)
    {
        printf("No se pudo abrir el archivo");
        return 0;
    }
    else
    {
        int codigoOperador=0, contadorEnvios=0;
        while (!(feof(fp))&&contadorEnvios<=MAX_Envios)
        {


            fscanf(fp, "%d", &codigoOperador);
            fscanf(fp, " %[^\n]", aux.codigo);
            if (codigoOperador == 1 || codigoOperador == 2)
            {

                // Leer y procesar los datos para Alta o Baja
                fscanf(fp, "%d", &aux.dni_receptor);
                fscanf(fp, " %[^\n]", aux.nombre);
                fscanf(fp, " %[^\n]", aux.direccion);
                fscanf(fp, "%d", &aux.dni_remitente);
                fscanf(fp, " %[^\n]", aux.nombre_r);
                fscanf(fp, " %[^\n]", aux.fecha_envio);
                fscanf(fp, " %[^\n]", aux.fecha_recepcion);

                // Llama a la función correspondiente para alta o baja en las estructuras
                if(codigoOperador == 1)
                {
                    //  mostrarenvio(aux);
                    AltaLSO(lso, aux);
                    AltaLSOBB(lsobb,aux);

                  altaABB(arbol,aux);




                }
                if(codigoOperador == 2)
                {



                bajaABB(arbol,aux);

                    BajaLSOBB(lsobb,aux);

                 BajaLSO(lso,aux);





                }

            }
            else if (codigoOperador == 3)
            {

                evocar++;


             //   Envio envioaux;
           //     aux = evocarLSO(lso,aux.codigo,&envioaux);


            }
            else
            {
                // Maneja el caso de código de operación no reconocido
                printf("Error: Codigo de operación no reconocido.\n");
                //break;
            }

        }

        fclose(fp);


        return 1;
    }

}
