#include <stdio.h>

typedef struct
{
    long id;
    char categoria[90];
    float valor;
    unsigned int estado;
} datos_t;

long funcion(long id);

int main(int argc, char const *argv[])
{
    long user_id, respuesta;
    printf("Hola, que id queres buscar? ");
    scanf("%ld",&user_id);

    respuesta=funcion(user_id);
    if(respuesta==-1){
        printf("\nERROR, NO se pudo abrir el archivo.\n");
        return -1;
    }
    if(respuesta == 0) {
        printf("\nNo se encontro el registro solicitado.\n");
        return 0;
    }

    printf("\nQuedan %ld registros hasta el fin de archivo.\n",respuesta-1);
    return 0;
}

long funcion(long id){
    FILE *fp;
    datos_t fileData;
    long ubicacion = 0, total = 1;
    char *s;

    printf("Se busca el id %ld",id);

    if((fp=fopen("datos.dat","rb+"))==NULL){
        return -1;
    }
    fread(&fileData, sizeof(datos_t), 1, fp);
    while (!feof(fp))
    {
        printf("\nID: %ld, Categoria: %s, Valor: %f, Estado: %d", fileData.id, fileData.categoria, fileData.valor, fileData.estado);
        if(fileData.id == id){
            printf(" -> ES LA CLAVE BUSCADA");
            ubicacion = total;
            if(fileData.estado & (1<<3)){
                s = fileData.categoria;
                while(*s){
                    if(*s>='A' && *s<='Z') {
                        *s += ('a'-'A');
                    }
                    s++;
                }
                fseek(fp,-1L*sizeof(datos_t), SEEK_CUR);
                fwrite(&fileData,sizeof(datos_t),1,fp);

            }
        }
        fread(&fileData, sizeof(datos_t), 1, fp);
        total++;
    }
    if(ubicacion == 0) return 0; // No encontro el registro.
    else return (total - ubicacion);

}