#include "hash.h"
#include "hash_interno.h"

const int CAPACIDAD_MINIMA = 3;
const int TAMANIO_MAXIMO_ARBOL = 10;
const int ERROR = -1;
const int EXITO = 0;

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
    if(capacidad_inicial < CAPACIDAD_MINIMA)
        capacidad_inicial = CAPACIDAD_MINIMA;

    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash)
        return NULL;

    hash->capacidad_maxima = capacidad_inicial;
    hash->cantidad_actual = 0;
    hash->destructor = destruir_elemento;
    hash->tabla_hash = calloc(capacidad_inicial, sizeof(lista_t*));

    if(!hash->tabla_hash){
        free(hash);
        return NULL;
    }

    return hash;
}


int hash_insertar(hash_t* hash, const char* clave, void* elemento){
    if(!hash || !clave)
        return ERROR;
    
    size_t clave_hasheada = hashear(clave) % hash->capacidad_maxima;
    casillero_t* casillero = inicializar_casillero(clave, elemento);
    if(!casillero)
        return ERROR;

    if(!hash->tabla_hash[clave_hasheada]){
        lista_t* lista = lista_crear();
        if(!lista)
            return ERROR;
        
        hash->cantidad_actual++;
        hash->tabla_hash[clave_hasheada] = lista;
    }

    if(!lista_insertar(hash->tabla_hash[clave_hasheada], casillero))
        return ERROR;

    return EXITO; // TODO: Rehashear despues de cierta cantidad
}


int hash_quitar(hash_t* hash, const char* clave){
    return 0;
}


void* hash_obtener(hash_t* hash, const char* clave){
    return NULL;
}


bool hash_contiene(hash_t* hash, const char* clave){
    return false;
}


size_t hash_cantidad(hash_t* hash){
    if(!hash)
        return 0;
        
    return hash->cantidad_actual;
}


void hash_destruir(hash_t* hash){
    if(!hash)
        return;

    for(size_t i = 0; i < hash->capacidad_maxima; i++){
        lista_con_cada_elemento(hash->tabla_hash[i], destructor_de_datos_aux, hash);
        lista_destruir(hash->tabla_hash[i]);
    }

    free(hash->tabla_hash);
    free(hash);
}


size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
    return 0;
}