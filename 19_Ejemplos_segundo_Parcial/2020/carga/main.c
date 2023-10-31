#include <stdio.h>


typedef struct 
{ 
    int cl;             //clave
    char d[30];         //descripcion    
    unsigned int tipo;  //bit 4 en 1 valores positivos, bit 4 en 0 valores negativos
    unsigned int valor;
    char m;             // A-Alta, B-Baja
}datos_t;

int main(int argc, char const *argv[])
{
    datos_t datos;
    FILE *fp;
    char mas = 0;

    if((fp = fopen("../datos.dat","ab")) == NULL){
        printf("\nNo se pudo abrir el archivo.\n");
        return 1;
    }

    printf("\nCarga de datos");

    do
    {
        printf("\nIngrese la clave");
        scanf("%d", &datos.cl);
        fflush(stdin);
        getchar();
        printf("\nIngrese la descripcion: "),
        gets(datos.d);
        fflush(stdin);
        printf("\nIngrese el tipo:");
        scanf("%d", &datos.tipo);
        printf("\nIngrese el Valor:");
        scanf("%d", &datos.valor);
        fflush(stdin);
        getchar();
        printf("\nIngrese la marca:");
        datos.m = getchar();
        fflush(stdin);

        fwrite(&datos, sizeof(datos_t),1, fp);
        printf("\n¿Desea Ingresar mas datos? s/n");
        getchar();
        mas=getchar();
        fflush(stdin);
    } while (mas != 'n');
    

    fclose(fp);
    return 0;
}



