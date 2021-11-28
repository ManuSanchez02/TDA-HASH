#include "hash.h"
#include "hash_interno.h"

const int CAPACIDAD_MINIMA = 3;
const int ERROR = -1;
const int EXITO = 0;
const int MULTIPLICADOR_LIMITE_REHASHEO = 3;
const int MULTIPLICADOR_NUEVO_TAMANIO = 5;

typedef struct informacion_funcion {
    bool (*funcion)(hash_t* hash, const char* clave, void* aux);
    hash_t* hash;
    void* aux;
    bool retorno;
} datos_funcion_t;


hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
    if(capacidad_inicial < CAPACIDAD_MINIMA)
        capacidad_inicial = CAPACIDAD_MINIMA;

    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash)
        return NULL;

    hash->cantidad_maxima_tabla = capacidad_inicial;
    hash->cantidad_actual_casilleros = 0;
    hash->cantidad_actual_tabla = 0;
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

    if(hash_cantidad(hash) > hash->cantidad_maxima_tabla*MULTIPLICADOR_LIMITE_REHASHEO){
        if(!rehashear(hash, MULTIPLICADOR_NUEVO_TAMANIO))
            return ERROR;
    }

    size_t clave_hasheada = hashear(clave) % hash->cantidad_maxima_tabla;

    int pos_casillero = obtener_posicion_casillero(hash, clave);
    if(pos_casillero != -1){
        casillero_t* casillero_a_reemplazar = lista_elemento_en_posicion(hash->tabla_hash[clave_hasheada], pos_casillero);
        if(hash->destructor)
            hash->destructor(casillero_a_reemplazar->valor);

        casillero_a_reemplazar->valor = elemento;
        return EXITO;
    }

    

    casillero_t* casillero = inicializar_casillero(clave, elemento);
    if(!casillero)
        return ERROR;

    if(!hash->tabla_hash[clave_hasheada]){
        lista_t* lista = lista_crear();
        if(!lista)
            return ERROR;
        
        hash->tabla_hash[clave_hasheada] = lista;
        hash->cantidad_actual_tabla++;
    }



    if(!lista_insertar(hash->tabla_hash[clave_hasheada], casillero))
        return ERROR;

    hash->cantidad_actual_casilleros++;
    return EXITO; 
}


int hash_quitar(hash_t* hash, const char* clave){
    if(!hash || !clave)
        return ERROR;


    size_t clave_hasheada = hashear(clave) % hash->cantidad_maxima_tabla;

    int pos_casillero = obtener_posicion_casillero(hash, clave);
    if(pos_casillero != -1){
        casillero_t* casillero = lista_quitar_de_posicion(hash->tabla_hash[clave_hasheada], pos_casillero);
        free(casillero->clave);
        if(hash->destructor)
            hash->destructor(casillero->valor);
        
        free(casillero);
        hash->cantidad_actual_casilleros--;
        
        return EXITO;
    }

    return ERROR;
}


void* hash_obtener(hash_t* hash, const char* clave){
    if(!hash || !clave)
        return NULL;

    size_t clave_hasheada = hashear(clave) % hash->cantidad_maxima_tabla;
    int pos_casillero = obtener_posicion_casillero(hash, clave);

    if(pos_casillero == -1)
        return NULL;
    
    casillero_t* casillero = lista_elemento_en_posicion(hash->tabla_hash[clave_hasheada], pos_casillero);
    return casillero->valor;
}


bool hash_contiene(hash_t* hash, const char* clave){
    if(!hash || !clave)
        return false;

    int pos_casillero = obtener_posicion_casillero(hash, clave);

    return (pos_casillero != -1);
}


size_t hash_cantidad(hash_t* hash){
    if(!hash)
        return 0;
        
    return hash->cantidad_actual_casilleros;
}


void hash_destruir(hash_t* hash){
    if(!hash)
        return;

    liberar_tabla_hash(hash);

    free(hash);
}

/*
 * Pre: _casillero y _datos_funcion deben ser distintos de NULL
        - _casillero debe ser un puntero a casillero_t
        - _datos_funcion debe ser un puntero a datos_funcion_t
 * Post: devuelve true si datos_funcion->funcion(datos_funcion->hash, casillero->clave, datos_funcion->aux) == false, y false
         en caso contrario
*/
bool hash_con_cada_clave_aux(void* _casillero, void* _datos_funcion){
    if(!_casillero || !_datos_funcion)
        return true;

    casillero_t* casillero = _casillero;
    datos_funcion_t* datos_funcion = _datos_funcion;


    return !(datos_funcion->funcion(datos_funcion->hash, casillero->clave, datos_funcion->aux));
}


size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
    if(!hash || ! funcion)
        return 0;

    datos_funcion_t datos_funcion;


    datos_funcion.funcion = funcion;
    datos_funcion.hash = hash;
    datos_funcion.aux = aux;
    datos_funcion.retorno = false;

    size_t contador_iteraciones = 0;
    int i = 0;
    while(i < hash->cantidad_maxima_tabla && datos_funcion.retorno == false){
        contador_iteraciones += lista_con_cada_elemento(hash->tabla_hash[i], hash_con_cada_clave_aux, &datos_funcion);
        i++;
    }



    return contador_iteraciones;
}