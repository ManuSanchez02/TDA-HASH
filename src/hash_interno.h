#ifndef __HASH_INTERNO_H__
#define __HASH_INTERNO_H__

#include "hash.h"

const int CAPACIDAD_MINIMA;
const int ERROR;
const int EXITO;
const int MULTIPLICADOR_LIMITE_REHASHEO;
const int MULTIPLICADOR_NUEVO_TAMANIO;



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


/*
 * Pre: clave debe ser distinta de NULL
 * Post: Devuelve la posicion de la tabla_hash para la respectiva clave
*/
size_t hashear(const char* clave);


/*
 * Pre: clave debe ser distinta de NULL
 * Post: Reserva memoria para el casillero que contiene a clave y elemento, y devuelve su puntero
*/
casillero_t* inicializar_casillero(const char* clave, void* elemento);


/*
 * Pre: hash y clave deben ser distintos de NULL
 * Post: Devuelve la posicion (en la lista de tabla_hash[clave_hasheada]) del casillero con la respectiva clave 
*/
int obtener_posicion_casillero(hash_t* hash, const char* clave);


/*
 * Pre: hash debe ser distinto de NULL
 * Post: Libera la tabla_hash, las listas dentro de ella, todos los casilleros dentro de las mismas
*/
void liberar_tabla_hash(hash_t* hash);


/*
 * Pre: hash debe ser distinto de NULL y multiplicador_tamanio debe ser mayor a 0
 * Post: - Multiplica la cantidad de listas en el hash por multiplicador_tamanio, insertando todos los elementos
 *       en sus nuevas posiciones
 *      - Devuelve true si fue exitoso o false en caso contrario
*/
bool rehashear(hash_t* hash, size_t multplicador_tamanio);

#endif /* __HASH_INTERNO_H__ */