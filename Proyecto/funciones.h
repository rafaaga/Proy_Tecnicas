/*
* @name: Funciones usadas en el proyecto final de Técnicas y Prácticas de Programación
* @autores:
 * Rafael Hermida
 * Valentina Caicedo
 * Laura Rojas
* @Descripcion:
 *Todas las funciones utilizadas en el archivo main
*/

/*importaciones */

#include "estructuras.h"
#include "pokemons.h"

/* @Funcion: menuInicial
 * @Descripcion: Primer menú que se ve cuando no hay partidas guardadas.
 */

void menuInicial(){
   printf( "BIENVENIDO A POKÉMON\n"
           "----------------------\n"
           "1. Juego nuevo\n"
           "0. Salir\n"
           "Digita tu respuesta: ");
	return;
}

/* @Funcion: menuInicial2
 * @Descripcion: Primer menú que se ve cuando hay partidas guardadas.
 */

void menuInicial2(){
	printf(  "BIENVENIDO A POKÉMON\n"
           "----------------------\n"
           "1. Juego nuevo\n"
  			  "2. Continuar Juego\n"
           "0. Salir\n"
           "Digita tu respuesta: ");
	return;
}

/* @Funcion: menuPrincipal
 * @Descripcion: Menú con las opciones que tiene el jugador durante la partida
 */

void menuPrincipal(){
	printf( "1. Caminar\n"
           "2. Pokédex\n"
           "3. Pokémon\n"
           "4. Mochila\n"
           "5. Guardar\n"
           "0. Salir\n"
           "Digita tu respuesta: ");
	return;
}

/* @Funcion: menuCombate
 * @Descripcion: Menú con las opciones que tiene el jugador durante la batalla
 */

void menuCombate(){
    printf("1. Atacar\n"
           "2. Mochila\n"   // Menú de combate
           "3. Huir\n");
    return;
}

/* @Funcion: casosPrincipal
 * @Descripcion: Se enumeran los casos para ser usados en el menú principal y evaluar la condición
 */

enum casosPrincipal{
	salir, //0
   caminar, //1
	pokedex, //2
   pokemonn, //3
   mochilla, //4
   guardar //5
};

/* @Funcion: crearPokemon
 * @Descripcion: Se llena la estructura datos con la información de los 151 pokemones
 */

void crearPokemon(datos * x){
   int i;
   srand(time(NULL));
   for(i = 0; i < 151; i++){
      x[i].nombre = nombres[i];
      x[i].tipo = tipos[i];
      x[i].descripcion = descripcion[i];
      x[i].vida = rand() % 21+70; //Numero aleatorio entre 70 y 90
      x[i].vistas = 0;
      x[i].capturado = 0;
   }
   return;
}

/* @Funcion: primerPokemon
 * @Descripcion: El usuario escoge su pokemon inicial
 */

int primerPokemon(datos *x){
   int opc;
   printf("\n");
   printf("Para empezar tu camino como maestro, elige tu primer pokémon\n");
   printf("1. Bulbasaur\n"
  			 "2. Charmander\n"
          "3. Squirtle\n"
          "Digita tu respuesta: ");
   scanf("%d", &opc);
   while (opc < 1 || opc > 3){
      printf("Selecciona una opción valida: ");
      scanf("%d", &opc);
   }switch (opc){
   case 1:
      x[0].capturado = 1; //Cambia su estado a visto
      x[0].vistas = 1; //Cambia su estado a capturado
      return 0;
   case 2:
      x[3].capturado = 1;
      x[3].vistas = 1;
      return 3;
   case 3:
      x[6].capturado = 1;
      x[6].vistas = 1;
      return 6;
   default:
      break;
   }
}

/* @Funcion: capturar
 * @Descripcion: Se añade un pokémon determinado a la lista de capturados
 */

void capturar( capturados * x, datos * d, int index ){
   int i;
   Node * y = malloc( sizeof( Node ) );
   y->indice = index;
   y->vida = d[index].vida;
   d[index].capturado = 1;
   d[index].vistas = 1;
   y->next = x->firstNode; //Siempre se agrega en la posición 0
   x->firstNode = y;
   x->n++;
   return;
}

/* @Funcion: añadirEquipo
 * @Descripcion: Se añade un pokémon al equipo, si está lleno, se reemplaza por otro
 */

void añadirEquipo(Lista * l, datos *x, capturados *c, int e){
   int i, opc;
   if( l->n < 6){
      l->a[l->n] = e;
      l->vida[l->n] = x[e].vida;
      l->n++;
   }
   else{
      printf("Oh! Al parecer tienes tu equipo lleno, selecciona al pokémon que"
             "deseas reemplazar para añadir a %s\n", x[e].nombre);
      printf("\n");
      for( i=0; i < l->n; i++)
         printf("%d. %s\n", (i+1), x[l->a[i]].nombre);
      printf("Digita tu respuesta: ");
      scanf("%d", &opc); //El usuario escoge el pokémon que desea sustituir
      while (opc < 1 || opc > 6){
         printf("Selecciona una opción valida: ");
         scanf("%d", &opc);
      }
      printf("El cambio de %s por %s fue exitoso, tu pokémon está listo para ser usado!\n",
             x[l->a[opc-1]].nombre, x[l->a[i]].nombre);
      l->a[opc-1] = e;
      l->vida[opc-1] = x[e].vida;
   }
   return;
}

/* @Funcion: mostrarEquipo
 * @Descripcion: Se muestran los pokemones en el equipo
 */

void mostrarEquipo( Lista * l, datos * x){
   int i;
   for( i=0; i < l->n; i++){
      printf("%d. %s\n", (i+1), x[l->a[i]].nombre);
      printf("   Vida: %d/%d\n", l->vida[i], x[l->a[i]].vida);
   }
   return;
}

/* @Funcion: display
 * @Descripcion: Se muestra la pokédex
 */

void display( datos * x, Lista * l, capturados * c){
   int i, opc, opc2, opc3;
   printf("\nHas avistado los siguientes pokemones:\n");
   for( i = 0; i < 151; i++){
      if( x[i].vistas > 0){ //Se muestran los pokémones vistos
         printf("P%d. %s", (i+1), x[i].nombre);
         if( x[i].capturado > 0){
            printf(" (C)\n"); //Si se han capturado se muestra (C) a su lado
         }else printf("\n");
      }
   }
   printf("\n");
   printf("1. Ver pokémon\n");
   printf("0. Salir\n");
   printf("Digita tu respuesta: "); //ver detalles de un pokémon
   scanf("%d", &opc);
   while (opc < 0 || opc > 1){
      printf("Selecciona una opción valida: ");
      scanf("%d", &opc);
   }if(opc == 1){
      printf("Número del pokémon a detallar: ");
      scanf("%d", &opc2);
      while (opc2 < 1 || opc2 > 151){
         printf("Selecciona una opción valida: ");
         scanf("%d", &opc2);
      }
      opc2--;
      if( x[opc2].capturado > 0){ //Si se ha capturado se muestra nombre, tipo, descripción
         printf("Nombre: %s\n", x[opc2].nombre);
         printf("Tipo: %s\n", x[opc2].tipo);
         printf("Descripción: %s\n", x[opc2].descripcion);
         printf("\n");
         printf("1.Añadir al equipo\n"); //Se da la opción de añadir al equipo ese pokémon
         printf("0.Volver\n");
         scanf("%d", &opc3);
         while (opc3 < 0 || opc3 > 151){
            printf("Selecciona una opción valida: ");
            scanf("%d", &opc3);
         }
         if(opc3 == 1){
            añadirEquipo(l, x, c, opc2);
         }
         else display( x, l, c);
      }else if(x[opc2].vistas > 0){
         printf("Nombre: %s\n", x[opc2].nombre);
      }else printf("No hay información de este pokémon\n"); //Si no se ha visto ni capturado
   }
   return;
}

/* @Funcion: batalla
 * @Descripcion: Lógica de batalla
 */

void batalla(Lista * l, datos * x, maleta * m, capturados * c) {
   int option = 0, i = 0, pok = 0, p = 0, opcion = 0, life = 0;
   printf("Se ha seleccionado Pokemon e iniciado una batalla por turnos\n");
   printf("Estos son los Pokemones con los que puedes jugar:\n"); //se muestran los pokémones en el equipo
   mostrarEquipo(l, x);
   printf("Digite el numero del Pokemon con el que desea jugar: ");
   scanf("%d", &pok); //El usuario escoge el pokémon con el que desea combatir
   printf("\n");
   printf("Bienvenido a la batalla %s, tiene %d/%d puntos de vida y su nivel es 7\n", x[l->a[pok-1]].nombre, l->vida[pok-1], x[l->a[pok-1]].vida);
   srand(time(NULL));
   option = rand() % 150; //Se escoge aleatoriamente el rival
   life = x[option].vida;
   printf("Su rival es %s, tiene %d puntos de vida y esta en nivel 7\n", x[option].nombre, x[option].vida);
   x[option].vistas = 1;
   while(i != 3){
      menuCombate();
      printf("Digite la opcion que desee: ");
      scanf("%d", &i);
      switch (i) {
         case 1:
            if(x[option].vida >= 7 && l->vida[pok-1] >= 7){
               x[option].vida -= 7;
               printf("El oponente ha quedado con %d vidas\n", x[option].vida);
               l->vida[pok-1] -= 7;
               printf("Su pokemon ha quedado con %d vidas\n", l->vida[pok-1]);
            }else if(x[option].vida < 7 && l->vida[pok-1] > 7){
               printf("El oponente no tienes suficientes vidas para la batalla\n");
               i = 3;
            }
            else if(x[option].vida > 7 || l->vida[pok-1] < 7){
               printf("Este Pokemon NO tienes suficientes vidas para un batalla\n");
               printf("1. Cambiar de Pokemon\n"
                      "2. Continuar\n");
               printf("Digite la opcion que desee: ");
               scanf("%d", &p);
               switch (p) {
                  case 1:
                     printf("Estos son los Pokemones con los que puedes jugar:\n");
                     mostrarEquipo(l, x);
                     printf("Digite el numero del Pokemon con el que desea jugar en la nueva batalla: ");
                     scanf("%d", &pok);
                     break;
                  case 2:
                     break;
                  default:
                     printf("Ingreso una opcion fuera de rango\n");
                     break;
               }
            }
            break;
         case 2: //Usar la mochila
            printf("Pokebolas: %d\n", m[0].pokebolas);
            printf("Pociones: %d\n", m[0].pociones);
            printf("Desea usar:\n"
                   "1. Pokebola\n"
                   "2. Pocion\n");
            scanf("%d", &opcion);
            switch (opcion) {
               case 1:
                  if(x[option].vida <= life/3 && m[0].pokebolas > 0){
                     capturar(c, x, option);
                     m[0].pokebolas--; //Opción capturar usando la pokébola
                  }
                  else printf("No se pudo capturar\n");
                  break;
               case 2:
                  if(m[0].pociones > 0){
                     l->vida[pok-1] += 50;
                     printf("Su pokemon ha quedado con %d/%d vidas\n", l->vida[pok-1], x[l->a[pok-1]].vida);
                     m[0].pociones--; //Opción de tomar poción
                  }else printf("No tienes pociones suficientes\n");
                  break;
               default:
                  break;
            }
            break;
         case 3:
            printf("Fin de la batalla\n");
            break;
         default:
            printf("Ingreso una opcion fuera de rango\n");
            break;
      }
   }
   x[option].vida = life;
}

/* @Funcion: Save
 * @Descripcion: Se guarda la información
 */

/*
void save(datos * x, maleta * m, Lista * l, capturados * c, char * fn){
   int pc, pk, lon, cn, a[6], vidaa[6], cap[c->n], vc[c->n], i;
   pc = m[0].pociones;
   pk = m[0].pokebolas;
   lon = l->n;
   cn = c->n;
   for( i = 0; i <l->n; i++)
      a[i] = l->a[i];
   for( i = 0; i <l->n; i++)
      vidaa[i] = l->vida[i];
   Node * p = c->firstNode;
   for( i = 0; i <c->n; i++){
      cap[i] = p->indice;
      p = p->next;
   }
   Node * q = c->firstNode;
   for( i = 0; i <c->n; i++){
      vc[i] = q->vida;
      q = q->next;
   }
   FILE * f;
   f = fopen(fn, "wb");
      fwrite(&lon, sizeof(int), 1, f);
      fwrite(a, sizeof(a), 1, f);
      fwrite(vidaa, sizeof(vidaa), 1, f);
      fwrite(&pc, sizeof(int), 1, f);
      fwrite(&pk, sizeof(int), 1, f);
      fwrite(&cn, sizeof(int), 1, f);
      fwrite(x, sizeof(x), 1, f);
      fwrite(cap, sizeof(cap), 1, f);
      fwrite(vc, sizeof(vc), 1, f);
   fclose(f);
   return;
}
*/

/* @Funcion: Cargar
 * @Descripcion: Se carga la información guardada en una partida
 */

/*
void cargar(datos * x, maleta * m, capturados * c, Lista * l, char * fn){
   int pc, pk, lon, cn, a[6], vidaa[6], cap[150], vc[150], i;
   FILE * f;
   f = fopen(fn, "rb");
      fread(&lon, sizeof(int), 1, f);
      fread(a, sizeof(a), 1, f);
      fread(vidaa, sizeof(vidaa), 1, f);
      fread(&pc, sizeof(int), 1, f);
      fread(&pk, sizeof(int), 1, f);
      fread(&cn, sizeof(int), 1, f);
      fread(x, sizeof(x), 1, f);
      fread(cap, sizeof(cap), 1, f);
      fread(vc, sizeof(vc), 1, f);
   fclose(f);
   pc = m[0].pociones;
   pk = m[0].pokebolas;
   l->n = lon;
   c->n = cn;
   for( i = 0; i <lon; i++)
      l->a[i] = a[i];
   for( i = 0; i <lon; i++)
      l->vida[i] = vidaa[i];
   Node * p = c->firstNode;
   for( i = 0; i <cn-1; i++){
      p->indice = cap[i];
      p = p->next;
   }
   Node * q = c->firstNode;
   for( i = 0; i <cn-1; i++){
      q->vida = vc[i];
      q = q->next;
   }
   return;
}
*/