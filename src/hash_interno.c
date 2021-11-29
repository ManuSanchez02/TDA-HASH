#include "hash_interno.h"


size_t hashear(const char* clave){
    if(!clave)
        return 0;
    
    size_t clave_hasheada = 0;
    size_t i = 0;

    while(clave[i] != '\0'){
        clave_hasheada += clave[i];
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


/*
 * Pre: - _casillero y _hash deben ser distintos de NULL
        - _casillero debe ser un puntero a un casillero
        - _hash debe ser un puntero a un hash
 * Post: Libera la memoria de la clave, el casillero, y si el hash tiene una
 *       funcion de destruccion, tambien libera el elemento
*/
bool destructor_de_datos_aux(void* _casillero, void* _hash){
    if(!_hash || !_casillero)
        return false;

    hash_t* hash = _hash;
    casillero_t* casillero = _casillero;

    if(hash->destructor)
        hash->destructor(casillero->valor);

    free(casillero->clave);
    free(casillero);

    return true;    
}


int obtener_posicion_casillero(hash_t* hash, const char* clave){
    if(!clave)
        return -1;

    size_t clave_hasheada = hashear(clave) % hash->cantidad_maxima_listas;

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


void liberar_tabla_hash(hash_t* hash){
    if(!hash)
        return;
    
    for(size_t i = 0; i < hash->cantidad_maxima_listas; i++){
        lista_con_cada_elemento(hash->tabla_hash[i], destructor_de_datos_aux, hash);
        lista_destruir(hash->tabla_hash[i]);
    }

    free(hash->tabla_hash);
}


/*
 * Pre: - origen, clave y destino deben ser distintos de NULL
        - destino debe ser un puntero hash
 * Post: - Inserta en _destino, el casillero de origen correspondiente a clave
         - Devuelve false si pudo insertae el elemento y true en caso contrario
*/
bool copiar_casillero(hash_t* origen, const char* clave, void* _destino){
    if(!origen || !clave || !_destino)
        return true;

    hash_t* destino = _destino;

    void* elemento_en_posicion = hash_obtener(origen, clave);

    if(hash_insertar(destino, clave, elemento_en_posicion) == EXITO)
        return false; // !EXPLICAR
    else
        return true; // !EXPLICAR
}


bool rehashear(hash_t* hash, size_t multplicador_tamanio){
    if(!hash || !hash->tabla_hash || multplicador_tamanio == 0)
        return false;

    hash_t* hash_nuevo = hash_crear(hash->destructor, hash->cantidad_maxima_listas*MULTIPLICADOR_NUEVO_TAMANIO);
    if(!hash_nuevo)
        return false;


    if(hash_con_cada_clave(hash, copiar_casillero, hash_nuevo) == hash_cantidad(hash)){
        hash->destructor = NULL; // !EXPLICAR
        liberar_tabla_hash(hash);
        *hash = *hash_nuevo;
        free(hash_nuevo);
        return true;
    }else{
        hash_nuevo->destructor = NULL; // !EXPLICAR
        hash_destruir(hash_nuevo);
        return false;
    }
}