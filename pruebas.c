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
    pa2m_afirmar(hash->capacidad_maxima == 5, "El hash se crea con la capacidad correcta");

    hash_destruir(hash);
}

void prueboCrearUnHashConCapacidadMenorALaMinima_ySeCreaConLaCapacidadMinima(){
    hash_t* hash = hash_crear(NULL, 2);

    pa2m_afirmar(hash != NULL, "Puedo crear un hash con capacidad menor a la minima");
    pa2m_afirmar(hash->capacidad_maxima == 3, "El hash se crea con la capacidad correcta");

    hash_destruir(hash);
}

void dadoUnHashVacio_puedoInsertarUnElemento(){
    hash_t* hash = hash_crear(NULL, 1);
    int elemento = 5;

    pa2m_afirmar((hash_insertar(hash, "abc", &elemento) == EXITO), "Puedo insertar el elemento");
    pa2m_afirmar((hash_cantidad(hash) == 1), "El hash tiene el tamanio correcto");

    hash_destruir(hash);
}


int main(){
    pa2m_nuevo_grupo("Pruebas de creacion y destruccion de Hash");
    prueboCrearYDestruirUnHash();
    prueboCrearUnHashConCapacidadMayorALaMinima_ySeCreaConLaCapacidadIndicada();
    prueboCrearUnHashConCapacidadMenorALaMinima_ySeCreaConLaCapacidadMinima();

    pa2m_nuevo_grupo("Pruebas de insercion");
    dadoUnHashVacio_puedoInsertarUnElemento();


    return pa2m_mostrar_reporte();
}