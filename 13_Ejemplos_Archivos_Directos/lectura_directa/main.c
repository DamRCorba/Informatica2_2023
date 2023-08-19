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
    long id;
    int tipo;
    if ((fp = fopen("datos.dat", "rb+")) == NULL)
    {
        printf("No se pudo abrir el archivo");
        return -1; // Error
    }
    printf("Hola, como estas? Que registro queres consultar? ");
    scanf("%ld",&id);

    fseek(fp, (long)(sizeof(datos_t)*(id-1)),SEEK_SET);

    fread(&fileData, sizeof(datos_t), 1, fp);
    printf("\nID: %d, Descripcion: %s, Tipo: %d, Marca: %c", fileData.id, fileData.descripcion, fileData.tipo, fileData.marca);
    
    printf("Desea dar de baja al registro? 1-Si, 2-No");
    scanf("%d",&tipo);

    if(tipo == 1 ) { // le doy de baja logica
        fileData.marca='B';
        fseek(fp, -1L * sizeof(datos_t), SEEK_CUR);
        fwrite(&fileData, sizeof(datos_t), 1, fp);
        fseek(fp, -1L * sizeof(datos_t), SEEK_CUR);
        fread(&fileData, sizeof(datos_t), 1, fp);
        printf("\nID: %d, Descripcion: %s, Tipo: %d, Marca: %c", fileData.id, fileData.descripcion, fileData.tipo, fileData.marca);
    }

    // Modificacion de Archivo directo
    // printf("\nCual es el nuevo tipo: ");
    // scanf("%d",&tipo);
    // fseek(fp, -1L*sizeof(datos_t) , SEEK_CUR);
    // fileData.tipo = tipo;
    // fwrite(&fileData, sizeof(datos_t), 1, fp);

    // fseek(fp, -1L * sizeof(datos_t), SEEK_CUR);
    // fread(&fileData, sizeof(datos_t), 1, fp);
    // printf("\nID: %d, Descripcion: %s, Tipo: %d, Marca: %c", fileData.id, fileData.descripcion, fileData.tipo, fileData.marca);

    return 0;
}
