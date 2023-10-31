#include <stdio.h>
#include <malloc.h>

typedef struct
{
    int cl;            // clave
    char d[30];        // descripcion
    unsigned int tipo; // bit 4 en 1 valores positivos, bit 4 en 0 valores negativos
    unsigned int valor;
    char m; // A-Alta, B-Baja
} datos_t;

struct pila
{
    long posicion;
    int cl;
    struct pila *sig;
};

typedef struct pila pila_t;

pila_t *funcion(int cl, pila_t *pila);

int main(int argc, char const *argv[])
{
    pila_t *pila = NULL, *aux;
    int clave = 0;

    pila = malloc(sizeof(pila_t));
    pila->cl = -1;

    do
    {
        printf("\nQue clave desea Buscar? 0 para salir: ");
        scanf("%d", &clave);
        if (clave)
            pila = funcion(clave, pila);
    } while (clave != 0);
    printf("\nImprimimos la pila");

    while (pila->sig != NULL)
        
    {
        printf("\nCL: %d, Posicion: %d", pila->cl, pila->posicion);
        aux = pila;
        pila = pila->sig;
        free(aux);
    }
    printf("\nCL: %d, Posicion: %d", pila->cl, pila->posicion);

    return 0;
}

pila_t *funcion(int clave, pila_t *pila)
{
    FILE *fp;
    pila_t *au;
    datos_t datos;
    long pos = 0;

    if ((fp = fopen("../datos.dat", "rb")) == NULL)
    {
        printf("\nNo se pudo abrir el archivo");
        return pila;
    }

    fread(&datos, sizeof(datos_t), 1, fp);
    while (!feof(fp))
    {
        printf("\nCL: %d, Descripcion:%s, Tipo: %d, Valor: %d, marca:%c", datos.cl, datos.d, datos.tipo, datos.valor, datos.m);

        if (datos.cl == clave)
        { // esta es la clave que busco
            if ((datos.tipo & (1 << 4)) && (datos.m == 'A'))
            { // bit 4 en 1 entonces apilo
                printf("\nApilo.");

                if (pila->cl == -1)
                { // el primero de la pila
                    pila->cl = clave;
                    pila->posicion = pos;
                    pila->sig = NULL;
                    fclose(fp);
                    return pila;
                }
                else
                {
                    au = malloc(sizeof(pila_t));
                    au->cl = clave;
                    au->posicion = pos;
                    au->sig = pila;
                    fclose(fp);
                    return au;
                }
                // au->cl = clave;
                // au->posicion = pos;
                // au->sig = pila;
                // fclose(fp);
                // return au;
            }
            else
            { // no apilo
                printf("\nNo Apilo.");
                fclose(fp);
                return pila;
            }
        }
        pos++;
        fread(&datos, sizeof(datos_t), 1, fp);
    }
    printf("\nNo se encontro el registro");
    fclose(fp);
    return pila;
}