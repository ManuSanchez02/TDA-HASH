#include "hash_interno.h"
#include "hash.h"


size_t hashear(const char* clave){
    if(!clave)
        return 0;
    
    size_t clave_hasheada = (size_t)clave[0];
    int i = 1;

    while(clave[i] != '\0'){
        clave_hasheada *= clave[i];
        i++;
    }

    return clave_hasheada;
}

casillero_t* inicializar_casillero(const char* clave, void* elemento){
    if(!clave)
        return NULL;

    casillero_t* casillero = malloc(sizeof(casillero_t));
    if(!casillero)
        return NULL;

    casillero->clave = malloc(sizeof(char) * (strlen(clave)+1));
    if(!casillero->clave)
        return NULL;

    strcpy(casillero->clave, clave);
    casillero->valor = elemento;

    return casillero;
}

bool destructor_de_datos_aux(void* _casillero, void* _hash){
    hash_t* hash = _hash;
    casillero_t* casillero = _casillero;

    if(!hash || !casillero)
        return false;

    if(hash->destructor)
        hash->destructor(casillero->valor);

    free(casillero->clave);
    free(casillero);

    return true;    
}

bool copiar_casilleros_hash(hash_t* destino, hash_t* origen){
    /*for(size_t i = 0; i < origen->cantidad_actual_casilleros){
        char* clave;
        hash_con_cada_clave
    }*/

    return false;
}

bool rehashear(hash_t* hash){
    if(!hash)
        return false;

    hash_t* hash_nuevo = malloc(sizeof(hash_t));
    if(!hash_nuevo)
        return false;

    size_t nuevo_tamanio_maximo = MULTIPLICADOR_NUEVO_TAMANIO*hash->cantidad_maxima_tabla;

    hash_nuevo->cantidad_actual_tabla = 0;
    hash_nuevo->destructor = hash->destructor;
    hash_nuevo->cantidad_actual_casilleros = hash->cantidad_actual_casilleros;
    hash_nuevo->cantidad_maxima_tabla = nuevo_tamanio_maximo;
    hash_nuevo->tabla_hash = calloc(nuevo_tamanio_maximo, sizeof(lista_t*));
    if(!hash_nuevo->tabla_hash){
        free(hash_nuevo);
        return false;
    }

    return copiar_casilleros_hash(hash_nuevo, hash);
}


int obtener_posicion_casillero(hash_t* hash, const char* clave){
    if(!clave)
        return -1;

    size_t clave_hasheada = hashear(clave) % hash->cantidad_maxima_tabla;

    lista_iterador_t* iterador = lista_iterador_crear(hash->tabla_hash[clave_hasheada]);
    if(!iterador)
        return -1;


    casillero_t* casillero_actual = NULL;
    size_t i = 0;
    int posicion = -1;
    while(lista_iterador_tiene_siguiente(iterador)){
        casillero_actual = lista_iterador_elemento_actual(iterador);
        if(strcmp(casillero_actual->clave, clave) == 0)
            posicion = i;

        lista_iterador_avanzar(iterador);
        i++;
    }
    free(iterador);

    return posicion;
}
