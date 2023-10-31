#include <stdio.h>

typedef struct 
{
    char id[5];
    char ayn[30];
    unsigned int tipo;
    int b;
}datos_t;

int main(int argc, char const *argv[])
{
    FILE *fp;
    datos_t misDatos;
    

    if((fp = fopen("../pacientes.dat","rb")) == NULL) {
        printf("NO encontre el archivo");
        return 1;

    }

    fread(&misDatos,sizeof(datos_t),1,fp);

    while (!feof(fp))
    {
        printf("\nID: %s, Nombre: %s, Tipo: %d, B:%d", misDatos.id, misDatos.ayn, misDatos.tipo, misDatos.b);
        fread(&misDatos, sizeof(datos_t), 1, fp);
    }
    fclose(fp);


    return 0;
}

