#include "pa2mm.h"
#include "src/hash.h"
#include "src/hash_interno.h"

void destructor_de_enteros(void* elemento){
    free(elemento);
}

void prueboCrearYDestruirUnHash(){
    hash_t* hash = hash_crear(NULL, 5);

    pa2m_afirmar(hash != NULL, "Puedo crear un hash");

    hash_destruir(hash);
}

void prueboCrearUnHashConCapacidadMayorALaMinima_ySeCreaConLaCapacidadIndicada(){
    hash_t* hash = hash_crear(NULL, 5);

    pa2m_afirmar(hash != NULL, "Puedo crear un hash con capacidad mayor a la minima");
    pa2m_afirmar(hash->cantidad_maxima_tabla == 5, "El hash se crea con la capacidad correcta");

    hash_destruir(hash);
}

void prueboCrearUnHashConCapacidadMenorALaMinima_ySeCreaConLaCapacidadMinima(){
    hash_t* hash = hash_crear(NULL, 2);

    pa2m_afirmar(hash != NULL, "Puedo crear un hash con capacidad menor a la minima");
    pa2m_afirmar(hash->cantidad_maxima_tabla == 3, "El hash se crea con la capacidad correcta");

    hash_destruir(hash);
}

void dadoUnHashVacio_puedoInsertarUnElemento(){
    hash_t* hash = hash_crear(NULL, 1);
    int elemento = 5;

    pa2m_afirmar((hash_insertar(hash, "abc", &elemento) == EXITO), "Puedo insertar el elemento");
    pa2m_afirmar((hash_insertar(hash, NULL, &elemento) == ERROR), "No puedo insertar el elemento sin clave");
    pa2m_afirmar((hash_cantidad(hash) == 1), "El hash tiene el tamanio correcto");

    hash_destruir(hash);
}

void dadoUnHashVacio_puedoInsertarUnElementoYLiberarloCorrectamente(){
    hash_t* hash = hash_crear(destructor_de_enteros, 1);
    int* elemento = malloc(sizeof(int));
    if(!elemento)
        return;

    *elemento = 5;

    pa2m_afirmar((hash_insertar(hash, "abc", elemento) == EXITO), "Puedo insertar el elemento del heap");
    pa2m_afirmar((hash_cantidad(hash) == 1), "El hash tiene el tamanio correcto");

    hash_destruir(hash);
}

void dadoUnHashVacio_puedoInsertarVariosElementos_yLiberarlosCorrectamente(){
    hash_t* hash = hash_crear(destructor_de_enteros, 1);

    int* elemento1 = malloc(sizeof(int));
    int* elemento2 = malloc(sizeof(int));
    int* elemento3 = malloc(sizeof(int));
    int* elemento4 = malloc(sizeof(int));
    int* elemento5 = malloc(sizeof(int));
    int* elemento6 = malloc(sizeof(int));
    if(!elemento1 || !elemento2 || !elemento3 || !elemento4 || !elemento5 || !elemento6)
        return;

    *elemento1 = 5;
    *elemento2 = 2;
    *elemento3 = 5;
    *elemento4 = 7;
    *elemento5 = 21;
    *elemento6 = 8;

    pa2m_afirmar((hash_insertar(hash, "abc", elemento1) == EXITO), "Puedo insertar el elemento del heap");
    pa2m_afirmar((hash_insertar(hash, "r", elemento2) == EXITO), "Puedo insertar el elemento del heap");
    pa2m_afirmar((hash_insertar(hash, "qw", elemento3) == EXITO), "Puedo insertar el elemento del heap");
    pa2m_afirmar((hash_insertar(hash, "hgtert", elemento4) == EXITO), "Puedo insertar el elemento del heap");
    pa2m_afirmar((hash_insertar(hash, "dasdsadfgdgreerew", elemento5) == EXITO), "Puedo insertar el elemento del heap");
    pa2m_afirmar((hash_insertar(hash, "vbd", elemento6) == EXITO), "Puedo insertar el elemento del heap");
    pa2m_afirmar((hash_cantidad(hash) == 6), "El hash tiene el tamanio correcto");

    hash_destruir(hash);
}

void dadoUnHashVacio_puedoInsertarMuchosElementos(){
    hash_t* hash = hash_crear(NULL, 25);
    int vector[10000];

    bool hubo_error = false;

    for(int i = 0; i < 10000; i++){
        vector[i] = i;
        if(hash_insertar(hash, "A"+ i%26, &vector[i]) == ERROR){
            hubo_error = true;
        }
    }

    pa2m_afirmar((hubo_error == false), "No hubo error al insertar 10000 elementos");

    hash_destruir(hash);
}


int main(){
    pa2m_nuevo_grupo("Pruebas de creacion y destruccion de Hash");
    prueboCrearYDestruirUnHash();
    prueboCrearUnHashConCapacidadMayorALaMinima_ySeCreaConLaCapacidadIndicada();
    prueboCrearUnHashConCapacidadMenorALaMinima_ySeCreaConLaCapacidadMinima();

    pa2m_nuevo_grupo("Pruebas de insercion");
    dadoUnHashVacio_puedoInsertarUnElemento();
    dadoUnHashVacio_puedoInsertarUnElementoYLiberarloCorrectamente();
    dadoUnHashVacio_puedoInsertarVariosElementos_yLiberarlosCorrectamente();
    dadoUnHashVacio_puedoInsertarMuchosElementos();


    return pa2m_mostrar_reporte();
}