/*
* @name: Estructuras para proyecto final de Técnicas y Prácticas de Programación
* @autores:
 * Rafael Hermida
 * Valentina Caicedo
 * Laura Rojas
* @Descripcion:
 *En el software se estan creando varias estructuras en su mayoria estaticas, y una dinamica para la simulando de la logica del videojuego "Pokémon de GameBoy", mediante batallas, pokebolas, posicones, mochila, etc.
*/

/*Importaciones*/
#include <stdlib.h>

/*Declaracion de las estructuras*/
typedef struct datos datos;
typedef struct maleta maleta;
typedef struct capturados capturados;
typedef struct Node Node;
typedef struct Lista Lista;

/*Estructura estática para guardar pokemones*/
struct datos{
	char *nombre;
   char *tipo;
   char *descripcion;
   int vida;
   int vistas;
   int capturado;
};

/*Estructura estática para guarda pokemones al equipo*/
struct Lista{
   int a[6], vida[6], n;
};

/*Estructura dinámica para capturados*/
struct Node{
   int indice;
   int vida;
   Node * next;
};

/* Estructura dinámica para almacenar en numero de posiones y pokebolas*/
struct maleta{
   int pociones;
   int pokebolas;
};

/*Estructura dinámica para capturados*/
struct capturados{
   Node * firstNode;
   int n;
};

/*Función tipo capturados para crear el arreglo de capturados*/
capturados create( ){
   capturados c;
   c.firstNode = NULL;
   c.n = 0;
   return c;
}
