#include <stdio.h>

typedef struct{
    long id;
    char descripcion[90];
    int tipo;
    char marca; // Marca 'A': Alta  'B': Baja)
}datos_t;

int main(int argc, char const *argv[])
{
    datos_t fileDato;
    FILE *fp;
    char opc='s';
    long id=1;

    if((fp=fopen("datos.dat","wb")) == NULL){
        printf("No se pudo abrir el archivo");
        return -1; // Error
    }
    printf("Bienvenido a la carga de Archivos\n");

    do {
        printf("Ingrese la Descripcion: ");
        gets(fileDato.descripcion);
        printf("Ingresar el Tipo: ");
        scanf("%d",&fileDato.tipo);
        fileDato.id = id;
        printf("Ingrese la marca (A ó B): ");
        fflush(stdin);
        getchar();
        fileDato.marca = getchar();

        fwrite(&fileDato,sizeof(datos_t),1,fp);

        printf("\nDesea Ingresar mas datos? s/n");
        fflush(stdin);
        getchar();
        opc=getchar();
        fflush(stdin);
        getchar();
        id++;

    }while(opc != 'n');

    return 0;
}

