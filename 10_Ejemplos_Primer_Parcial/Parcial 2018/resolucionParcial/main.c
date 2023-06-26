#include <stdio.h>
#include <string.h>

typedef struct
{
    long id;
    char descripcion[90];
    int tipo;
    char marca; // Marca 'A': Alta  'B': Baja)
} datos_t;

datos_t funcion (long id);

int main(int argc, char const *argv[])
{
    long id;
    datos_t registro_devuelto;

    printf("\nIngrese el Id que desea buscar: ");
    scanf("%d",&id);
    registro_devuelto = funcion(id);
    if(registro_devuelto.id == -1) {
        printf("\nError\n");
        return -1;
    }else {
        printf("\nID: %d, Descripcion: %s, Tipo: %d, Marca: %c", registro_devuelto.id, registro_devuelto.descripcion, registro_devuelto.tipo, registro_devuelto.marca);
    }
    return 0;
}

datos_t funcion(long id){
    FILE *fp, *baja;
    datos_t registro;
    char *s;

    if((fp = fopen("datos.dat","rb+"))== NULL){
        printf("No se pudo abrir el archivo de datos");
        registro.id = -1;
        return registro;
    }

    if ((baja = fopen("baja.dat", "ab")) == NULL)
    {
        printf("No se pudo abrir el archivo de bajas");
        registro.id = -1;
        return registro;
    }

    fread(&registro, sizeof(datos_t), 1, fp);
    while (!feof(fp))
    {
        if ( registro.id == id ) {
            if(registro.marca == 'A') {
                strcpy(registro.descripcion,"Registro Procesado");
                registro.marca = 'B';
                fseek(fp,-1L*sizeof(datos_t),SEEK_CUR);
                fwrite(&registro,sizeof(datos_t),1,fp);
                return registro;
            }
            if(registro.marca == 'B') {
                s = registro.descripcion;
                while(*s){
                    if(*s == 'a' || *s == 'o') *s = 'e';
                    s++;
                }
                fwrite(&registro, sizeof(datos_t), 1, baja);
                return registro;

            }
        }
        fread(&registro, sizeof(datos_t), 1, fp);
    }
    registro.id = -1;
    printf("No se encontro el registro");
    return registro;
}