![](https://i.imgur.com/P0aqOMI.jpg)
​
# **TDA - HASH** 
## [7541/9515] Algoritmos y Programación II

​
### Segundo cuatrimestre de 2021
​
|  Alumno: | SANCHEZ FERNANDEZ DE LA VEGA, Manuel |
| ----------- | ----------- |
| Número de padrón: | 107951 |
| Email: | msanchezf@fi.uba.ar |
​
​
#### 1. Introducción

El TDA Hash consiste principalmente de una tabla. Esta contiene pares de clave y valor. El valor es el elemento que deseamos guardar, y la clave es una cadena de caracteres que se traduce a una posicion en la tabla mediante la funcion de hash. Hay practicamente infinitas funciones de hash, algunas mas efectivas que otras (tienen una mayor dispersion en la tabla). 
Una de las ventajas del hash es que permite obtener elementos del mismo a con un orden de complejidad de O(1), al menos si esta implementado correctamente (mas detalle en la seccion de teoria).
Hay diversas formas de implementar un hash, en las secciones posteriores explicare mi implementacion y las decisiones detras de la misma.
​
#### 2. Teoría

Como ya lo mencione previamente, una tabla de hash es, esencialmente, una tabla de datos que consisten de pares clave y valor. Estas claves se traducen en posiciones en la tabla hash. 
Por ejemplo, yo puedo guardar un elemento con la clave `"abc"`, la cual mediante la funcion hash, es traducida a un numero que representa la posicion en esta tabla. La ventaja de esto es que si yo quiero recuperar el elemento que guarde con la clave `"abc"`, es tan simple como volver a traducir la clave, y acceder a esa posicion de la tabla. Como no es necesario iterar sobre toda la tabla, lo podemos considerar como `O(1)`.
Una consecuencia de el uso de estos pares clave y valor es que no pueden existir 2 valores con la misma clave, ya que las claves deben ser unicas. De otro modo, no habria forma de diferenciar cual estamos buscando.

A la hora de insertar elementos, puede suceder que 2 claves distintas se traduzcan en la misma posicion en la tabla. A esto se lo conoce como colision. Este problema es lo que genera una distincion entre los tipos de hash. Como consecuencia del mismo, existen 2 tipos:
+ Hash abierto - direccionamiento cerrado
+ Hash cerrado - direccionamiento abierto


##### Hash Abierto - direccionamiento cerrado
Los hash abiertos consisten en que los elementos no son insertados en la tabla de hash directamente, por eso se los llama abiertos. Tecnicamente, los elementos estan fuera de la tabla de hash. Por el otro lado, se lo conoce como direccionamiento cerrado ya que los elementos son insertados en la posicion que devuelve la clave hasheada.
Los hash abiertos consisten en implementar algun otro TDA en la tabla de hash, como puede ser una lista o un arbol binario. Es decir, la tabla de hash consiste de un vector que en cada posicion contiene algun TDA. Lo que nos permite hacer esto es que, si tenemos una colision, los elementos pueden compartir esa posicion de la tabla ya que se pueden insertar en el TDA.
Consecuentemente, para acceder a un elemento en un hash abierto, hay que acceder a la posicion de la clave hasheada, y luego iterar en el TDA hasta encontrar el elemento con la clave buscada.
No obstante, esto puede traer problemas ya que si se insertan demasiados elementos en una sola posicion de la tabla, el orden de complejidad de esta iteracion puede dejar de ser considerado como insignificante por lo que perdemos eficiencia. Como solucion, se suele rehashear. Es decir, agrandar el hash e insertar todos los elementos nuevamente (los cuales puede que caigan en posiciones distintas a las que estaban previamente). Sin embargo, se evita hacer esta operacion seguido ya que es muy costosa.
Esta es la implementacion que yo utilice y voy a detallar en la seccion de mas abajo.

##### Hash Cerrado - direccionamiento cerrado
Por el otro lado, los hash cerrados se destacan por el hecho de que los elementos siempre son insertados en la tabla de hash, sin hacer uso de otro TDA de por medio. Los pares clave y valor siempre son insertados en la tabla, y si en algun momento ocurre una colision, hay diversas formas de tratarla como:
+ Probing lineal
+ Probing cuadratico
+ Hash doble

El probing lineal, por ejemplo, consiste en avanzar una posicion en la tabla e intentar insertarlo ahi. Este proceso se repite hasta que se encuentra una posicion libre. De ahi viene el nombre de direccionamiento abierto, ya que la posicion del elemento no es siempre la que devuelve la funcion de hash.
Si se intenta acceder a un elemento que no esta en su posicion correspondiente, lo que se hace es avanzar de posicion y comparar la clave. Este proceso se repite hasta que no haya mas claves por comparar, o hasta encontrarse con un espacio en blanco. Esto trae como consecuencia que, a la hora de eliminar un elemento, no es tan sencillo como quitarlo de la tabla ya que afectaria otras busquedas. Para solucionar esto, se pueden tomar enfoques distintos, pero uno de los mas simples es marcar al casillero con un flag que indique que tuvo en elemento eliminado. De esta forma, se evita afectar futuras busquedas.
Nuevamente, en esta implementacion es necesario rehashear para evitar quedarse sin espacio para nuevos elementos.

Otra implementacion posible es usar una zona de desbordes, la cual es una parte de la tabla de hash reservada para elementos colisionados. Si llegara a ocurrir una colision, el elemento se agrega en la zona de desbordes en vez de realizar probing lineal. Esto produce que, a la hora de buscar un elemento, tambien debo buscar sobre la zona de desbordes.

​
#### 3. Detalles de implementación

​
En mi implementacion, desarrolle un hash abierto. Es decir, mi tabla de hash consiste de un vector dinamico de listas simplemente enlazadas. En estas listas es donde se almacenan los pares clave y valor del hash.
![Estructura de hash](https://imgur.com/lBzhhhJ.png)

Decidi almacenar la cantidad actual de casilleros para saber cuantos elementos tiene el hash en todo momento. Por el otro lado, tambien guarde la cantidad maxima de listas. Estos parametros son los que voy a usar para decidir cuando rehashear.

Yo decidi agrupar estos pares en una estructura que llame casillero. En otras palabras, lo que realmente contienen las listas son casilleros donde se almacenan los pares clave y valor.
![Listas y casilleros](https://imgur.com/hENoFFx.png)
En los casilleros, las claves son strings, es decir `char*`, mientras que los valores son punteros genericos.
De esta forma, las colisiones no son un problema ya que si 2 claves pertenencen a la misma posicion en la tabla, simplemente las inserto en la lista de esa posicion sin tener problema alguno.

Al estar trabajando con listas, puedo hacer uso de sus primitivas por ejemplo a la hora de insertar, quitar elementos, iterar sobre el hash, etc.

​Voy a detallar el funcionamiento y decisiones implementacion para algunas funciones que considero importantes:

1. `funcion_hash()`
    Hay infinidades de funciones de hash, algunas de ellas muy complejas pero eficientes. Sin embargo, para mi implementacion opte por realizar una funcion muy sencilla que simplemente suma el valor de la tabla ASCII de cada caracter en la clave, y lo devuelve. Aunque sea cierto que no es la funcion mas efectiva de todas, cumple su rol y si en algun momento decido cambiarla, es tan simple como modificar la `funcion_hash()` y listo. En otras palabras, el resto del codigo no se ve afectado.
​
2. `hash_insertar()`
    La parte que me gustaria destacar de esta funcion es el rehasheo. Si se intenta insertar un elemento y la cantidad de elementos del hash supera la cantidad de listas del hash multiplicado por una constante (MULTIPLICADOR_LIMITE_REHASHEO), entonces se realiza un rehash. Decidi definir a esta constante que multiplica la cantidad de listas como 5. Esto se debe a que si no pusiera un limite para el rehasheo, entonces las operaciones de busqueda en el hash dejarian de ser O(1). Entonces, decidi que el hash puede almacenar, como maximo antes de rehashear, 5 veces la cantidad de listas que el mismo tiene.

3. `rehashear()`
   Esta funcion se resume en crear un hash nuevo con una cantidad de listas `multiplicador_tamanio` veces mas que el anterior hash. Luego copia todos los elementos del viejo hash al nuevo. Esta cantidad de veces mayor esta definida en una constante llamado MULTIPLICADOR_NUEVO_TAMANIO que defini en 10. Es decir, cada vez que rehasheo, el hash se hace 10 veces mas grande. Esto es asi ya que, al ser una operacion muy costosa, prefiero utilizar mas memoria a cambio de tener que hacer esta operacion repetidas veces.

   Para desarrollar esta funcion, use el iterador interno del hash, pasandole como parametro una funcion que copie los casilleros de uno a otro. Esta funcion se llama `copiar_casillero()` y devuelve false si lo pudo copiar y true si no pudo. Esto se debe a que el iterador interno continua iterando mientras que la funcion devuelva false. Asimismo, esta funcion es necesaria ya que no puedo usar directamente `hash_insertar()` ya que no es el mismo tipo de funcion que la que se le pasa por parametro a `hash_con_cada_clave()` 

   Si pudo copiar todas las claves con exito, entonces libera las claves, casilleros y listas del hash viejo. Hay que prestar mucha atencion ya que no se tienen que liberar los valores que inserto el usuario. Para evitar esto, cambio el destructor del hash a NULL y luego llamo a la funcion de `liberar_tabla_hash()`. Luego, asigno el hash nuevo al hash viejo.

   Si no se pudieron copiar las claves, libero el hash nuevo pero nuevamente teniendo el cuidado de no liberar los elementos.

4. `hash_con_cada_clave()`
   A la hora de implementar esta funcion, use el iterador interno de lista. Sin embargo, el iterador de hash recibe un `bool (*funcion)(hash_t*, const char*, void*)` mientras que el de lista recibe un `bool (*funcion)(void*, void*)`. Por esta misma razon, tuve que hacer un wrapper llamado `hash_con_cada_clave_aux()`, al cual le paso una estructura `datos_funcion_t` que contiene todos los datos necesarios para aplicar la funcion que recibe `hash_con_cada_clave`.

   Como el iterador de lista itera mientras la funcion devuelva `true`, y el iterador de hash itera mientras la funcion devuelva `false`, el wrapper almacena el retorno de la funcion pasada por parametro en `datos_funcion->retorno`. Este es el valor que define si se continua iterando en el iterador de hash. Luego, el wrapper devuelve `!(datos_funcion->retorno)` ya que es el valor utilizado para seguir iterando por la lista.

5. `obtener_posicion_casillero()`
   Esta es una funcion esencial para el TDA. A pesar de no ser una primitiva, es una funcion que me permite simplificar el codigo ya que la reuso en:
   + `hash_insertar()`
   + `hash_quitar()`
   + `hash_obtener()`
   + `hash_contiene()`
    Funciona usando el iterador externo de lista (para variar un poco y no tener que definir otra funcion auxiliar :D ).

    ![obtener_posicion_casillero_1](https://i.imgur.com/mi1tWEA.png)
    ![obtener_posicion_casillero_2](https://i.imgur.com/YzrDySl.png)
    ![obtener_posicion_casillero_3](https://i.imgur.com/ok28kpN.png)