#include <stdio.h>

typedef struct{
    long id;
    char categoria[90];
    float valor;
    unsigned int estado;
}datos_t;

int main(int argc, char const *argv[])
{
    datos_t fileDato;
    FILE *fp;
    char opc='s';
    long id=1;

    if((fp=fopen("/var/datos.dat","wb")) == NULL){
        printf("No se pudo abrir el archivo");
        return -1; // Error
    }
    printf("Bienvenido a la carga de Archivos\n");

    do {
        printf("Ingrese la Categoria: ");
        gets(fileDato.categoria);
        printf("Ingresar el Valor: ");
        scanf("%f",&fileDato.valor);
        fileDato.id = id;
        printf("Ingrese el Estado: ");
        scanf("%d",&fileDato.estado);

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

