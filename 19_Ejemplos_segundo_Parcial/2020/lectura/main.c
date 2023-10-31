#include <stdio.h>

typedef struct
{
    int cl;            // clave
    char d[30];        // descripcion
    unsigned int tipo; // bit 4 en 1 valores positivos, bit 4 en 0 valores negativos
    unsigned int valor;
    char m; // A-Alta, B-Baja
} datos_t;

int main(int argc, char const *argv[]){
    FILE *fp;
    datos_t datos;


    if((fp=fopen("../datos.dat","rb"))==NULL){
        printf("\nNo se pudo abrir el archivo");
        return 1;
    }

    fread(&datos, sizeof(datos_t),1,fp);
    while (!feof(fp))
    {
        printf("\nCL: %d, Descripcion:%s, Tipo: %d, Valor: %d, marca:%c", datos.cl,datos.d, datos.tipo, datos.valor, datos.m);

        fread(&datos, sizeof(datos_t), 1, fp);
    }
    


    return 0;
}