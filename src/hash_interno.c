#include "hash_interno.h"

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