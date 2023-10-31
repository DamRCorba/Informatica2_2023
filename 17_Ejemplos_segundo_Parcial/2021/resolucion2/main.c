#include <stdio.h>
#include <malloc.h>

typedef struct 
{
    char id[5];
    char ayn[30];
    unsigned int tipo;
    int b;
} datos_t;

struct  cola {
    datos_t datos;
    struct cola *ant;
}; 

typedef struct cola cola_t;

cola_t* funcion(cola_t *primero, cola_t *ultimo, datos_t datos);

int main(int argc, char const *argv[])
{
    FILE *fp;
    cola_t *p, *u=NULL, *aux=NULL;
    datos_t misDatos;

    if ((fp = fopen("../pacientes.dat", "rb+")) == NULL)
    {
        printf("NO encontre el archivo");
        return 1;
    }
    p = malloc(sizeof(cola_t));
    p->ant = NULL;
    
    
    fread(&misDatos, sizeof(datos_t), 1, fp);
    while (!feof(fp))
    {
        printf("\nDato Archivo ID: %s, Nombre: %s, Tipo: %d, B:%d", misDatos.id, misDatos.ayn, misDatos.tipo, misDatos.b);
        if ((misDatos.tipo & (1 << 3)) && (misDatos.tipo & (1 << 4)) && misDatos.b == 1){
            // llamar a la funcion y actualizar al registro
            u=funcion(p,u, misDatos);
            misDatos.tipo = misDatos.tipo & ~((1 << 3) | (1 << 4));
            fseek(fp, -1L * sizeof(datos_t), SEEK_CUR);
            fwrite(&misDatos, sizeof(datos_t), 1, fp);
        }
        fread(&misDatos, sizeof(datos_t), 1, fp);
    }

    
    
    u = p;
    while (u->ant != NULL)
    {
        printf("\nDato Cola ID: %s, Nombre: %s, Tipo: %d, B:%d", u->datos.id, u->datos.ayn, u->datos.tipo, u->datos.b);
        aux = u;
        u = u->ant;
        free(aux);
    }
    printf("\nDato Cola ID: %s, Nombre: %s, Tipo: %d, B:%d", u->datos.id, u->datos.ayn, u->datos.tipo, u->datos.b);

    return 0;
}

// 01111011 = 123
// 01100011 = 99

cola_t * funcion(cola_t *primero, cola_t *ultimo, datos_t d){    
    cola_t *aux;

    if (ultimo == NULL)
    {
        primero->datos = d;         
        ultimo = primero;        
    }
    else
    {
        aux = malloc(sizeof(datos_t));
        aux->datos = d;
        aux->ant = NULL;
        ultimo->ant = aux;
        ultimo = aux;
    }
    return ultimo;
}
