#include "pa2mm.h"
#include "src/hash.h"
#include "src/hash_interno.h"

/*
 * Pre: elemento debe ser un puntero a int
 * Post: Libera la memoria de elemento
*/
void destructor_de_enteros(void* elemento){
    free(elemento);
}

/*
 * Pre:
 * Post: Si hash o clave son NULL, devuelve true. Devuelve false en caso contrario
*/
bool recorrer_todo(hash_t* hash, const char* clave, void* aux){
    if(!hash || !clave)
        return true;

    hash = hash;
    clave = clave;
    aux = aux;

    return false;
}

/*
 * Pre:
 * Post: Devuelve false si contador es menor a 4 y true en caso contrario. Si hash o clave son NULL, tambien devuelve true
*/
bool mayor_a_4(hash_t* hash, const char* clave, void* _contador){
    if(!hash || !clave)
        return true;

    int* contador = _contador;
    hash = hash;
    clave = clave;

    if(*contador < 4){
        (*contador)++;
        return false;
    }

    return true;
}

void dadoUnHashNULL_intentoRealizarOperaciones(){
    hash_t* hash = NULL;
    int elemento = 5;

    pa2m_afirmar((hash_cantidad(hash) == 0), "El hash NULL tiene el tamanio 0 al ser creado");
    pa2m_afirmar((hash_insertar(hash, "abc", &elemento) == ERROR), "No puedo insertar el elemento en hash NULL");
    pa2m_afirmar((hash_contiene(hash, "abc") == false), "No puedo encontrar el elemento en el hash NULL");
    pa2m_afirmar((hash_obtener(hash, "abc") == NULL), "No puedo obtener el elemento del hash NULL");
    pa2m_afirmar((hash_quitar(hash, "abc") == ERROR), "No puedo quitar elementos en un hash NULL");
    pa2m_afirmar((hash_cantidad(hash) == 0), "El hash NULL tiene el tamanio 0 despues de las operaciones");
}

void dadoUnHashVacio_intentoRealizarOperaciones(){
    hash_t* hash = hash_crear(NULL, 5);

    pa2m_afirmar((hash_cantidad(hash) == 0), "El hash vacio tiene el tamanio 0 al ser creado");
    pa2m_afirmar((hash_contiene(hash, "abc") == false), "No puedo encontrar el elemento en el hash vacio");
    pa2m_afirmar((hash_obtener(hash, "abc") == NULL), "No puedo obtener el elemento del hash vacio");
    pa2m_afirmar((hash_quitar(hash, "abc") == ERROR), "No puedo quitar elementos en un hash vacio");

    hash_destruir(hash);
}

void prueboCrearYDestruirUnHash(){
    hash_t* hash = hash_crear(NULL, 5);

    pa2m_afirmar(hash != NULL, "Puedo crear un hash");

    hash_destruir(hash);
}

void prueboCrearUnHashConCapacidadMayorALaMinima_ySeCreaConLaCapacidadIndicada(){
    hash_t* hash = hash_crear(NULL, 5);

    pa2m_afirmar(hash != NULL, "Puedo crear un hash con capacidad mayor a la minima");
    pa2m_afirmar(hash->cantidad_maxima_listas == 5, "El hash se crea con la capacidad correcta");

    hash_destruir(hash);
}

void prueboCrearUnHashConCapacidadMenorALaMinima_ySeCreaConLaCapacidadMinima(){
    hash_t* hash = hash_crear(NULL, 2);

    pa2m_afirmar(hash != NULL, "Puedo crear un hash con capacidad menor a la minima");
    pa2m_afirmar(hash->cantidad_maxima_listas == 3, "El hash se crea con la capacidad correcta");

    hash_destruir(hash);
}

void dadoUnHashVacio_puedoInsertarUnElemento(){
    hash_t* hash = hash_crear(NULL, 1);
    int elemento = 5;

    pa2m_afirmar((hash_insertar(hash, "abc", &elemento) == EXITO), "Puedo insertar el elemento");
    pa2m_afirmar((hash_contiene(hash, "abc") == true), "Puedo encontrar el elemento en el hash");
    pa2m_afirmar((hash_obtener(hash, "abc") == &elemento), "Puedo obtener el elemento del hash");
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
        pa2m_afirmar((hash_contiene(hash, "abc") == true), "Puedo encontrar el elemento en el hash");
    pa2m_afirmar((hash_obtener(hash, "abc") == elemento), "Puedo obtener el elemento del hash");
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

    pa2m_afirmar((hash_contiene(hash, "dasdsadfgdgreerew") == true), "Puedo encontrar uno de los elementos en el hash");
    pa2m_afirmar((hash_obtener(hash, "qw") == elemento3), "Puedo obtener uno de los elementos del hash");

    hash_destruir(hash);
}

void dadoUnHashVacio_puedoInsertarMuchosElementos(){
    hash_t* hash = hash_crear(NULL, 5);
    int vector[1000];

    bool hubo_error = false;

    for(int i = 0; i < 1000; i++){
        vector[i] = i;
        char* clave = malloc(6*sizeof(char));
        sprintf(clave, "%i", i);
        if(hash_insertar(hash, clave, &vector[i]) == ERROR){
            hubo_error = true;
        }
        free(clave);
    }

    pa2m_afirmar((hubo_error == false), "No hubo error al insertar 1000 elementos");
    pa2m_afirmar((hash_cantidad(hash) == 1000), "La cantidad de elementos es 1000");

    hash_destruir(hash);
}

void dadoUnHashConUnElemento_puedoSobreescribirlo(){
    hash_t* hash = hash_crear(NULL, 3);
    int elemento1 = 5;
    int elemento2 = 23;

    hash_insertar(hash, "abc", &elemento1);

    pa2m_afirmar((hash_insertar(hash, "abc", &elemento2) == EXITO), "Puedo sobreescribir el elemento existente");

    pa2m_afirmar((hash_contiene(hash, "abc") == true), "El elemento esta en el hash");
    pa2m_afirmar((hash_obtener(hash, "abc") == &elemento2), "El elemento con la clave asignada es el nuevo");
    pa2m_afirmar((hash_cantidad(hash) == 1), "El hash tiene 1 elemento");

    pa2m_afirmar((hash_quitar(hash, "abc") == EXITO), "Puedo eliminar el elemento");

    hash_destruir(hash);
}

void dadoUnHashConVariosElemento_puedoSobreescribirAlgunos(){
    hash_t* hash = hash_crear(NULL, 3);
    int elemento1 = 5;
    int elemento2 = -65;
    int elemento3 = 45;
    int elemento4 = 2;
    int elemento5 = 99;
    int elemento6 = 99999;
    int elemento7 = 4;
    int elemento8 = 10;

    hash_insertar(hash, "abc", &elemento1);
    hash_insertar(hash, "dsa", &elemento2);
    hash_insertar(hash, "hrtyr", &elemento3);
    hash_insertar(hash, "vds", &elemento4);
    hash_insertar(hash, "xzcxzcxz", &elemento5);

    pa2m_afirmar((hash_insertar(hash, "hrtyr", &elemento6) == EXITO), "Puedo sobreescribir el elemento 3");
    pa2m_afirmar((hash_contiene(hash, "hrtyr") == true), "El elemento esta en el hash");
    pa2m_afirmar((hash_obtener(hash, "hrtyr") == &elemento6), "El elemento con la clave asignada es el nuevo");
    pa2m_afirmar((hash_cantidad(hash) == 5), "El hash tiene 5 elementos");

    pa2m_afirmar((hash_insertar(hash, "dsa", &elemento7) == EXITO), "Puedo sobreescribir el elemento 2");
    pa2m_afirmar((hash_contiene(hash, "dsa") == true), "El elemento esta en el hash");
    pa2m_afirmar((hash_obtener(hash, "dsa") == &elemento7), "El elemento con la clave asignada es el nuevo");
    pa2m_afirmar((hash_cantidad(hash) == 5), "El hash tiene 5 elementos");

    pa2m_afirmar((hash_insertar(hash, "hrtyr", &elemento8) == EXITO), "Puedo sobreescribir el elemento 3 nuevamente");
    pa2m_afirmar((hash_contiene(hash, "hrtyr") == true), "El elemento esta en el hash");
    pa2m_afirmar((hash_obtener(hash, "hrtyr") == &elemento8), "El elemento con la clave asignada es el nuevo");
    pa2m_afirmar((hash_cantidad(hash) == 5), "El hash tiene 5 elementos");

    pa2m_afirmar((hash_quitar(hash, "dsa") == EXITO), "Puedo eliminar el elemento sobreescrito");
    pa2m_afirmar((hash_quitar(hash, "hrtyr") == EXITO), "Puedo eliminar el elemento sobreescrito");

    hash_destruir(hash);
}

void dadoUnHashConUnElemento_puedoQuitarlo_yEsteQuedaVacio(){
    hash_t* hash = hash_crear(NULL, 3);
    int elemento = 5;

    hash_insertar(hash, "abc", &elemento);

    pa2m_afirmar((hash_quitar(hash, "abc") == EXITO), "Puedo eliminar el elemento");
    pa2m_afirmar((hash_cantidad(hash) == 0), "El hash esta vacio");
    pa2m_afirmar((hash_contiene(hash, "abc") == false), "El elemento no esta en el hash");
    pa2m_afirmar((hash_obtener(hash, "abc") == NULL), "No puedo obtener el elemento que ya no esta en el hash");


    hash_destruir(hash);
}

void dadoUnHashConVariosElementos_puedoQuitarAlgunos_yElEstadoEsCorrecto(){
    hash_t* hash = hash_crear(NULL, 7);
    int elemento1 = 5;
    int elemento2 = 2;
    int elemento3 = 6;
    int elemento4 = 6;
    int elemento5 = 1;

    hash_insertar(hash, "abc", &elemento1);
    hash_insertar(hash, "dfs", &elemento2);
    hash_insertar(hash, "fds", &elemento3);
    hash_insertar(hash, "gfd", &elemento4);
    hash_insertar(hash, "gfa", &elemento5);

    pa2m_afirmar((hash_quitar(hash, "dfs") == EXITO), "Puedo eliminar un elemento");
    pa2m_afirmar((hash_cantidad(hash) == 4), "El hash tiene 4 elementos");
    pa2m_afirmar((hash_contiene(hash, "dfs") == false), "El elemento no esta en el hash");
    pa2m_afirmar((hash_obtener(hash, "dfs") == NULL), "No puedo obtener el elemento que ya no esta en el hash");

    pa2m_afirmar((hash_quitar(hash, "fds") == EXITO), "Puedo eliminar un elemento");
    pa2m_afirmar((hash_cantidad(hash) == 3), "El hash tiene 3 elementos");
    pa2m_afirmar((hash_contiene(hash, "fds") == false), "El elemento no esta en el hash");
    pa2m_afirmar((hash_obtener(hash, "fds") == NULL), "No puedo obtener el elemento que ya no esta en el hash");

    pa2m_afirmar((hash_quitar(hash, "abc") == EXITO), "Puedo eliminar un elemento");
    pa2m_afirmar((hash_cantidad(hash) == 2), "El hash tiene 2 elementos");
    pa2m_afirmar((hash_contiene(hash, "abc") == false), "El elemento no esta en el hash");
    pa2m_afirmar((hash_obtener(hash, "abc") == NULL), "No puedo obtener el elemento que ya no esta en el hash");


    hash_destruir(hash);
}

void dadoUnHashNULL_elIteradorInternoDevuelve0Elementos(){
    hash_t* hash = NULL;

    pa2m_afirmar((hash_con_cada_clave(hash, recorrer_todo, NULL) == 0), "Iterar sobre un hash NULL devuelve 0 elementos iterados");
}

void dadoUnHashVacio_elIteradorInternoDevuelve0Elementos(){
    hash_t* hash = hash_crear(NULL, 3);

    pa2m_afirmar((hash_con_cada_clave(hash, recorrer_todo, NULL) == 0), "Iterar sobre un hash vacio devuelve 0 elementos iterados");

    hash_destruir(hash);
}

void dadoUnHash_elIteradorInternoConFuncionNULLDevuelve0Elementos(){
    hash_t* hash = hash_crear(NULL, 3);

    pa2m_afirmar((hash_con_cada_clave(hash, NULL, NULL) == 0), "Iterar sobre un hash con una funcion NULL devuelve 0 elementos iterados");

    hash_destruir(hash);
}

void dadoUnHashConElementos_recorroTodosLosElementos(){
    hash_t* hash = hash_crear(NULL, 3);
    int elemento1 = 97;
    int elemento2 = 2;
    int elemento3 = 343;
    int elemento4 = 865;
    int elemento5 = 21;
    int elemento6 = 242;

    hash_insertar(hash, "abc", &elemento1);
    hash_insertar(hash, "sa", &elemento2);
    hash_insertar(hash, "cvfd", &elemento3);
    hash_insertar(hash, "sagfdgfder", &elemento4);
    hash_insertar(hash, "fdsfd", &elemento5);
    hash_insertar(hash, "asaaa", &elemento6);

    pa2m_afirmar((hash_con_cada_clave(hash, recorrer_todo, NULL) == 6), "Iterar sobre un hash con una funcion de recorrer todo devuelve todos los elementos iterados");

    hash_destruir(hash);
}

void dadoUnHashConElementos_recorro5Elementos(){
    hash_t* hash = hash_crear(NULL, 3);
    int elemento1 = 97;
    int elemento2 = 2;
    int elemento3 = 343;
    int elemento4 = 865;
    int elemento5 = 21;
    int elemento6 = 242;

    int contador = 0;

    hash_insertar(hash, "a", &elemento1);
    hash_insertar(hash, "b", &elemento2);
    hash_insertar(hash, "c", &elemento3);
    hash_insertar(hash, "d", &elemento4);
    hash_insertar(hash, "e", &elemento5);
    hash_insertar(hash, "f", &elemento6);

    pa2m_afirmar((hash_con_cada_clave(hash, mayor_a_4, &contador) == 5), "Iterar sobre un hash devuelve que la funcion es invocada 5 veces");

    hash_destruir(hash);
}


int main(){
    pa2m_nuevo_grupo("Pruebas con hash nulo o vacio");
    dadoUnHashNULL_intentoRealizarOperaciones(),

    pa2m_nuevo_grupo("Pruebas de creacion y destruccion de Hash");
    prueboCrearYDestruirUnHash();
    prueboCrearUnHashConCapacidadMayorALaMinima_ySeCreaConLaCapacidadIndicada();
    prueboCrearUnHashConCapacidadMenorALaMinima_ySeCreaConLaCapacidadMinima();

    pa2m_nuevo_grupo("Pruebas de insercion");
    dadoUnHashVacio_puedoInsertarUnElemento();
    dadoUnHashVacio_puedoInsertarUnElementoYLiberarloCorrectamente();
    dadoUnHashVacio_puedoInsertarVariosElementos_yLiberarlosCorrectamente();
    dadoUnHashVacio_puedoInsertarMuchosElementos();
    dadoUnHashConUnElemento_puedoSobreescribirlo();
    dadoUnHashConVariosElemento_puedoSobreescribirAlgunos();

    pa2m_nuevo_grupo("Pruebas de quitado");
    dadoUnHashConUnElemento_puedoQuitarlo_yEsteQuedaVacio();
    dadoUnHashConVariosElementos_puedoQuitarAlgunos_yElEstadoEsCorrecto();

    pa2m_nuevo_grupo("Pruebas de iterador interno");
    dadoUnHashNULL_elIteradorInternoDevuelve0Elementos();
    dadoUnHashVacio_elIteradorInternoDevuelve0Elementos();
    dadoUnHash_elIteradorInternoConFuncionNULLDevuelve0Elementos();
    dadoUnHashConElementos_recorroTodosLosElementos();
    dadoUnHashConElementos_recorro5Elementos();

    return pa2m_mostrar_reporte();
}