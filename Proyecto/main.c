/*
 * @name:
 * Proyecto final de Técnicas y Prácticas de Programación
 * @autor:
 * Rafael Hermida
 * Valentina Caicedo
 * Laura Rojas
 * @Descripcion:
 * En el software se esta simulando la logica del videojuego "Pokémon de GameBoy", mediante batallas, pokebolas, posicones, mochila, etc.
 */

/*Importaciones*/
#include "funciones.h"

/* @Funcion: Main
 * @Descripcion: Funcion principal del programa en C.
 */

int main(){
   srand(time(NULL));
   int i, opc, opc2, opc3, elec, primer,
   p = 0;
   FILE *partidas;
   char usuarios[10][20] = {};  //Arreglo donde se guardaran los nombres de los jugadores de cada partida
   char nombre[20];  //Varible tipo char donde se almacenara el nombre del jugador en la partida
   partidas = fopen( "partidas.dat", "rb" );
   fread( &p, sizeof( int ), 1, partidas );
   fread( usuarios, sizeof( usuarios ), 1, partidas );
   fclose(partidas);
   datos pokemon[151];  //Se crea una estructura estatica tipo datos, donde se guardaran los 151 pokemones
   maleta mochila[1];  //Se crea una estructura estatica tipo mochila en el cual se almacena la cantidad de pokebolas y pociones
   Lista equipo; //Estrutura estatica donde se guardaran los pokemons vistos y capturados
   equipo.n = 0;
   capturados cap = create(); //Estructura dinamica en la cual se almacenara los pokemones capturados y el numero de vidas que tienen
   mochila[0].pociones = 0, mochila[0].pociones = 0;
   crearPokemon( pokemon );  //Se guardan todos los pokemones en el arreglo pokemon
   if( p == 0){  //En caso de no tener partidas guardadas
      menuInicial();
      scanf("%d", &opc);
      if(opc == 1){
         printf("\n");
         printf("Tu nombre, jugador: ");
         scanf("%s", nombre);
         strcpy(usuarios[p], nombre);
         p++;
         primer = primerPokemon(&pokemon);
         capturar(&cap, &pokemon, primer);
         añadirEquipo(&equipo, &pokemon, &cap, primer);
         //save(&pokemon, &mochila, &equipo, &cap, nombre);
      }
   }
   else{  //En caso de tener partidas guardadas
      menuInicial2();
      scanf("%d", &opc);
      if (opc==1){
         printf("\nTu nombre, jugador: ");
         scanf("%s", nombre);
         strcpy(usuarios[p], nombre);
         p++;
         primer = primerPokemon(&pokemon);
         capturar(&cap, &pokemon, primer);
         añadirEquipo(&equipo, &pokemon, &cap, primer);
         //save(&pokemon, &mochila, &equipo, &cap, nombre);
         printf("Se ha añadido a %s a tu equipo!\n", pokemon[primer].nombre);
      }
      if(opc == 2){
         printf("\n");
         printf("Selecciona la partida:\n");
         for(i=0; i<p; i++)
            printf("%d. %s\n", (i+1), usuarios[i]);
         printf("Selección: ");
         scanf("%d", &opc2);
         while (opc2 < 1 || opc2 > (p)){
         printf("Selecciona una opción valida: ");
         scanf("%d", &opc2);
         }
         //cargar(&pokemon, &mochila, &cap, &equipo, usuarios[(opc2-1)]);
         printf("PROGRESO CARGADO CON ÉXITO...");
         printf("SE CARGÓ EL PROGRESO DE %s", usuarios[(opc2-1)]);
      }
   }
   printf("\n");
   menuPrincipal();  //Se imprime el menu principal del juego
   scanf("%d", &opc3);
   srand(time(NULL));
   while (opc3 < 0 || opc3 > 5){
      printf("Selecciona una opción valida: ");
      scanf("%d", &opc3);
   }while (opc3 != 0){
      switch (opc3){
      case caminar:
      printf("\n");
         elec = rand() % 4;  //Se selecciona un numero rand entre 0 a 3
         if(elec == 0)
            batalla(&equipo, &pokemon, &mochila, &cap);  //Se inicia una batalla
         else if(elec == 1){
            mochila[0].pociones++;
            printf("Se ha añadido 1 poción...\n"); //Se agrega una pocion
         }
         else if(elec == 2){
            mochila[0].pokebolas++;
            printf("Se ha añadido 1 pokebola...\n"); //Se agrega una pokebola
         }
         else if(elec == 3)
            printf("Nada ha ocurrido...\n");
         printf("\n");
         break;
      case pokedex:
         display(&pokemon, &equipo, &cap);
         break;
      case pokemonn:
         mostrarEquipo( &equipo, &pokemon);
         break;
      case mochilla:
         printf("Pokebolas: %d\n", mochila[0].pokebolas);
         printf("Pociones: %d\n", mochila[0].pociones);
         break;
      case guardar:
         //save(&pokemon, &mochila, &equipo, &cap,  nombre);
         break;
      default:
         printf("Ingreso una opcion fuera de rango\n");
         break;
      }
      menuPrincipal();
      scanf("%d", &opc3);
      while (opc3 < 0 || opc3 > 5){
         printf("Selecciona una opción valida: ");
         scanf("%d", &opc3);
      }
   }
//-------------GUARDADO DE PARTIDAS--------------------
   /*partidas = fopen( "partidas.dat", "wb" );
   fwrite( &p, sizeof( int ), 1, partidas );
   fwrite( usuarios, sizeof( usuarios ), 1, partidas );
   fclose(partidas);
   return 0;*/
}