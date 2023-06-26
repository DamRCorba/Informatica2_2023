#include <stdio.h>

typedef struct
{
    long id;
    char categoria[90];
    float valor;
    unsigned int estado;
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
        printf("\nID: %d, Categoria: %s, Valor: %f, Estado: %d", fileData.id, fileData.categoria, fileData.valor, fileData.estado);
        fread(&fileData, sizeof(datos_t), 1, fp);
    }
    return 0;

    return 0;
}
