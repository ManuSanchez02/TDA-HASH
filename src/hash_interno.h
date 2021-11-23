#ifndef __HASH_INTERNO_H__
#define __HASH_INTERNO_H__

#include "hash.h"

const int CAPACIDAD_MINIMA;
const int TAMANIO_MAXIMO_ARBOL;
const int ERROR;
const int EXITO;


struct hash{
    size_t cantidad_maxima_tabla;
    size_t cantidad_actual_tabla; // TODO: REVISAR SI ES UTIL
    size_t cantidad_actual_casilleros;
    hash_destruir_dato_t destructor;
    lista_t** tabla_hash;
};

typedef struct casillero{
    char* clave;
    void* valor;
} casillero_t;

size_t hashear(const char* clave);

casillero_t* inicializar_casillero(const char* clave, void* elemento);

bool destructor_de_datos_aux(void* elemento, void* _hash);


#endif /* __HASH_INTERNO_H__ */