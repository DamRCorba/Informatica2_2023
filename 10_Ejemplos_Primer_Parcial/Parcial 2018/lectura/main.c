#include <stdio.h>

typedef struct
{
    long id;
    char descripcion[90];
    int tipo;
    char marca; // Marca 'A': Alta  'B': Baja)
} datos_t;

int main(int argc, char const *argv[])
{
    FILE *fp;
    datos_t fileData;

    if ((fp = fopen("datos.dat", "rb")) == NULL)
    {
        printf("No se pudo abrir el archivo");
        return -1; // Error
    }

    fread(&fileData,sizeof(datos_t),1,fp);
    while(!feof(fp)) {
        printf("\nID: %d, Descripcion: %s, Tipo: %d, Marca: %c", fileData.id, fileData.descripcion, fileData.tipo, fileData.marca);
        fread(&fileData, sizeof(datos_t), 1, fp);
    }
    return 0;

    return 0;
}
