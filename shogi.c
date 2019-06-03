#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
** FUNCIONES
**/
int verifica_fin(char ); //done
int inteligenciaPC(char juega);//done
int jaque_mate(char ); //done
int mueve_negro(char juega); //done
int mueve_blanco (char juega);//done
int come_reemplaza(char ficha,char filaActual,int columnaActual, char filaDestino, int columnaDestino); //done
void imprime(); //done
void carga_tablero(); //done
void inicia();  //done
void randoms(); //done
void juega_negro_human(); //done
void juega_blanco_human(); //done
void juega_negro_PC(); //done
void juega_blanco_PC(); //done
/**
** TIPO DE DATO
**/
typedef struct tablero{
  char ficha; //ficha peon rey lo que fuese
  char color; //color 'n'(negro) y 'b'(blanco)
}tablero;

/**
* VARIABLES GLOBALES
**/
tablero table[9][9];
int jugadasMaximas;
int turnosRealizados;
char jugadorHuman;
int jugadorHumanTurno;
char jugadorPC;
int jugadorPcTurno;

int main(){

  srand(time(NULL)); //semilla de random
  inicia();
  carga_tablero();
  printf("           (0 0)           \n");
  printf("   ---oOO-- (_) ----oOO---\n");
  printf("╔═════════════════════════╗\n");
  printf("║ Bienvenido a Shogi !..♣ ║\n");
  printf("╚═════════════════════════╝\n");
  printf("    ------------------     \n");
  printf("          |__|__|          \n");
  printf("           || ||           \n");
  printf("          ooO Ooo\n");
  printf(".::Bienvenido al juego de Shogi 将棋::.\n Seleccione la cantidad de jugadas máximas que tendrá esta partida: ");
  scanf("%d", &jugadasMaximas);
  imprime();
  printf("\n");
  printf("\nAhora se procedera a realizar un sorteo de que fichas usara cada jugador (color)\n");
  randoms();
  if(jugadorHumanTurno==0){
    if(jugadorHuman=='n'){
      juega_negro_human();
    }
    else{
      juega_blanco_human();
    }
  }
  else{
    if(jugadorPC=='n'){
      juega_negro_PC();
    }
    else{
      juega_blanco_PC();
    }
  }

  return 0;
}

//Funcion donde se realizan todas las cosas con randoms
void randoms(){
  int random;
  random= rand()%2; //random de 0 o 1
  if(random){
    jugadorHuman= 'n';
    jugadorPC= 'b';
  }
  else{
    jugadorHuman= 'b';
    jugadorPC= 'n';
  }
  if (jugadorHuman=='n') {
    printf("El jugador humano jugara con las fichas negras y la PC con las blancas\n");
  }
  else {
    printf("El jugador humano jugara con las fichas blancas y la PC con las negras\n");
  }

  random=rand()%2;
  //Si sale 1 empieza el humano y si sale 0 empieza la CPU
  if(random){
    jugadorHumanTurno=0;
    jugadorPcTurno=1;
  }
  else{
    jugadorHumanTurno=1;
    jugadorPcTurno=0;
  }
  printf("\nAhora se procedera a realizar un sorteo de que jugador empieza\n");
  if (jugadorHumanTurno == 0) {
    printf("El jugador humano empieza\n");
  }
  else {
    printf("La PC empieza\n");
  }
}

//Funcion que incializa tablero
void inicia(){
  int i,j;
  turnosRealizados=0;
  for( i=0; i<9 ; i++ ){
    for( j=0; j<9 ; j++ ){
      table[i][j].ficha= '-';
      table[i][j].color= 'x';
    }
  }
}

//Funcion que imprime el tablero
void imprime(){
  int i,j,columnas;
  columnas=9;
  for(i=0;i<9;i++)
    printf("%i  \t", columnas-i);
  printf("\n");
  for(i=0;i<9;i++)
    printf("_______\t");
  printf("\n\n");
  for( i=0; i<9 ; i++ ){
    for( j=0; j<9 ; j++ ){
      if(table[i][j].color == 'b'){
        if(table[i][j].ficha == 'P')
          printf("%c%c%c\t", table[i][j].ficha, 'l','b');
        else if(table[i][j].ficha == 'p')
          printf("%c%c \t", 'P','b');
        else
          printf("%c%c \t", table[i][j].ficha, 'b');
      }
      else{
        if(table[i][j].ficha == 'P')
          printf("%c%c \t", table[i][j].ficha,'l');
        else if(table[i][j].ficha == 'p')
          printf("%c \t", 'P');
        else
          printf("%c  \t", table[i][j].ficha);
      }
      if(j == 8)
        printf("  | %c", 'a'+i);
    }
    printf("\n");
  }


}

//Funcion que carga tablero predeterminado
//Rey (R), General Oro (O), General Plata (P), Caballos (C), Lanceros (L), Alfil (A), Torre(T), Peones (p)
void carga_tablero(){
  int i, j;
  //Peones
  for( i=0; i<9 ; i++ ){
    table[2][i].ficha= 'p';
    table[2][i].color= 'b';
    table[6][i].ficha= 'p';
    table[6][i].color= 'n';
  }
  //Lancero
  table[0][8].ficha= 'L';
  table[0][8].color= 'b';
  table[0][0].ficha= 'L';
  table[0][0].color= 'b';

  table[8][8].ficha= 'L';
  table[8][8].color= 'n';
  table[8][0].ficha= 'L';
  table[8][0].color= 'n';

  //Caballos
  table[0][7].ficha= 'C';
  table[0][7].color= 'b';
  table[0][1].ficha= 'C';
  table[0][1].color= 'b';

  table[8][7].ficha= 'C';
  table[8][7].color= 'n';
  table[8][1].ficha= 'C';
  table[8][1].color= 'n';

  //Plata
  table[0][6].ficha= 'P';
  table[0][6].color= 'b';
  table[0][2].ficha= 'P';
  table[0][2].color= 'b';

  table[8][6].ficha= 'P';
  table[8][6].color= 'n';
  table[8][2].ficha= 'P';
  table[8][2].color= 'n';

  //Oro
  table[0][5].ficha= 'O';
  table[0][5].color= 'b';
  table[0][3].ficha= 'O';
  table[0][3].color= 'b';

  table[8][5].ficha= 'O';
  table[8][5].color= 'n';
  table[8][3].ficha= 'O';
  table[8][3].color= 'n';

  //Alfiles
  table[1][1].ficha= 'A';
  table[1][1].color= 'b';
  table[7][1].ficha= 'A';
  table[7][1].color= 'n';

  //Torres
  table[1][7].ficha= 'T';
  table[1][7].color= 'b';
  table[7][7].ficha= 'T';
  table[7][7].color= 'n';

  //Reyes
  table[0][4].ficha= 'R';
  table[0][4].color= 'b';
  table[8][4].ficha= 'R';
  table[8][4].color= 'n';

  /**PRUEBA DE JAQUE MATE
  //cambiar
  table[0][5].ficha='P';
  table[0][5].color='n';
  table[2][5].ficha='R';
  table[2][5].color='b';
  table[4][5].ficha='p';
  table[4][5].color='n';
  table[4][6].ficha='p';
  table[4][6].color='n';
  table[4][4].ficha='p';
  table[4][4].color='n';
  table[1][7].ficha='T';
  table[1][7].color='n';
  table[3][7].ficha='A';
  table[3][7].color='n';
  table[6][0].ficha='p';
  table[6][0].color='b';**/
}

//En esta funcion se verificara si el juego llega a su fin
//Si retorna 1 se sigue jugando, si retorna 0 es empate, si retorna -1 perdio negro, si retorna 2 gano negro
int verifica_fin(char jaque){
  int retorno=1;
  int i,j;
  int reyes=0;
  int reyNegro=0;
  int reyBlanco=0;

  for(i=0; i<9 ; i++){
    for(j=0; j<9 ; j++){
      if(table[i][j].ficha == 'R'){
        reyes=reyes+1;
        if(table[i][j].color=='n'){
          reyNegro=1;
        }
        else{
          reyBlanco=1;
        }
      }
    }
  }

  //Si alguien comio al rey
  if(reyes<2){
    if(reyNegro == 1){
      printf("Gana el jugador de la ficha negra!\n");
      retorno=2;
      return retorno; //gana negro
    }
    else if( reyBlanco == 1){
      printf("Gana el jugador de la ficha blanca!\n");
      retorno=-1;
      return retorno; //gana blanco
    }
    else{
      printf("Empate!\n");
      retorno=0;
      return retorno;
    }
  }

  //puts("\nLlega hasta antes de entrar a jaque mate\n"); //cambiar
  //Si es jaque mate
  if(jaque_mate(jaque)){
    retorno=0;
  }

  //Si se realizaron todas las jugadas
  if(turnosRealizados == jugadasMaximas){
    printf("\nSe han realizado el maximo de jugadas termino en empate\n");
    retorno=0;
  }
  return retorno;
}

//Esta funcion retorna 1 si es jaque mate y 0 si no
int jaque_mate(char jaque){
  int retorno=0;
  int i,j;
  int filaActual,columnaActual;
  int contadorJaque[9]={0,0,0,0,0,0,0,0,0}; //si en los 9 lugares hay uno o mas jaques pierde
  int checks=0;
  //printf("entro a jaque mate");
  //se encuentra al rey
  for(i=0; i<9 ;i++){
    for(j=0; j<9; j++){
      if(table[i][j].ficha=='R' && table[i][j].color == jaque){
        filaActual=i;
        columnaActual=j;
      }
    }
  }
  //si el rey se mueve abajo controlar si alguna de las otras 8 fichas puede comerlo
  if(filaActual+1 >= 0 && filaActual+1<9 && table[filaActual+1][columnaActual].color!=jaque){
    for(i=0; i<8; i++){
      if(i==0){
        //controla que un peon pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+2][columnaActual].ficha=='p' && table[filaActual+2][columnaActual].color=='n'){
            //hay un peon que puede comerte
            contadorJaque[0]++;
            break;
          }
        }
        else{ //si es rey negro
          //ningun peon blanco puede comerle
        }
      }
      if(i==1 && contadorJaque[0]==0){
        //controla que un alfil pueda comerlo en esa posicion
        for(j=1; j+(filaActual+1)<9 && columnaActual+j<9 ;j++){
          if(table[filaActual+1+j][columnaActual+j].ficha=='A' && table[filaActual+1+j][columnaActual+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[0]++;
            break;
          }
          else if(table[filaActual+1+j][columnaActual+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(filaActual+1)<9 && columnaActual-j>=0 ;j++){
          if(table[filaActual+1-j][columnaActual-j].ficha=='A' && table[filaActual+1-j][columnaActual-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[0]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual+1)-j>=0 && columnaActual-j>=0 ;j++){
          if(table[filaActual+1-j][columnaActual-j].ficha=='A' && table[filaActual+1-j][columnaActual-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[0]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual+1)-j>=0 && columnaActual+j<9 ;j++){
          if(table[filaActual+1-j][columnaActual+j].ficha=='A' && table[filaActual+1-j][columnaActual+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[0]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==2 && contadorJaque[0]==0){
        //controla que un torre pueda comerlo en esa posicion
        for(j=1; j+(filaActual+1)<9;j++){
          if(table[filaActual+1+j][columnaActual].ficha=='T' && table[filaActual+1+j][columnaActual].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[0]++;
            break;
          }
          else if(table[filaActual+1+j][columnaActual].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual+1)-j >= 0 ;j++){
          if(table[filaActual+1-j][columnaActual].ficha=='T' && table[filaActual+1-j][columnaActual].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[0]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(columnaActual) < 9 ;j++){
          if(table[filaActual+1][columnaActual+j].ficha=='T' && table[filaActual+1][columnaActual+j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[0]++;
            break;
          }
          else if(table[filaActual+1][columnaActual+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (columnaActual-j)>=0 && j;j++){
          if(table[filaActual+1][columnaActual-j].ficha=='T' && table[filaActual+1][columnaActual-j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[0]++;
            break;
          }
          else if(table[filaActual+1][columnaActual-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==3 && contadorJaque[0]==0){
        //controla que un lancero pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          for(j=1; filaActual+1+j <9 ; j++){
            if(table[filaActual+1+j][columnaActual].ficha=='L' && table[filaActual+1+j][columnaActual].color=='n'){
              //hay un lancero que puede comerte
              contadorJaque[0]++;
              break;
            }
            else if(table[filaActual+1+j][columnaActual].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
        else{ //si es rey negro
          for(j=1; filaActual+1-j >=0 ; j++){
            if(table[filaActual+1-j][columnaActual].ficha=='L' && table[filaActual+1-j][columnaActual].color =='b'){
              //hay un lancero que puede comerte
              contadorJaque[0]++;
              break;
            }
            else if(table[filaActual+1-j][columnaActual].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
      }
      if(i==4 && contadorJaque[0]==0){
      //controla que un plata pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+2][columnaActual].ficha == 'P' && table[filaActual+2][columnaActual].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[0]++;
            break;
          }
          if(table[filaActual+2][columnaActual-1].ficha == 'P' && table[filaActual+2][columnaActual-1].color =='n'){
            //hay un plata que puede comerte
            contadorJaque[0]++;
            break;
          }
          if(table[filaActual+2][columnaActual+1].ficha == 'P' && table[filaActual+2][columnaActual+1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[0]++;
            break;
          }
        }
        else{ //si es rey negro
          if(table[filaActual+2][columnaActual-1].ficha == 'P' && table[filaActual+2][columnaActual-1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[0]++;
            break;
          }
          if(table[filaActual+2][columnaActual+1].ficha == 'P'&& table[filaActual+2][columnaActual+1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[0]++;
            break;
          }
        }
      }
      if(i==5 && contadorJaque[0]==0){
      //controla que un oro pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+2][columnaActual].ficha == 'O' && table[filaActual+2][columnaActual].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[0]++;
            break;
          }
          if(table[filaActual+2][columnaActual-1].ficha == 'O' && table[filaActual+2][columnaActual-1].color =='n'){
            //hay un oro que puede comerte
            contadorJaque[0]++;
            break;
          }
          if(table[filaActual+2][columnaActual+1].ficha == 'O' && table[filaActual+2][columnaActual+1].color == 'n'){
            //hay un Oro que puede comerte
            contadorJaque[0]++;
            break;
          }
        }
        else{ //si es rey negro
          if(table[filaActual+2][columnaActual].ficha == 'O' && table[filaActual+2][columnaActual].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[0]++;
            break;
          }
        }
      }
      if(i==6 && contadorJaque[0]==0){
      //controla que un caballo pueda comerlo
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+1+2][columnaActual+1].ficha=='C' && table[filaActual+1+2][columnaActual+1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[0]++;
            break;
          }
          if(table[filaActual+1+2][columnaActual-1].ficha=='C' && table[filaActual+1+2][columnaActual-1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[0]++;
            break;
          }

        }
        else{
          //Caballo negro
          if(table[filaActual+1-2][columnaActual+1].ficha=='C' && table[filaActual+1-2][columnaActual+1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[0]++;
            break;
          }
          if(table[filaActual+1-2][columnaActual-1].ficha=='C' && table[filaActual+1-2][columnaActual-1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[0]++;
            break;
          }
        }
      }
      if(i==7 && contadorJaque[0]==0){
      //controla que un rey pueda comerlo
        if(table[filaActual+2][columnaActual].ficha == 'R' && table[filaActual+2][columnaActual].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[0]++;
          break;
        }
        if(table[filaActual+2][columnaActual-1].ficha == 'R' && table[filaActual+2][columnaActual-1].color !=jaque){
          //hay un rey que puede comerte
          contadorJaque[0]++;
          break;
        }
        if(table[filaActual+2][columnaActual+1].ficha == 'R' && table[filaActual+2][columnaActual+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[0]++;
          break;
        }
      }
    }
  }
  //el rey se mueve arriba
  if(filaActual-1 >= 0 && filaActual-1<9 && table[filaActual-1][columnaActual].color!=jaque){
    for(i=0; i<8; i++){
      if(i==0 && contadorJaque[1]==0){
        //controla que un peon pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          //ningun peon negro puede comerle
        }
        else{ //si es rey negro
          if(table[filaActual-2][columnaActual].ficha=='p'&& table[filaActual-2][columnaActual].color=='b'){
            //hay un peon que puede comerte
            contadorJaque[1]++;
            break;
          }
        }
      }
      if(i==1 && contadorJaque[1]==0){
        //controla que un alfil pueda comerlo en esa posicion
        for(j=2; j+(filaActual-1)<9 && j+columnaActual<9 ;j++){
          if(table[filaActual-1+j][columnaActual+j].ficha=='A' && table[filaActual-1+j][columnaActual+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[1]++;
            break;
          }
          else if(table[filaActual-1+j][columnaActual+j].ficha!= 'x'){
            //hay algo en el medio
            printf("\nhay algo entre la posicion y el alfil\n"); //cambiar
            break;
          }
        }
        for(j=1; j+(filaActual-1)<9 && columnaActual-j>=0 ;j++){
          if(table[filaActual-1+j][columnaActual-j].ficha=='A' && table[filaActual-1+j][columnaActual-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[1]++;
            break;
          }
          else if(table[filaActual-1+j][columnaActual-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual-1)-j>=0 && j+columnaActual<9 ;j++){
          if(table[filaActual-1-j][columnaActual+j].ficha=='A' && table[filaActual-1-j][columnaActual+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[1]++;
            break;
          }
          else if(table[filaActual-1-j][columnaActual+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual-1)-j>=0 && columnaActual-j>=0 ;j++){
          if(table[filaActual-1-j][columnaActual-j].ficha=='A' && table[filaActual-1-j][columnaActual-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[1]++;
            break;
          }
          else if(table[filaActual-1-j][columnaActual-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==2 && contadorJaque[1]==0){
        //controla que un torre pueda comerlo en esa posicion
        for(j=1; j+(filaActual-1)<9;j++){
          if(table[filaActual-1+j][columnaActual].ficha=='T' && table[filaActual-1+j][columnaActual].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[1]++;
            break;
          }
          else if(table[filaActual-1+j][columnaActual].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual-1)-j >= 0 ;j++){
          if(table[filaActual-1-j][columnaActual].ficha=='T' && table[filaActual-1-j][columnaActual].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[1]++;
            break;
          }
          else if(table[filaActual-1-j][columnaActual].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(columnaActual) < 9 ;j++){
          if(table[filaActual-1][columnaActual+j].ficha=='T' && table[filaActual-1][columnaActual+j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[1]++;
            break;
          }
          else if(table[filaActual-1][columnaActual+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (columnaActual-j)>=0 && j;j++){
          if(table[filaActual-1][columnaActual-j].ficha=='T' && table[filaActual-1][columnaActual-j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[1]++;
            break;
          }
          else if(table[filaActual-1][columnaActual-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==3 && contadorJaque[1]==0){
        //controla que un lancero pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          for(j=1; filaActual-1+j <9 ; j++){
            if(table[filaActual-1+j][columnaActual].ficha=='L' && table[filaActual-1+j][columnaActual].color=='n'){
              //hay un lancero que puede comerte
              contadorJaque[1]++;
              break;
            }
            else if(table[filaActual-1+j][columnaActual].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
        else{ //si es rey negro
          for(j=1; filaActual-1-j >=0 ; j++){
            if(table[filaActual-1-j][columnaActual].ficha=='L' && table[filaActual-1-j][columnaActual].color =='b'){
              //hay un lancero que puede comerte
              contadorJaque[1]++;
              break;
            }
            else if(table[filaActual-1-j][columnaActual].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
      }
      if(i==4 && contadorJaque[1]==0){
      //controla que un plata pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual-2][columnaActual-1].ficha == 'P' && table[filaActual-2][columnaActual-1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[1]++;
            break;
          }
          if(table[filaActual-2][columnaActual+1].ficha == 'P' && table[filaActual-2][columnaActual+1].color =='n'){
            //hay un plata que puede comerte
            contadorJaque[1]++;
            break;
          }

        }
        else{ //si es rey negro
          if(table[filaActual-2][columnaActual-1].ficha == 'P' && table[filaActual-2][columnaActual-1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[1]++;
            break;
          }
          if(table[filaActual-2][columnaActual+1].ficha == 'P'&& table[filaActual-2][columnaActual+1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[1]++;
            break;
          }
          if(table[filaActual-2][columnaActual].ficha == 'P'&& table[filaActual-2][columnaActual].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[1]++;
            break;
          }
        }
      }
      if(i==5 && contadorJaque[1]==0){
      //controla que un oro pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual-2][columnaActual].ficha == 'O' && table[filaActual-2][columnaActual].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[1]++;
          }
        }
        else{ //si es rey negro
          if(table[filaActual-2][columnaActual].ficha == 'O' && table[filaActual-2][columnaActual].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[1]++;
            break;
          }
          if(table[filaActual-2][columnaActual+1].ficha == 'O' && table[filaActual-2][columnaActual+1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[1]++;
            break;
          }
          if(table[filaActual-2][columnaActual-1].ficha == 'O' && table[filaActual-2][columnaActual-1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[1]++;
            break;
          }
        }
      }
      if(i==6 && contadorJaque[1]==0){
      //controla que un caballo pueda comerlo
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual-1+2][columnaActual+1].ficha=='C' && table[filaActual-1+2][columnaActual+1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[1]++;
            break;
          }
          if(table[filaActual-1+2][columnaActual-1].ficha=='C' && table[filaActual-1+2][columnaActual-1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[1]++;
            break;
          }

        }
        else{
          //Caballo negro
          if(table[filaActual-1-2][columnaActual+1].ficha=='C' && table[filaActual-1-2][columnaActual+1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[1]++;
            break;
          }
          if(table[filaActual-1-2][columnaActual-1].ficha=='C' && table[filaActual-1-2][columnaActual-1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[1]++;
            break;
          }
        }
      }
      if(i==7 && contadorJaque[1]==0){
      //controla que un rey pueda comerlo
        if(table[filaActual-2][columnaActual].ficha == 'R' && table[filaActual-2][columnaActual].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[1]++;
          break;
        }
        if(table[filaActual-2][columnaActual-1].ficha == 'R' && table[filaActual-2][columnaActual-1].color !=jaque){
          //hay un rey que puede comerte
          contadorJaque[1]++;
          break;
        }
        if(table[filaActual-2][columnaActual+1].ficha == 'R' && table[filaActual-2][columnaActual+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[1]++;
          break;
        }
      }
    }
  }
  //el rey se mueve abajo derecha
  if(filaActual+1 >= 0 && filaActual+1<9 && columnaActual+1 >= 0 && columnaActual+1<9 && table[filaActual+1][columnaActual+1].color!=jaque){
    for(i=0; i<8; i++){
      if(i==0 && contadorJaque[2]==0){
        //controla que un peon pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+2][columnaActual+1].ficha=='p' && table[filaActual+2][columnaActual+1].color=='n'){
            //hay un peon que puede comerte
            contadorJaque[2]++;
            break;
          }
        }
        else{ //si es rey negro
          //ningun peon blanco puede comerle
        }
      }
      if(i==1 && contadorJaque[2]==0){
        //controla que un alfil pueda comerlo en esa posicion
        for(j=1; j+(filaActual+1)<9 && columnaActual+1+j<9 ;j++){
          if(table[filaActual+1+j][columnaActual+1+j].ficha=='A' && table[filaActual+1+j][columnaActual+1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[2]++;
            break;
          }
          else if(table[filaActual+1+j][columnaActual+1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(filaActual+1)<9 && columnaActual+1-j>=0 ;j++){
          if(table[filaActual+1-j][columnaActual+1-j].ficha=='A' && table[filaActual+1-j][columnaActual+1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[2]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual+1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual+1)-j>=0 && columnaActual+1-j>=0 ;j++){
          if(table[filaActual+1-j][columnaActual+1-j].ficha=='A' && table[filaActual+1-j][columnaActual+1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[2]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual+1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual+1)-j>=0 && columnaActual+1+j<9 ;j++){
          if(table[filaActual+1-j][columnaActual+1+j].ficha=='A' && table[filaActual+1-j][columnaActual+1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[2]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual+1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==2 && contadorJaque[2]==0){
        //controla que un torre pueda comerlo en esa posicion
        for(j=1; j+(filaActual+1)<9;j++){
          if(table[filaActual+1+j][columnaActual+1].ficha=='T' && table[filaActual+1+j][columnaActual+1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[2]++;
            break;
          }
          else if(table[filaActual+1+j][columnaActual+1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual+1)-j >= 0 ;j++){
          if(table[filaActual+1-j][columnaActual+1].ficha=='T' && table[filaActual+1-j][columnaActual+1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[2]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual+1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(columnaActual+1) < 9 ;j++){
          if(table[filaActual+1][columnaActual+1+j].ficha=='T' && table[filaActual+1][columnaActual+1+j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[2]++;
            break;
          }
          else if(table[filaActual+1][columnaActual+1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (columnaActual+1-j)>=0 && j;j++){
          if(table[filaActual+1][columnaActual+1-j].ficha=='T' && table[filaActual+1][columnaActual+1-j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[2]++;
            break;
          }
          else if(table[filaActual+1][columnaActual+1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==3 && contadorJaque[2]==0){
        //controla que un lancero pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          for(j=1; filaActual+1+j <9 ; j++){
            if(table[filaActual+1+j][columnaActual+1].ficha=='L' && table[filaActual+1+j][columnaActual+1].color=='n'){
              //hay un lancero que puede comerte
              contadorJaque[2]++;
              break;
            }
            else if(table[filaActual+1+j][columnaActual+1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
        else{ //si es rey negro
          for(j=1; filaActual+1-j >=0 ; j++){
            if(table[filaActual+1-j][columnaActual+1].ficha=='L' && table[filaActual+1-j][columnaActual+1].color =='b'){
              //hay un lancero que puede comerte
              contadorJaque[2]++;
              break;
            }
            else if(table[filaActual+1-j][columnaActual+1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
      }
      if(i==4 && contadorJaque[2]==0){
      //controla que un plata pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+2][columnaActual+1].ficha == 'P' && table[filaActual+2][columnaActual+1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual+2][columnaActual+1-1].ficha == 'P' && table[filaActual+2][columnaActual+1-1].color =='n'){
            //hay un plata que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual+2][columnaActual+1+1].ficha == 'P' && table[filaActual+2][columnaActual+1+1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual][columnaActual+1+1].ficha == 'P' && table[filaActual][columnaActual+1+1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[2]++;
            break;
          }
        }
        else{ //si es rey negro
          if(table[filaActual+2][columnaActual+1-1].ficha == 'P' && table[filaActual+2][columnaActual+1-1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual+2][columnaActual+1+1].ficha == 'P'&& table[filaActual+2][columnaActual+1+1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual][columnaActual+1+1].ficha == 'P' && table[filaActual][columnaActual+1+1].color == 'b'){
            //hay un plata que puede comerte
            contadorJaque[2]++;
            break;
          }
        }
      }
      if(i==5 && contadorJaque[2]==0){
      //controla que un oro pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+2][columnaActual+1].ficha == 'O' && table[filaActual+2][columnaActual+1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual+2][columnaActual+1-1].ficha == 'O' && table[filaActual+2][columnaActual+1-1].color =='n'){
            //hay un oro que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual+2][columnaActual+1+1].ficha == 'O' && table[filaActual+2][columnaActual+1+1].color == 'n'){
            //hay un Oro que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual+1][columnaActual+1+1].ficha == 'O' && table[filaActual+1][columnaActual+1+1].color == 'n'){
            //hay un Oro que puede comerte
            contadorJaque[2]++;
            break;
          }
        }
        else{ //si es rey negro
          if(table[filaActual+2][columnaActual+1].ficha == 'O' && table[filaActual+2][columnaActual+1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual+1][columnaActual+2].ficha == 'O' && table[filaActual+1][columnaActual+2].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual][columnaActual+2].ficha == 'O' && table[filaActual][columnaActual+2].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[2]++;
            break;
          }
        }
      }
      if(i==6 && contadorJaque[2]==0){
      //controla que un caballo pueda comerlo
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+1+2][columnaActual+1+1].ficha=='C' && table[filaActual+1+2][columnaActual+1+1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual+1+2][columnaActual+1-1].ficha=='C' && table[filaActual+1+2][columnaActual+1-1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[2]++;
            break;
          }
        }
        else{
          //rey negro
          if(table[filaActual+1-2][columnaActual+1+1].ficha=='C' && table[filaActual+1-2][columnaActual+1+1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[2]++;
            break;
          }
          if(table[filaActual+1-2][columnaActual+1-1].ficha=='C' && table[filaActual+1-2][columnaActual+1-1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[2]++;
            break;
          }
        }
      }
      if(i==7 && contadorJaque[2]==0){
      //controla que un rey pueda comerlo
        if(table[filaActual+2][columnaActual+1].ficha == 'R' && table[filaActual+2][columnaActual+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[2]++;
          break;
        }
        if(table[filaActual+2][columnaActual+1-1].ficha == 'R' && table[filaActual+2][columnaActual+1-1].color !=jaque){
          //hay un rey que puede comerte
          contadorJaque[2]++;
          break;
        }
        if(table[filaActual+2][columnaActual+1+1].ficha == 'R' && table[filaActual+2][columnaActual+1+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[2]++;
          break;
        }
        if(table[filaActual+1][columnaActual+1+1].ficha == 'R' && table[filaActual+1][columnaActual+1+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[2]++;
          break;
        }
        if(table[filaActual][columnaActual+1+1].ficha == 'R' && table[filaActual][columnaActual+1+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[2]++;
          break;
        }
      }
    }
  }
  //el rey se mueve abajo izquierda
  if(filaActual+1 >= 0 && filaActual+1<9 && columnaActual-1 >= 0 && columnaActual-1<9 && table[filaActual+1][columnaActual-1].color!=jaque){
    for(i=0; i<8; i++){
      if(i==0 && contadorJaque[3]==0){
        //controla que un peon pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+2][columnaActual-1].ficha=='p' && table[filaActual+2][columnaActual-1].color=='n'){
            //hay un peon que puede comerte
            contadorJaque[3]++;
            break;
          }
        }
        else{ //si es rey negro
          //ningun peon blanco puede comerle
        }
      }
      if(i==1 && contadorJaque[3]==0){
        //controla que un alfil pueda comerlo en esa posicion
        for(j=1; j+(filaActual+1)<9 && columnaActual-1+j<9 ;j++){
          if(table[filaActual+1+j][columnaActual-1+j].ficha=='A' && table[filaActual+1+j][columnaActual-1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[3]++;
            break;
          }
          else if(table[filaActual+1+j][columnaActual-1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(filaActual+1)<9 && columnaActual-1-j>=0 ;j++){
          if(table[filaActual+1-j][columnaActual-1-j].ficha=='A' && table[filaActual+1-j][columnaActual-1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[3]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual-1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual+1)-j>=0 && columnaActual-1-j>=0 ;j++){
          if(table[filaActual+1-j][columnaActual-1-j].ficha=='A' && table[filaActual+1-j][columnaActual-1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[3]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual-1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual+1)-j>=0 && columnaActual-1+j<9 ;j++){
          if(table[filaActual+1-j][columnaActual-1+j].ficha=='A' && table[filaActual+1-j][columnaActual-1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[3]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual-1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==2 && contadorJaque[3]==0){
        //controla que un torre pueda comerlo en esa posicion
        for(j=1; j+(filaActual+1)<9;j++){
          if(table[filaActual+1+j][columnaActual-1].ficha=='T' && table[filaActual+1+j][columnaActual-1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[3]++;
            break;
          }
          else if(table[filaActual+1+j][columnaActual-1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual+1)-j >= 0 ;j++){
          if(table[filaActual+1-j][columnaActual-1].ficha=='T' && table[filaActual+1-j][columnaActual-1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[3]++;
            break;
          }
          else if(table[filaActual+1-j][columnaActual-1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(columnaActual-1) < 9 ;j++){
          if(table[filaActual+1][columnaActual-1+j].ficha=='T' && table[filaActual+1][columnaActual-1+j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[3]++;
            break;
          }
          else if(table[filaActual+1][columnaActual-1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (columnaActual-1-j)>=0 && j;j++){
          if(table[filaActual+1][columnaActual-1-j].ficha=='T' && table[filaActual+1][columnaActual-1-j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[3]++;
            break;
          }
          else if(table[filaActual+1][columnaActual-1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==3 && contadorJaque[3]==0){
        //controla que un lancero pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          for(j=1; filaActual+1+j <9 ; j++){
            if(table[filaActual+1+j][columnaActual-1].ficha=='L' && table[filaActual+1+j][columnaActual-1].color=='n'){
              //hay un lancero que puede comerte
              contadorJaque[3]++;
              break;
            }
            else if(table[filaActual+1+j][columnaActual-1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
        else{ //si es rey negro
          for(j=1; filaActual+1-j >=0 ; j++){
            if(table[filaActual+1-j][columnaActual-1].ficha=='L' && table[filaActual+1-j][columnaActual-1].color =='b'){
              //hay un lancero que puede comerte
              contadorJaque[3]++;
              break;
            }
            else if(table[filaActual+1-j][columnaActual-1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
      }
      if(i==4 && contadorJaque[3]==0){
      //controla que un plata pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+2][columnaActual-1].ficha == 'P' && table[filaActual+2][columnaActual-1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual+2][columnaActual-1-1].ficha == 'P' && table[filaActual+2][columnaActual-1-1].color =='n'){
            //hay un plata que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual+2][columnaActual-1+1].ficha == 'P' && table[filaActual+2][columnaActual-1+1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual][columnaActual-1-1].ficha == 'P' && table[filaActual][columnaActual-1-1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[3]++;
            break;
          }
        }
        else{ //si es rey negro
          if(table[filaActual+2][columnaActual-1-1].ficha == 'P' && table[filaActual+2][columnaActual-1-1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual+2][columnaActual-1+1].ficha == 'P'&& table[filaActual+2][columnaActual-1+1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual][columnaActual-1-1].ficha == 'P' && table[filaActual][columnaActual-1-1].color == 'b'){
            //hay un plata que puede comerte
            contadorJaque[3]++;
            break;
          }
        }
      }
      if(i==5 && contadorJaque[3]==0){
      //controla que un oro pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+2][columnaActual-1].ficha == 'O' && table[filaActual+2][columnaActual-1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual+2][columnaActual-1-1].ficha == 'O' && table[filaActual+2][columnaActual-1-1].color =='n'){
            //hay un oro que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual+2][columnaActual-1+1].ficha == 'O' && table[filaActual+2][columnaActual-1+1].color == 'n'){
            //hay un Oro que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual+1][columnaActual-1-1].ficha == 'O' && table[filaActual+1][columnaActual-1-1].color == 'n'){
            //hay un Oro que puede comerte
            contadorJaque[3]++;
            break;
          }
        }
        else{ //si es rey negro
          if(table[filaActual+2][columnaActual-1].ficha == 'O' && table[filaActual+2][columnaActual-1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual+1][columnaActual-2].ficha == 'O' && table[filaActual+1][columnaActual-2].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual][columnaActual-2].ficha == 'O' && table[filaActual][columnaActual-2].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[3]++;
            break;
          }
        }
      }
      if(i==6 && contadorJaque[3]==0){
      //controla que un caballo pueda comerlo
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+1+2][columnaActual-1+1].ficha=='C' && table[filaActual+1+2][columnaActual-1+1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual+1+2][columnaActual-1-1].ficha=='C' && table[filaActual+1+2][columnaActual-1-1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[3]++;
            break;
          }
        }
        else{
          //rey negro
          if(table[filaActual+1-2][columnaActual-1+1].ficha=='C' && table[filaActual+1-2][columnaActual-1+1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[3]++;
            break;
          }
          if(table[filaActual+1-2][columnaActual-1-1].ficha=='C' && table[filaActual+1-2][columnaActual-1-1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[3]++;
            break;
          }
        }
      }
      if(i==7 && contadorJaque[3]==0){
      //controla que un rey pueda comerlo
        if(table[filaActual+2][columnaActual-1].ficha == 'R' && table[filaActual+2][columnaActual-1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[3]++;
          break;
        }
        if(table[filaActual+2][columnaActual-1-1].ficha == 'R' && table[filaActual+2][columnaActual-1-1].color !=jaque){
          //hay un rey que puede comerte
          contadorJaque[3]++;
          break;
        }
        if(table[filaActual+2][columnaActual-1+1].ficha == 'R' && table[filaActual+2][columnaActual-1+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[3]++;
          break;
        }
        if(table[filaActual+1][columnaActual-1-1].ficha == 'R' && table[filaActual+1][columnaActual-1-1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[3]++;
          break;
        }
        if(table[filaActual][columnaActual-1-1].ficha == 'R' && table[filaActual][columnaActual-1-1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[3]++;
          break;
        }
      }
    }
  }
  //el rey se mueve arriba derecha
  if(filaActual-1 >= 0 && filaActual-1<9 && columnaActual+1 >= 0 && columnaActual+1<9 && table[filaActual-1][columnaActual+1].color!=jaque){
    for(i=0; i<8; i++){
      if(i==0 && contadorJaque[4]==0){
        //controla que un peon pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          //ningun peon negro puede comerle
        }
        else{ //si es rey negro
          if(table[filaActual-2][columnaActual+1].ficha=='p'&& table[filaActual-2][columnaActual+1].color=='b'){
            //hay un peon que puede comerte
            contadorJaque[4]++;
            break;
          }
        }
      }
      if(i==1 && contadorJaque[4]==0){
        //controla que un alfil pueda comerlo en esa posicion
        for(j=1; j+(filaActual-1)<9 && j+columnaActual+1<9 ;j++){
          if(table[filaActual-1+j][columnaActual+1+j].ficha=='A' && table[filaActual-1+j][columnaActual+1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[4]++;
            break;
          }
          else if(table[filaActual-1+j][columnaActual+1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(filaActual-1)<9 && columnaActual+1-j>=0 ;j++){
          if(table[filaActual-1+j][columnaActual+1-j].ficha=='A' && table[filaActual-1+j][columnaActual+1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[4]++;
            break;
          }
          else if(table[filaActual-1+j][columnaActual+1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual-1)-j>=0 && j+columnaActual+1<9 ;j++){
          if(table[filaActual-1-j][columnaActual+1+j].ficha=='A' && table[filaActual-1-j][columnaActual+1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[4]++;
            break;
          }
          else if(table[filaActual-1-j][columnaActual+1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual-1)-j>=0 && columnaActual+1-j>=0 ;j++){
          if(table[filaActual-1-j][columnaActual+1-j].ficha=='A' && table[filaActual-1-j][columnaActual+1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[4]++;
            break;
          }
          else if(table[filaActual-1-j][columnaActual+1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==2 && contadorJaque[4]==0){
        //controla que un torre pueda comerlo en esa posicion
        for(j=1; j+(filaActual-1)<9;j++){
          if(table[filaActual-1+j][columnaActual+1].ficha=='T' && table[filaActual-1+j][columnaActual+1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[4]++;
            break;
          }
          else if(table[filaActual-1+j][columnaActual+1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual-1)-j >= 0 ;j++){
          if(table[filaActual-1-j][columnaActual+1].ficha=='T' && table[filaActual-1-j][columnaActual+1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[4]++;
            break;
          }
          else if(table[filaActual-1-j][columnaActual+1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(columnaActual+1) < 9 ;j++){
          if(table[filaActual-1][columnaActual+1+j].ficha=='T' && table[filaActual-1][columnaActual+1+j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[4]++;
            break;
          }
          else if(table[filaActual-1][columnaActual+1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (columnaActual+1-j)>=0 && j;j++){
          if(table[filaActual-1][columnaActual+1-j].ficha=='T' && table[filaActual-1][columnaActual+1-j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[4]++;
            break;
          }
          else if(table[filaActual-1][columnaActual+1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==3 && contadorJaque[4]==0){
        //controla que un lancero pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          for(j=1; filaActual-1+j <9 ; j++){
            if(table[filaActual+1+j][columnaActual+1].ficha=='L' && table[filaActual+1+j][columnaActual+1].color=='n'){
              //hay un lancero que puede comerte
              contadorJaque[4]++;
              break;
            }
            else if(table[filaActual+1+j][columnaActual+1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
        else{ //si es rey negro
          for(j=1; filaActual-1-j >=0 ; j++){
            if(table[filaActual+1-j][columnaActual+1].ficha=='L' && table[filaActual+1-j][columnaActual+1].color =='b'){
              //hay un lancero que puede comerte
              contadorJaque[4]++;
              break;
            }
            else if(table[filaActual+1-j][columnaActual+1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
      }
      if(i==4 && contadorJaque[4]==0){
      //controla que un plata pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual-2][columnaActual+1-1].ficha == 'P' && table[filaActual-2][columnaActual+1-1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[4]++;
            break;
          }
          if(table[filaActual-2][columnaActual+1+1].ficha == 'P' && table[filaActual-2][columnaActual+1+1].color =='n'){
            //hay un plata que puede comerte
            contadorJaque[4]++;
            break;
          }
          if(table[filaActual][columnaActual+1+1].ficha == 'P' && table[filaActual][columnaActual+1+1].color =='n'){
            //hay un plata que puede comerte
            contadorJaque[4]++;
            break;
          }
        }
        else{ //si es rey negro
          if(table[filaActual-2][columnaActual+1-1].ficha == 'P' && table[filaActual-2][columnaActual+1-1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[4]++;
            break;
          }
          if(table[filaActual-2][columnaActual+1+1].ficha == 'P'&& table[filaActual-2][columnaActual+1+1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[4]++;
            break;
          }
          if(table[filaActual-2][columnaActual+1].ficha == 'P'&& table[filaActual-2][columnaActual+1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[4]++;
            break;
          }
          if(table[filaActual][columnaActual+1+1].ficha == 'P'&& table[filaActual][columnaActual+1+1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[4]++;
            break;
          }
        }
      }
      if(i==5 && contadorJaque[4]==0){
      //controla que un oro pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual-2][columnaActual+1].ficha == 'O' && table[filaActual-2][columnaActual+1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[4]++;
          }
          if(table[filaActual-1][columnaActual+1+1].ficha == 'O' && table[filaActual-1][columnaActual+1+1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[4]++;
          }
          if(table[filaActual][columnaActual+1+1].ficha == 'O' && table[filaActual][columnaActual+1+1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[4]++;
          }
        }
        else{ //si es rey negro
          if(table[filaActual-2][columnaActual+1].ficha == 'O' && table[filaActual-2][columnaActual+1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[4]++;
            break;
          }
          if(table[filaActual-2][columnaActual+1+1].ficha == 'O' && table[filaActual-2][columnaActual+1+1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[4]++;
            break;
          }
          if(table[filaActual-2][columnaActual+1-1].ficha == 'O' && table[filaActual-2][columnaActual+1-1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[4]++;
            break;
          }
          if(table[filaActual-1][columnaActual+1+1].ficha == 'O' && table[filaActual-1][columnaActual+1+1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[4]++;
            break;
          }
        }
      }
      if(i==6 && contadorJaque[4]==0){
      //controla que un caballo pueda comerlo
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual-1+2][columnaActual+1+1].ficha=='C' && table[filaActual-1+2][columnaActual+1+1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[4]++;
            break;
          }
          if(table[filaActual-1+2][columnaActual+1-1].ficha=='C' && table[filaActual-1+2][columnaActual+1-1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[4]++;
            break;
          }

        }
        else{
          //Caballo negro
          if(table[filaActual-1-2][columnaActual+1+1].ficha=='C' && table[filaActual-1+2][columnaActual+1+1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[4]++;
            break;
          }
          if(table[filaActual-1-2][columnaActual+1-1].ficha=='C' && table[filaActual-1-+2][columnaActual+1-1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[4]++;
            break;
          }
        }
      }
      if(i==7 && contadorJaque[4]==0){
      //controla que un rey pueda comerlo
        if(table[filaActual-2][columnaActual+1].ficha == 'R' && table[filaActual-2][columnaActual+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[4]++;
          break;
        }
        if(table[filaActual-2][columnaActual+1-1].ficha == 'R' && table[filaActual-2][columnaActual+1-1].color !=jaque){
          //hay un rey que puede comerte
          contadorJaque[4]++;
          break;
        }
        if(table[filaActual-2][columnaActual+1+1].ficha == 'R' && table[filaActual-2][columnaActual+1+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[4]++;
          break;
        }
        if(table[filaActual-1][columnaActual+1+1].ficha == 'R' && table[filaActual-1][columnaActual+1+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[4]++;
          break;
        }
        if(table[filaActual][columnaActual+1+1].ficha == 'R' && table[filaActual][columnaActual+1+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[4]++;
          break;
        }
      }
    }
  }
  //el rey se mueve arriba izquierda
  if(filaActual-1 >= 0 && filaActual-1<9 && columnaActual-1 >= 0 && columnaActual-1<9 && table[filaActual-1][columnaActual-1].color!=jaque){
    for(i=0; i<8; i++){
      if(i==0 && contadorJaque[5]==0){
        //controla que un peon pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          //ningun peon negro puede comerle
        }
        else{ //si es rey negro
          if(table[filaActual-2][columnaActual-1].ficha=='p'&& table[filaActual-2][columnaActual-1].color=='b'){
            //hay un peon que puede comerte
            contadorJaque[5]++;
            break;
          }
        }
      }
      if(i==1 && contadorJaque[5]==0){
        //controla que un alfil pueda comerlo en esa posicion
        for(j=1; j+(filaActual-1)<9 && j+columnaActual-1<9 ;j++){
          if(table[filaActual-1+j][columnaActual-1+j].ficha=='A' && table[filaActual-1+j][columnaActual-1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[5]++;
            break;
          }
          else if(table[filaActual-1+j][columnaActual-1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(filaActual-1)<9 && columnaActual-1-j>=0 ;j++){
          if(table[filaActual-1+j][columnaActual-1-j].ficha=='A' && table[filaActual-1+j][columnaActual-1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[5]++;
            break;
          }
          else if(table[filaActual-1+j][columnaActual-1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual-1)-j>=0 && j+columnaActual-1<9 ;j++){
          if(table[filaActual-1-j][columnaActual-1+j].ficha=='A' && table[filaActual-1-j][columnaActual-1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[5]++;
            break;
          }
          else if(table[filaActual-1-j][columnaActual-1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual-1)-j>=0 && columnaActual-1-j>=0 ;j++){
          if(table[filaActual-1-j][columnaActual-1-j].ficha=='A' && table[filaActual-1-j][columnaActual-1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[5]++;
            break;
          }
          else if(table[filaActual-1-j][columnaActual-1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==2 && contadorJaque[5]==0){
        //controla que un torre pueda comerlo en esa posicion
        for(j=1; j+(filaActual-1)<9;j++){
          if(table[filaActual-1+j][columnaActual-1].ficha=='T' && table[filaActual-1+j][columnaActual-1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[5]++;
            break;
          }
          else if(table[filaActual-1+j][columnaActual-1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual-1)-j >= 0 ;j++){
          if(table[filaActual-1-j][columnaActual-1].ficha=='T' && table[filaActual-1-j][columnaActual-1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[5]++;
            break;
          }
          else if(table[filaActual-1-j][columnaActual-1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(columnaActual-1) < 9 ;j++){
          if(table[filaActual-1][columnaActual-1+j].ficha=='T' && table[filaActual-1][columnaActual-1+j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[5]++;
            break;
          }
          else if(table[filaActual-1][columnaActual-1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (columnaActual-1-j)>=0 && j;j++){
          if(table[filaActual-1][columnaActual-1-j].ficha=='T' && table[filaActual-1][columnaActual-1-j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[5]++;
            break;
          }
          else if(table[filaActual-1][columnaActual-1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==3 && contadorJaque[5]==0){
        //controla que un lancero pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          for(j=1; filaActual-1+j <9 ; j++){
            if(table[filaActual+1+j][columnaActual-1].ficha=='L' && table[filaActual+1+j][columnaActual-1].color=='n'){
              //hay un lancero que puede comerte
              contadorJaque[5]++;
              break;
            }
            else if(table[filaActual+1+j][columnaActual-1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
        else{ //si es rey negro
          for(j=1; filaActual-1-j >=0 ; j++){
            if(table[filaActual+1-j][columnaActual-1].ficha=='L' && table[filaActual+1-j][columnaActual-1].color =='b'){
              //hay un lancero que puede comerte
              contadorJaque[5]++;
              break;
            }
            else if(table[filaActual+1-j][columnaActual-1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
      }
      if(i==4 && contadorJaque[5]==0){
      //controla que un plata pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual-2][columnaActual-1-1].ficha == 'P' && table[filaActual-2][columnaActual-1-1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[5]++;
            break;
          }
          if(table[filaActual-2][columnaActual-1+1].ficha == 'P' && table[filaActual-2][columnaActual-1+1].color =='n'){
            //hay un plata que puede comerte
            contadorJaque[5]++;
            break;
          }
          if(table[filaActual][columnaActual-1-1].ficha == 'P' && table[filaActual][columnaActual-1-1].color =='n'){
            //hay un plata que puede comerte
            contadorJaque[5]++;
            break;
          }
        }
        else{ //si es rey negro
          if(table[filaActual-2][columnaActual-1-1].ficha == 'P' && table[filaActual-2][columnaActual-1-1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[5]++;
            break;
          }
          if(table[filaActual-2][columnaActual-1+1].ficha == 'P'&& table[filaActual-2][columnaActual-1+1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[5]++;
            break;
          }
          if(table[filaActual-2][columnaActual-1].ficha == 'P'&& table[filaActual-2][columnaActual-1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[5]++;
            break;
          }
          if(table[filaActual][columnaActual-1-1].ficha == 'P'&& table[filaActual][columnaActual-1-1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[5]++;
            break;
          }
        }
      }
      if(i==5 && contadorJaque[5]==0){
      //controla que un oro pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual-2][columnaActual-1].ficha == 'O' && table[filaActual-2][columnaActual-1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[5]++;
          }
          if(table[filaActual-1][columnaActual-1-1].ficha == 'O' && table[filaActual-1][columnaActual-1-1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[5]++;
          }
          if(table[filaActual][columnaActual-1-1].ficha == 'O' && table[filaActual][columnaActual-1-1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[5]++;
          }
        }
        else{ //si es rey negro
          if(table[filaActual-2][columnaActual-1].ficha == 'O' && table[filaActual-2][columnaActual-1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[5]++;
            break;
          }
          if(table[filaActual-2][columnaActual-1+1].ficha == 'O' && table[filaActual-2][columnaActual-1+1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[5]++;
            break;
          }
          if(table[filaActual-2][columnaActual-1-1].ficha == 'O' && table[filaActual-2][columnaActual-1-1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[5]++;
            break;
          }
          if(table[filaActual-1][columnaActual-1-1].ficha == 'O' && table[filaActual-1][columnaActual-1-1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[5]++;
            break;
          }
        }
      }
      if(i==6 && contadorJaque[5]==0){
      //controla que un caballo pueda comerlo
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual-1+2][columnaActual-1+1].ficha=='C' && table[filaActual-1+2][columnaActual-1+1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[5]++;
            break;
          }
          if(table[filaActual-1+2][columnaActual-1-1].ficha=='C' && table[filaActual-1+2][columnaActual-1-1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[5]++;
            break;
          }

        }
        else{
          //Caballo negro
          if(table[filaActual-1-2][columnaActual-1+1].ficha=='C' && table[filaActual-1+2][columnaActual-1+1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[5]++;
            break;
          }
          if(table[filaActual-1-2][columnaActual-1-1].ficha=='C' && table[filaActual-1-+2][columnaActual-1-1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[5]++;
            break;
          }
        }
      }
      if(i==7 && contadorJaque[5]==0){
      //controla que un rey pueda comerlo
        if(table[filaActual-2][columnaActual-1].ficha == 'R' && table[filaActual-2][columnaActual-1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[5]++;
          break;
        }
        if(table[filaActual-2][columnaActual-1-1].ficha == 'R' && table[filaActual-2][columnaActual-1-1].color !=jaque){
          //hay un rey que puede comerte
          contadorJaque[5]++;
          break;
        }
        if(table[filaActual-2][columnaActual-1+1].ficha == 'R' && table[filaActual-2][columnaActual-1+1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[5]++;
          break;
        }
        if(table[filaActual-1][columnaActual-1-1].ficha == 'R' && table[filaActual-1][columnaActual-1-1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[5]++;
          break;
        }
        if(table[filaActual][columnaActual-1-1].ficha == 'R' && table[filaActual][columnaActual-1-1].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[5]++;
          break;
        }
      }
    }
  }
  //el rey se mueve a la derecha
  if(columnaActual+1 >= 0 && columnaActual+1<9 && table[filaActual][columnaActual+1].color!=jaque){
    for(i=1; i<8; i++){
      //peon no puede comer si se va a la derecha ni blanco ni negro
      if(i==1 && contadorJaque[6]==0){
        //controla que un alfil pueda comerlo en esa posicion
        for(j=1; j+(filaActual)<9 && j+columnaActual+1<9 ;j++){
          if(table[filaActual+j][columnaActual+1+j].ficha=='A' && table[filaActual+j][columnaActual+1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[6]++;
            break;
          }
          else if(table[filaActual+j][columnaActual+1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(filaActual)<9 && columnaActual+1-j>=0 ;j++){
          if(table[filaActual+j][columnaActual+1-j].ficha=='A' && table[filaActual+j][columnaActual+1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[6]++;
            break;
          }
          else if(table[filaActual+j][columnaActual+1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual)-j>=0 && j+columnaActual+1<9 ;j++){
          if(table[filaActual-j][columnaActual+1+j].ficha=='A' && table[filaActual-j][columnaActual+1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[6]++;
            break;
          }
          else if(table[filaActual-j][columnaActual+1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual)-j>=0 && columnaActual+1-j>=0 ;j++){
          if(table[filaActual-j][columnaActual+1-j].ficha=='A' && table[filaActual-j][columnaActual+1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[6]++;
            break;
          }
          else if(table[filaActual-j][columnaActual+1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==2 && contadorJaque[6]==0){
        //controla que un torre pueda comerlo en esa posicion
        for(j=1; j+(filaActual)<9;j++){
          if(table[filaActual+j][columnaActual+1].ficha=='T' && table[filaActual+j][columnaActual+1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[6]++;
            break;
          }
          else if(table[filaActual-1+j][columnaActual+1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual-1)-j >= 0 ;j++){
          if(table[filaActual-1-j][columnaActual+1].ficha=='T' && table[filaActual-1-j][columnaActual+1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[6]++;
            break;
          }
          else if(table[filaActual-j][columnaActual+1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(columnaActual+1) < 9 ;j++){
          if(table[filaActual][columnaActual+1+j].ficha=='T' && table[filaActual][columnaActual+1+j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[6]++;
            break;
          }
          else if(table[filaActual][columnaActual+1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (columnaActual+1-j)>=0 && j;j++){
          if(table[filaActual][columnaActual+1-j].ficha=='T' && table[filaActual][columnaActual+1-j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[6]++;
            break;
          }
          else if(table[filaActual][columnaActual+1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==3 && contadorJaque[6]==0){
        //controla que un lancero pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          for(j=1; filaActual+j <9 ; j++){
            if(table[filaActual+j][columnaActual+1].ficha=='L' && table[filaActual+j][columnaActual+1].color=='n'){
              //hay un lancero que puede comerte
              contadorJaque[6]++;
              break;
            }
            else if(table[filaActual+j][columnaActual+1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
        else{ //si es rey negro
          for(j=1; filaActual-j >=0 ; j++){
            if(table[filaActual-j][columnaActual+1].ficha=='L' && table[filaActual-j][columnaActual+1].color =='b'){
              //hay un lancero que puede comerte
              contadorJaque[6]++;
              break;
            }
            else if(table[filaActual-j][columnaActual+1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
      }
      if(i==4 && contadorJaque[6]==0){
      //controla que un plata pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+1][columnaActual+1+1].ficha == 'P' && table[filaActual+1][columnaActual+1+1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[6]++;
            break;
          }
          if(table[filaActual-1][columnaActual+1+1].ficha == 'P' && table[filaActual-1][columnaActual+1+1].color =='n'){
            //hay un plata que puede comerte
            contadorJaque[6]++;
            break;
          }
        }
        else{ //si es rey negro
          if(table[filaActual-1][columnaActual+1+1].ficha == 'P' && table[filaActual-1][columnaActual+1+1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[6]++;
            break;
          }
          if(table[filaActual+1][columnaActual+1+1].ficha == 'P'&& table[filaActual+1][columnaActual+1+1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[6]++;
            break;
          }
        }
      }
      if(i==5 && contadorJaque[6]==0){
      //controla que un oro pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual][columnaActual+1+1].ficha == 'O' && table[filaActual][columnaActual+1+1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[6]++;
          }
          if(table[filaActual+1][columnaActual+1+1].ficha == 'O' && table[filaActual+1][columnaActual+1+1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[6]++;
          }

        }
        else{ //si es rey negro
          if(table[filaActual-1][columnaActual+1+1].ficha == 'O' && table[filaActual-1][columnaActual+1+1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[6]++;
            break;
          }
          if(table[filaActual][columnaActual+1+1].ficha == 'O' && table[filaActual][columnaActual+1+1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[6]++;
            break;
          }
        }
      }
      if(i==6 && contadorJaque[6]==0){
      //controla que un caballo pueda comerlo
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual-1+2][columnaActual+1+1].ficha=='C' && table[filaActual-1+2][columnaActual+1+1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[6]++;
            break;
          }
          if(table[filaActual-1+2][columnaActual+1-1].ficha=='C' && table[filaActual-1+2][columnaActual+1-1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[6]++;
            break;
          }

        }
        else{
          //Caballo negro
          if(table[filaActual-1-2][columnaActual+1+1].ficha=='C' && table[filaActual-1-2][columnaActual+1+1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[6]++;
            break;
          }
          if(table[filaActual-1-2][columnaActual+1-1].ficha=='C' && table[filaActual-1-2][columnaActual+1-1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[6]++;
            break;
          }
        }
      }
      if(i==7 && contadorJaque[6]==0){
      //controla que un rey pueda comerlo
        if(table[filaActual-1][columnaActual+2].ficha == 'R' && table[filaActual-1][columnaActual+2].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[6]++;
          break;
        }
        if(table[filaActual+1][columnaActual+2].ficha == 'R' && table[filaActual+1][columnaActual+2].color !=jaque){
          //hay un rey que puede comerte
          contadorJaque[6]++;
          break;
        }
        if(table[filaActual][columnaActual+2].ficha == 'R' && table[filaActual][columnaActual+2].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[6]++;
          break;
        }
      }
    }
  }
  //el rey se mueve a la izquierda
  if(columnaActual-1 >= 0 && columnaActual-1<9 && table[filaActual][columnaActual-1].color!=jaque){
    for(i=1; i<8; i++){
      //peon no puede comer si se va a la derecha ni blanco ni negro
      if(i==1 && contadorJaque[7]==0){
        //controla que un alfil pueda comerlo en esa posicion
        for(j=1; j+(filaActual)<9 && j+columnaActual-1<9 ;j++){
          if(table[filaActual+j][columnaActual-1+j].ficha=='A' && table[filaActual+j][columnaActual-1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[7]++;
            break;
          }
          else if(table[filaActual+j][columnaActual-1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; j+(filaActual)<9 && columnaActual-1-j>=0 ;j++){
          if(table[filaActual+j][columnaActual-1-j].ficha=='A' && table[filaActual+j][columnaActual-1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[7]++;
            break;
          }
          else if(table[filaActual+j][columnaActual-1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual)-j>=0 && j+columnaActual-1<9 ;j++){
          if(table[filaActual-j][columnaActual-1+j].ficha=='A' && table[filaActual-j][columnaActual-1+j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[7]++;
            break;
          }
          else if(table[filaActual-j][columnaActual-1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual)-j>=0 && columnaActual-1-j>=0 ;j++){
          if(table[filaActual-j][columnaActual-1-j].ficha=='A' && table[filaActual-j][columnaActual-1-j].color!=jaque){
            //hay un alfil que puede comerte
            contadorJaque[7]++;
            break;
          }
          else if(table[filaActual-j][columnaActual+1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==2 && contadorJaque[7]==0){
        //controla que un torre pueda comerlo en esa posicion
        for(j=1; j+(filaActual)<9;j++){
          if(table[filaActual+j][columnaActual-1].ficha=='T' && table[filaActual+j][columnaActual-1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[7]++;
            break;
          }
          else if(table[filaActual+j][columnaActual-1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (filaActual)-j >= 0 ;j++){
          if(table[filaActual-j][columnaActual-1].ficha=='T' && table[filaActual-j][columnaActual-1].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[7]++;
            break;
          }
          else if(table[filaActual-j][columnaActual-1].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=3; j+(columnaActual-1) < 9 ;j++){
          if(table[filaActual][columnaActual-1+j].ficha=='T' && table[filaActual][columnaActual-1+j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[7]++;
            break;
          }
          else if(table[filaActual][columnaActual-1+j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
        for(j=1; (columnaActual-1-j)>=0;j++){
          if(table[filaActual][columnaActual-1-j].ficha=='T' && table[filaActual][columnaActual-1-j].color!=jaque){
            //hay un torre que puede comerte
            contadorJaque[7]++;
            break;
          }
          else if(table[filaActual][columnaActual-1-j].ficha!= 'x'){
            //hay algo en el medio
            break;
          }
        }
      }
      if(i==3 && contadorJaque[7]==0){
        //controla que un lancero pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          for(j=1; filaActual+j <9 ; j++){
            if(table[filaActual+j][columnaActual-1].ficha=='L' && table[filaActual+1+j][columnaActual-1].color=='n'){
              //hay un lancero que puede comerte
              contadorJaque[7]++;
              break;
            }
            else if(table[filaActual+j][columnaActual-1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
        else{ //si es rey negro
          for(j=1; filaActual-j >=0 ; j++){
            if(table[filaActual-j][columnaActual-1].ficha=='L' && table[filaActual-j][columnaActual-1].color =='b'){
              //hay un lancero que puede comerte
              contadorJaque[7]++;
              break;
            }
            else if(table[filaActual-j][columnaActual-1].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
      }
      if(i==4 && contadorJaque[7]==0){
      //controla que un plata pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+1][columnaActual-1-1].ficha == 'P' && table[filaActual+1][columnaActual-1-1].color == 'n'){
            //hay un plata que puede comerte
            contadorJaque[7]++;
            break;
          }
          if(table[filaActual-1][columnaActual-1-1].ficha == 'P' && table[filaActual-1][columnaActual-1-1].color =='n'){
            //hay un plata que puede comerte
            contadorJaque[7]++;
            break;
          }
        }
        else{ //si es rey negro
          if(table[filaActual-1][columnaActual-1-1].ficha == 'P' && table[filaActual-1][columnaActual-1-1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[7]++;
            break;
          }
          if(table[filaActual+1][columnaActual-1-1].ficha == 'P'&& table[filaActual+1][columnaActual-1-1].color=='b'){
            //hay un plata que puede comerte
            contadorJaque[7]++;
            break;
          }
        }
      }
      if(i==5 && contadorJaque[7]==0){
      //controla que un oro pueda comerlo en esa posicion
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual][columnaActual-1-1].ficha == 'O' && table[filaActual][columnaActual-1-1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[7]++;
          }
          if(table[filaActual+1][columnaActual-1-1].ficha == 'O' && table[filaActual+1][columnaActual-1-1].color == 'n'){
            //hay un oro que puede comerte
            contadorJaque[7]++;
          }

        }
        else{ //si es rey negro
          if(table[filaActual-1][columnaActual-1-1].ficha == 'O' && table[filaActual-1][columnaActual-1-1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[7]++;
            break;
          }
          if(table[filaActual][columnaActual-1-1].ficha == 'O' && table[filaActual][columnaActual-1-1].color == 'b'){
            //hay un oro que puede comerte
            contadorJaque[7]++;
            break;
          }
        }
      }
      if(i==6 && contadorJaque[7]==0){
      //controla que un caballo pueda comerlo
        if(jaque=='b'){ //si es rey blanco
          if(table[filaActual+2][columnaActual-1-1].ficha=='C' && table[filaActual+2][columnaActual-1-1].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[7]++;
            break;
          }
          if(table[filaActual+2][columnaActual].ficha=='C' && table[filaActual+2][columnaActual].color=='n'){
            //hay un caballo que puede comerte
            contadorJaque[7]++;
            break;
          }

        }
        else{
          //Caballo negro
          if(table[filaActual-2][columnaActual-1-1].ficha=='C' && table[filaActual-2][columnaActual-1-1].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[7]++;
            break;
          }
          if(table[filaActual-2][columnaActual].ficha=='C' && table[filaActual-2][columnaActual].color=='b'){
            //hay un caballo que puede comerte
            contadorJaque[7]++;
            break;
          }
        }
      }
      if(i==7 && contadorJaque[7]==0){
      //controla que un rey pueda comerlo
        if(table[filaActual-1][columnaActual-2].ficha == 'R' && table[filaActual-1][columnaActual-2].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[7]++;
          break;
        }
        if(table[filaActual+1][columnaActual-2].ficha == 'R' && table[filaActual+1][columnaActual-2].color !=jaque){
          //hay un rey que puede comerte
          contadorJaque[7]++;
          break;
        }
        if(table[filaActual][columnaActual-2].ficha == 'R' && table[filaActual][columnaActual-2].color != jaque){
          //hay un rey que puede comerte
          contadorJaque[7]++;
          break;
        }
      }
    }
  }
  //el rey en el mismo lugares
  if(table[filaActual][columnaActual].color==jaque){
      for(i=0; i<3; i++){
        //peon no puede comer si se va a la derecha ni blanco ni negro
        if(i==0 && contadorJaque[8]==0){
          //controla que un alfil pueda comerlo en esa posicion
          for(j=1; j+(filaActual)<9 && j+columnaActual<9 ;j++){
            if(table[filaActual+j][columnaActual+j].ficha=='A' && table[filaActual+j][columnaActual+j].color!=jaque){
              //hay un alfil que puede comerte
              contadorJaque[8]++;
              break;
            }
            else if(table[filaActual+j][columnaActual+j].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
          for(j=1; j+(filaActual)<9 && columnaActual-j>=0 ;j++){
            if(table[filaActual+j][columnaActual-j].ficha=='A' && table[filaActual+j][columnaActual-j].color!=jaque){
              //hay un alfil que puede comerte
              contadorJaque[8]++;
              break;
            }
            else if(table[filaActual+j][columnaActual-j].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
          for(j=1; (filaActual)-j>=0 && j+columnaActual<9 ;j++){
            if(table[filaActual-j][columnaActual+j].ficha=='A' && table[filaActual-j][columnaActual+j].color!=jaque){
              //hay un alfil que puede comerte
              contadorJaque[8]++;
              break;
            }
            else if(table[filaActual-j][columnaActual+j].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
          for(j=1; (filaActual)-j>=0 && columnaActual-j>=0 ;j++){
            if(table[filaActual-j][columnaActual-j].ficha=='A' && table[filaActual-j][columnaActual-j].color!=jaque){
              //hay un alfil que puede comerte
              contadorJaque[8]++;
              break;
            }
            else if(table[filaActual-j][columnaActual+1-j].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
        if(i==1 && contadorJaque[8]==0){
          //controla que un torre pueda comerlo en esa posicion
          for(j=1; j+(filaActual)<9;j++){
            if(table[filaActual+j][columnaActual].ficha=='T' && table[filaActual+j][columnaActual].color!=jaque){
              //hay un torre que puede comerte
              contadorJaque[8]++;
              break;
            }
            else if(table[filaActual+j][columnaActual].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
          for(j=1; (filaActual)-j >= 0 ;j++){
            if(table[filaActual-j][columnaActual].ficha=='T' && table[filaActual-j][columnaActual].color!=jaque){
              //hay un torre que puede comerte
              contadorJaque[8]++;
              break;
            }
            else if(table[filaActual-j][columnaActual].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
          for(j=2 ; columnaActual+j< 9 ; j++){
            if(table[filaActual][columnaActual+j].ficha=='T' && table[filaActual][columnaActual+j].color!=jaque){
              //hay un torre que puede comerte
              contadorJaque[8]++;
              break;
            }
            else if(table[filaActual][columnaActual+j].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
          for(j=1; (columnaActual-j)>=0;j++){
            if(table[filaActual][columnaActual-j].ficha=='T' && table[filaActual][columnaActual-j].color!=jaque){
              //hay un torre que puede comerte
              contadorJaque[8]++;
              break;
            }
            else if(table[filaActual][columnaActual-j].ficha!= 'x'){
              //hay algo en el medio
              break;
            }
          }
        }
        if(i==2 && contadorJaque[8]==0){
          //controla que un lancero pueda comerlo en esa posicion
          if(jaque=='b'){ //si es rey blanco
            for(j=1; filaActual+j <9 ; j++){
              if(table[filaActual+j][columnaActual].ficha=='L' && table[filaActual+j][columnaActual].color=='n'){
                //hay un lancero que puede comerte
                contadorJaque[8]++;
                break;
              }
              else if(table[filaActual+j][columnaActual].ficha!= 'x'){
                //hay algo en el medio
                break;
              }
            }
          }
          else{ //si es rey negro
            for(j=1; filaActual-j >=0 ; j++){
              if(table[filaActual-j][columnaActual].ficha=='L' && table[filaActual-j][columnaActual].color =='b'){
                //hay un lancero que puede comerte
                contadorJaque[8]++;
                break;
              }
              else if(table[filaActual-j][columnaActual].ficha!= 'x'){
                //hay algo en el medio
                break;
              }
            }
          }
        }
      }
    }

  for(i=0;i<9;i++){
    //printf("\ncontadorJaque=%d\n",contadorJaque[i]);
    if(contadorJaque[i]>0){
      checks++;
    }
  }
  if (checks==9) { //fue check mate
    if(jaque==jugadorHuman){ //perdio humano
      printf("\nHumano perdio! Gano PC\n");
      return 1;
    }
    else{
      printf("\nPC perdio! Gano Humano\n");
      return 1;
    }
  }

  return retorno;
}

//Esta funcion tiene el loop principal si empieza el humano y es negro
void juega_negro_human(){
  int jugadaH;
  int jugadaC;
  do{
    do{
      jugadaH=mueve_negro(jugadorHuman);
      if(jugadaH==-1)
        break;
    }while(jugadaH==1);
    imprime();
    if(jugadaH ==-1 || verifica_fin(jugadorPC) != 1){//termina la partida en ese turno
      break;
    }
    jugadaC=mueve_blanco(jugadorPC);
    imprime();
    if(jugadaC == -2)
      break;
    turnosRealizados++;
  }while(verifica_fin(jugadorHuman)==1);
}
//Esta funcion tiene el loop principal si empieza el humano y es blanco
void juega_blanco_human(){
  int jugadaH;
  int jugadaC;
  do{
    do{
      jugadaH=mueve_blanco(jugadorHuman);
      if(jugadaH==-1)
        break;
    }while(jugadaH==1);
    imprime();
    if(jugadaH== -1 || verifica_fin(jugadorPC) != 1 ){//termina la partida en ese turno
      break;
    }
    jugadaC=mueve_negro(jugadorPC);
    imprime();
    if(jugadaC==-2)
      break;
    turnosRealizados++;
  }while(verifica_fin(jugadorHuman)==1);
}

//Esta funcion tiene el loop principal si empieza el pc y es negro
void juega_negro_PC(){
  int jugadaH;
  int jugadaC;
  do{
    jugadaC=mueve_negro(jugadorPC);
    imprime();
    if(jugadaC== -2 || verifica_fin(jugadorHuman) != 1 )  {//termina la partida en ese turno
      break;
    }
    do{
      jugadaH=mueve_blanco(jugadorHuman);
      if(jugadaH == -1)
      break;
    }while(jugadaH==1);
    imprime();
    if(jugadaH == -1)
      break;
    turnosRealizados++;
  }while(verifica_fin(jugadorPC)==1);
}
//Esta funcion tiene el loop principal si empieza el pc y es blanco
void juega_blanco_PC(){
  int jugadaH;
  int jugadaC;
  do{
    jugadaC=mueve_blanco(jugadorPC);//hace rato llego aca pero hace como si movia negro
    imprime();
    if(jugadaC== -2 || verifica_fin(jugadorHuman) != 1){//termina la partida en ese turno
      break;
    }
    do{
      jugadaH=mueve_negro(jugadorHuman);
      if(jugadaH == -1)
        break;
    }while(jugadaH==1);
    imprime();
    if(jugadaH == -1)
      break;
    turnosRealizados++;
  }while(verifica_fin(jugadorPC)==1);
}

//En esta funcion retorna 1 si comio tranquilo y 0 si por ejemplo se encontro con alguna otra ficha en el camino
int come_reemplaza(char ficha,char filaActual,int columnaActual, char filaDestino, int columnaDestino){
  int i;
  if(ficha=='R' || ficha=='O' || ficha=='P' || ficha=='C'  || ficha == 'p'){
    table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
    table [filaDestino][columnaDestino].ficha= ficha ;
    table [filaActual][columnaActual].ficha='-';
    table [filaActual][columnaActual].color='x';
    return 1;
  }
  else if(ficha=='T'){
    //Cuando la torre va hacia abajo
    for(i=filaActual+1; i<=filaDestino; i++){
      if(table[i][columnaActual].color == 'x' && filaDestino!=i){ //vacio
        //printf("\nAvanza\n");
      }
      else if(table[i][columnaActual].color == 'x' && filaDestino==i){ //vacio destino
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else if (table[i][columnaActual].color != table[filaActual][columnaActual].color && i != filaDestino){
        printf("\nSe encontro una ficha del otro color por el camino!\n");
        return 0;
      }
      else if (table[i][columnaActual].color != table[filaActual][columnaActual].color && i == filaDestino){
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else{
        printf("\nPor el camino hay una ficha tuya!\n");
        return 0;
      }

    }
    //Cuando la torre va hacia arriba
    for(i=filaActual-1; i>=filaDestino; i--){
      if(table[i][columnaActual].color == 'x' && filaDestino != i ){ //vacio
        //printf("\nAvanza\n");
      }
      else if(table[i][columnaActual].color == 'x' && filaDestino==i){ //vacio destino
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else if (table[i][columnaActual].color != table[filaActual][columnaActual].color && i != filaDestino){
        printf("\nSe encontro una ficha del otro color por el camino!\n");
        return 0;
      }
      else if (table[i][columnaActual].color != table[filaActual][columnaActual].color && i == filaDestino){
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else{
        printf("\nPor el camino hay una ficha tuya!\n");
        return 0;
      }
    }
    //Cuando la torre va hacia la derecha
    for(i=columnaActual+1; i<=columnaDestino; i++){
      if(table[filaActual][i].color == 'x' && columnaDestino!=i){ //vacio
        //printf("\nAvanza\n");
      }
      else if(table[filaActual][i].color == 'x' && columnaDestino==i){ //vacio
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else if (table[filaActual][i].color != table[filaActual][columnaActual].color && i != columnaDestino){
        printf("\nSe encontro una ficha del otro color por el camino!\n");
        return 0;
      }
      else if (table[filaActual][i].color != table[filaActual][columnaActual].color && i == columnaDestino){
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else{
        printf("\nPor el camino hay una ficha tuya!\n");
        return 0;
      }
    }
    //Cuando la torre va hacia la izquierda
    for(i=columnaActual-1; i>=columnaDestino; i--){
      if(table[filaActual][i].color == 'x' && columnaDestino!=i){ //vacio
        //printf("\nAvanza\n");
      }
      else if(table[filaActual][i].color == 'x' && columnaDestino==i){ //vacio
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else if (table[filaActual][i].color != table[filaActual][columnaActual].color && i != columnaDestino){
        printf("\nSe encontro una ficha del otro color por el camino!\n");
        return 0;
      }
      else if (table[filaActual][i].color != table[filaActual][columnaActual].color && i == columnaDestino){
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else{
        printf("\nPor el camino hay una ficha tuya!\n");
        return 0;
      }
    }
  }
  else if(ficha == 'A'){
    //Cuando alfil va abajo derecha
    for(i=1; i+filaActual<=filaDestino ; i++){
      if(table[i+filaActual][i+columnaActual].color == 'x' &&  filaDestino != i+filaActual ){ //vacio
        //printf("\nAvanza\n");
      }
      else if(table[i+filaActual][i+columnaActual].color == 'x' && filaDestino == i+filaActual){ //vacio destino
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else if (table[i+filaActual][i+columnaActual].color != table[filaActual][columnaActual].color && i+filaActual != filaDestino){
        printf("\nSe encontro una ficha del otro color por el camino!\n");
          return 0;
      }
      else if (table[i+filaActual][i+columnaActual].color != table[filaActual][columnaActual].color && i+filaActual == filaDestino){
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else{
        printf("\nPor el camino hay una ficha tuya!\n");
        return 0;
      }
    }
    //Cuando alfil va arriba derecha
    for(i=1; filaActual-i>=filaDestino ; i++){
      if(table[filaActual-i][i+columnaActual].color == 'x' &&  filaDestino != filaActual-i ){ //vacio
        //printf("\nAvanza\n");
      }
      else if(table[filaActual-i][i+columnaActual].color == 'x' && filaDestino == filaActual-i){ //vacio destino
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else if (table[filaActual-i][i+columnaActual].color != table[filaActual][columnaActual].color && filaActual-i != filaDestino){
        printf("\nSe encontro una ficha del otro color por el camino!\n");
          return 0;
      }
      else if (table[filaActual-i][columnaActual].color != table[filaActual][columnaActual].color && filaActual-i == filaDestino){
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else{
        printf("\nPor el camino hay una ficha tuya!\n");
        return 0;
      }
    }
    //Cuando alfil va abajo izquierda
    for(i=1; i+filaActual<=filaDestino ; i++){
      if(table[i+filaActual][columnaActual-i].color == 'x' &&  filaDestino != i+filaActual ){ //vacio
        //printf("\nAvanza\n");
      }
      else if(table[i+filaActual][columnaActual-i].color == 'x' && filaDestino == i+filaActual){ //vacio destino
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else if (table[i+filaActual][columnaActual-i].color != table[filaActual][columnaActual].color && i+filaActual != filaDestino){
        printf("\nSe encontro una ficha del otro color por el camino!\n");
          return 0;
      }
      else if (table[i+filaActual][columnaActual-i].color != table[filaActual][columnaActual].color && i+filaActual == filaDestino){
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else{
        printf("\nPor el camino hay una ficha tuya!\n");
        return 0;
      }
    }
    //Cuando alfil va arriba izquierda
    for(i=1; filaActual-i>=filaDestino ; i++){
      if(table[filaActual-i][columnaActual-i].color == 'x' &&  filaDestino != filaActual-i ){ //vacio
        //printf("\nAvanza\n");
      }
      else if(table[filaActual-i][columnaActual-i].color == 'x' && filaDestino == filaActual-i){ //vacio destino
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else if (table[filaActual-i][columnaActual-i].color != table[filaActual][columnaActual].color && filaActual-i != filaDestino){
        printf("\nSe encontro una ficha del otro color por el camino!\n");
          return 0;
      }
      else if (table[filaActual-i][columnaActual-i].color != table[filaActual][columnaActual].color && filaActual-i == filaDestino){
        table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
        table [filaDestino][columnaDestino].ficha= ficha ;
        table [filaActual][columnaActual].ficha='-';
        table [filaActual][columnaActual].color='x';
        return 1;
      }
      else{
        printf("\nPor el camino hay una ficha tuya!\n");
        return 0;
      }
    }
  }
  else if(ficha == 'L'){
    if(table[filaActual][columnaActual].color == 'n'){ //lancero negro
      //Cuando lancero va hacia arriba
      for(i=filaActual-1; i>=filaDestino; i--){
        if(table[i][columnaActual].color == 'x' && filaDestino != i ){ //vacio
          //printf("\nAvanza\n");
        }
        else if(table[i][columnaActual].color == 'x' && filaDestino==i){ //vacio y destino
          table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
          table [filaDestino][columnaDestino].ficha= ficha ;
          table [filaActual][columnaActual].ficha='-';
          table [filaActual][columnaActual].color='x';
          return 1;
        }
        else if (table[i][columnaActual].color != table[filaActual][columnaActual].color && i != filaDestino){
          printf("\nSe encontro una ficha del otro color por el camino!\n");
          return 0;
        }
        else if (table[i][columnaActual].color != table[filaActual][columnaActual].color && i == filaDestino){
          table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
          table [filaDestino][columnaDestino].ficha= ficha ;
          table [filaActual][columnaActual].ficha='-';
          table [filaActual][columnaActual].color='x';
          return 1;
        }
        else{
          printf("\nPor el camino hay una ficha tuya!\n");
          return 0;
        }
      }
    }
    else{ //lancero blanco
      //Cuando lancero va hacia abajo
      for(i=filaActual+1; i<=filaDestino; i++){
        if(table[i][columnaActual].color == 'x' && filaDestino!=i){ //vacio
          //printf("\nAvanza\n");
        }
        else if(table[i][columnaActual].color == 'x' && filaDestino==i){ //vacio destino
          table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
          table [filaDestino][columnaDestino].ficha= ficha ;
          table [filaActual][columnaActual].ficha='-';
          table [filaActual][columnaActual].color='x';
          return 1;
        }
        else if (table[i][columnaActual].color != table[filaActual][columnaActual].color && i != filaDestino){
          printf("\nSe encontro una ficha del otro color por el camino!\n");
          return 0;
        }
        else if (table[i][columnaActual].color != table[filaActual][columnaActual].color && i == filaDestino){
          table [filaDestino][columnaDestino].color= table [filaActual][columnaActual].color;
          table [filaDestino][columnaDestino].ficha= ficha ;
          table [filaActual][columnaActual].ficha='-';
          table [filaActual][columnaActual].color='x';
          return 1;
        }
        else{
          printf("\nPor el camino hay una ficha tuya!\n");
          return 0;
        }
      }
    }
  }
  else{
    printf("\nError llega aca y se eligio una ficha que no es ninguna de las anteriores\n");
  }
}

//En esta funcion dependiendo de que parametro reciba jugara humano o PC las fichas negras
//Retornara 0 si no hubo problemas y se movio a una posicion o comio una ficha enemiga o se rindio y retornara 1 si el lugar de destino que eligio esta ocupada por una negra, retornara -1 si el humano se rindio
//retornara -2 si la pc quiere rendirse
int mueve_negro(char juega){
  char filaActual;
  int columnaActual;
  char filaDestino;
  int columnaDestino;
  int banderaInput=0;
  int opcion;
  if(jugadorHuman == juega){ //juega humano
    printf("\nElija si quiere jugar [1] o [2] si desea rendirse: ");
    scanf("%d", &opcion);
    while(getchar()!='\n'); //limpia buffer porque o si no imprime 2 veces
    if(opcion==1){
      printf("\n");
      printf("\nEscriba que ficha desea mover y a que coordenada en el formato [letra],[numero]-[letra],[numero]: ");
      scanf("%c,%d-%c,%d", &filaActual, &columnaActual, &filaDestino, &columnaDestino);
      while(getchar()!='\n'); //limpia buffer porque o si no imprime 2 veces
      if((filaActual-'a') < 0 || (filaActual-'a') > 8 || (columnaActual-1) < 0 || (columnaActual-1) > 8 ||
        (filaDestino-'a') < 0 || (filaDestino-'a') > 8 || (columnaDestino-1) < 0 || (columnaDestino-1) > 8 ){
          banderaInput= 1;
      }
      if(banderaInput){
        do{
          printf("\nSe introducieron datos fuera del rango, escriba de nuevo [letra],[numero]-[letra],[numero]>");
          scanf("%c,%d-%c,%d", &filaActual, &columnaActual, &filaDestino, &columnaDestino);
          while(getchar()!='\n'); //limpia buffer porque o si no imprime 2 veces
          if((filaActual-'a') >= 0 && (filaActual-'a') <= 8 && (9-columnaActual) >= 0 && (9-columnaActual) <= 8 &&
            (filaDestino-'a') >= 0 && (filaDestino-'a') <= 8 && (9-columnaDestino) >= 0 && (9-columnaDestino) <= 8 ){
              //Si ingreso algo dentro del rango controla de que sea el color que debe ser
              if(table[filaActual-'a'][9-columnaActual].color == 'b'){
                printf("\nIngreso coordenadas dentro del rango pero esta ficha no es negra!\n");

              }
              else if (table[filaActual-'a'][9-columnaActual].color == 'n'){
                banderaInput=0;//Ingreso dentro de rango y la ficha es negra
              }
              else{
                printf("\nNo hay ficha blanca o negra\n");
              }
            }
        }while(banderaInput);
      }

      puts("\nIngreso todo chill\n");

      filaActual=filaActual-'a' ;
      filaDestino=filaDestino-'a' ;
      columnaActual=9-columnaActual;
      columnaDestino=9-columnaDestino;

      //printf("\n\t\tColumna destino= %d || Columna actual= %d\n", columnaActual, columnaDestino);

      if(table[filaActual][columnaActual].ficha == '-'){
        printf("La ficha que quiere mover no se encuentra alli\n");
        return 1;
      }

      //Aqui se ve que ficha es la de la ubicacion actual (sabemos que es negra y que tanto la ficha como el destino son coordenadas en el rango) y que es una ficha negra
      if (table[filaActual] [columnaActual].ficha == 'p' ) {
        //peon negro solo hacia arriba
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a', 9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n Esta posicion de destino es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
      else if (table[filaActual] [columnaActual].ficha== 'R'){
        //el rey se mueve abajo
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve arriba
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve abajo derecha
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve arriba derecha
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve arriba izquierda
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve abajo izquierda
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve a la derecha
        if(filaDestino == filaActual && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve a la izquierda
        if(filaDestino == filaActual && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
      else if (table[filaActual] [columnaActual].ficha == 'T'){
        //Torre hacia arriba o abajo
        if((filaDestino > filaActual || filaDestino < filaActual ) && (columnaDestino == columnaActual) ){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }

        //Torre hacia derecha o izquierda
        if((filaDestino == filaActual ) && (columnaDestino > columnaActual || columnaDestino < columnaActual) ){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }

      }
      else if (table[filaActual][columnaActual].ficha == 'A'){
        //el alfil se mueve abajo derecha y arriba izquierda
        if( filaActual-filaDestino == columnaActual-columnaDestino){
          if(table[filaDestino][columnaDestino].color== 'b' || table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el alfil se mueve abajo izquierda y arriba derecha
        if( filaActual-filaDestino == columnaDestino-columnaActual){
          if(table[filaDestino][columnaDestino].color== 'b' || table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
      else if (table[filaActual] [columnaActual].ficha == 'L'){
        //Lancero negro va hacia arriba
        if( filaDestino < filaActual  && columnaDestino == columnaActual ){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
      else if (table[filaActual] [columnaActual].ficha == 'P'){

        //el plata se mueve arriba
        if(filaDestino == filaActual-1 && columnaDestino == columnaActual){
          if(table[filaDestino][columnaDestino].color== 'b' ||table[filaDestino][columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el plata se mueve abajo derecha
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el plata se mueve arriba derecha
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el plata se mueve arriba izquierda
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el plata se mueve abajo izquierda
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }

      }
      else if (table[filaActual] [columnaActual].ficha == 'O'){
        //el oro se mueve abajo
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el oro se mueve arriba
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }

        //el oro se mueve arriba derecha
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el oro se mueve arriba izquierda
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }

        //el oro se mueve a la derecha
        if(filaDestino == filaActual && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el oro se mueve a la izquierda
        if(filaDestino == filaActual && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'b' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
      else{  //caballo
        if(filaDestino == filaActual -2 && columnaDestino == columnaActual -1){    //el caballo se mueve arriba a la izquierda
          if(table [filaDestino][columnaDestino].color== 'b' || table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t\tSe realizo una jugada satisfactoria, el jugador=%c movio su ficha %c de %d,%d a %d,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual,columnaActual,filaDestino,columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        if(filaDestino == filaActual -2 && columnaDestino == columnaActual+1){    //el caballo se mueve arriba a la derecha
          if(table [filaDestino][columnaDestino].color== 'b' || table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t\tSe realizo una jugada satisfactoria, el jugador=%c movio su ficha %c de %d,%d a %d,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual,columnaActual,filaDestino,columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
    }
    else if(opcion==2){
      //El Humano desea rendirse
      printf("\nEl humano se rindio! Gano PC\n");
      //fin_juego();
      return -1;
    }
  }
  else{ //Juega PC
    puts("Jugara pc");
    if(rand()%8){ //si da cualquier numero distinto de 0 decide jugar
      opcion=inteligenciaPC(juega);
      //printf("\npc jugo=%d \n",opcion);
    }
    else{
      //La pc desea rendirse
      printf("\nLa PC se rindio! Gano Humano\n");
      return -2;
    }
  }
}

//En esta funcion dependiendo de que parametro reciba jugara humano o PC las fichas blancas
//Retornara 0 si no hubo problemas y se movio a una posicion o comio una ficha enemiga o se rindio y retornara 1 si el lugar de destino que eligio esta ocupada por una blanca, retornara -1 si el humano se rindio
//retornara -2 si la pc quiere rendirse
int mueve_blanco(char juega){
  char filaActual;
  int columnaActual;
  char filaDestino;
  int columnaDestino;
  int banderaInput=0;
  int opcion;
  if(jugadorHuman == juega){ //juega humano
    printf("Elija si quiere jugar [1] o [2] si desea rendirse: ");
    scanf("%d", &opcion);
    while(getchar()!='\n'); //limpia buffer porque o si no imprime 2 veces
    if(opcion==1){
      printf("\n");
      printf("\nEscriba que ficha desea mover y a que coordenada en el formato [letra],[numero]-[letra],[numero]: ");
      scanf("%c,%d-%c,%d", &filaActual, &columnaActual, &filaDestino, &columnaDestino);
      while(getchar()!='\n'); //limpia buffer porque o si no imprime 2 veces
      if((filaActual-'a') < 0 || (filaActual-'a') > 8 || (columnaActual-1) < 0 || (columnaActual-1) > 8 ||
        (filaDestino-'a') < 0 || (filaDestino-'a') > 8 || (columnaDestino-1) < 0 || (columnaDestino-1) > 8 ){
          banderaInput= 1;
      }
      if(banderaInput){
        do{
          printf("\nSe introducieron datos fuera del rango, escriba de nuevo [letra],[numero]-[letra],[numero]>");
          scanf("%c,%d-%c,%d", &filaActual, &columnaActual, &filaDestino, &columnaDestino);
          while(getchar()!='\n'); //limpia buffer porque o si no imprime 2 veces
          if((filaActual-'a') >= 0 && (filaActual-'a') <= 8 && (9-columnaActual) >= 0 && (9-columnaActual) <= 8 &&
            (filaDestino-'a') >= 0 && (filaDestino-'a') <= 8 && (9-columnaDestino) >= 0 && (9-columnaDestino) <= 8 ){
              //Si ingreso algo dentro del rango controla de que sea el color que debe ser
              if(table[filaActual-'a'][9-columnaActual].color == 'n'){
                printf("\nIngreso coordenadas dentro del rango pero esta ficha no es blanca!\n");

              }
              else if (table[filaActual-'a'][9-columnaActual].color == 'b'){
                banderaInput=0;//Ingreso dentro de rango y la ficha es blanca
              }
              else{
                printf("\nNo hay ficha blanca o negra\n");
              }
            }
        }while(banderaInput);
      }

      puts("\nIngreso todo chill\n");
      filaActual=filaActual-'a' ;
      filaDestino=filaDestino-'a' ;
      columnaActual=9-columnaActual;
      columnaDestino=9-columnaDestino;

      if(table[filaActual][columnaActual].ficha == '-'){
        printf("La ficha que quiere mover no se encuentra alli\n");
        return 1;
      }

      //Aqui se ve que ficha es la de la ubicacion actual (sabemos que es blanca y que tanto la ficha como el destino son coordenadas en el rango) y que es una ficha blanca
      if (table[filaActual][columnaActual].ficha == 'p' ) {
        //peon blanco solo hacia abajo
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
      else if (table[filaActual] [columnaActual].ficha== 'R'){
        //el rey se mueve abajo
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve arriba
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve abajo derecha
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve arriba derecha
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve arriba izquierda
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve abajo izquierda
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve a la derecha
        if(filaDestino == filaActual && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el rey se mueve a la izquierda
        if(filaDestino == filaActual && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
      else if (table[filaActual] [columnaActual].ficha == 'T'){
        //Torre hacia arriba o abajo
        if((filaDestino > filaActual || filaDestino < filaActual ) && (columnaDestino == columnaActual) ){
          if(table[filaDestino] [columnaDestino].color== 'n' || table[filaDestino][columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }

        //Torre hacia derecha o izquierda
        if((filaDestino == filaActual ) && (columnaDestino > columnaActual || columnaDestino < columnaActual) ){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }

      }
      else if (table[filaActual] [columnaActual].ficha == 'A'){
        //el alfil se mueve abajo derecha y arriba izquierda
        if( filaActual-filaDestino == columnaActual-columnaDestino){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el alfil se mueve abajo izquierda y arriba derecha
        if( filaActual-filaDestino == columnaDestino-columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
      else if (table[filaActual] [columnaActual].ficha == 'L'){
        //Lancero blanco va hacia abajo
        if( filaDestino > filaActual  && columnaDestino == columnaActual ){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
      else if (table[filaActual] [columnaActual].ficha == 'P'){

        //el plata se mueve abajo
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el plata se mueve arriba izquierda
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el plata se mueve abajo izquierda
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el plata se mueve abajo derecha
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el plata se mueve arriba derecha
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }

      }
      else if (table[filaActual] [columnaActual].ficha == 'O'){
        //el oro se mueve arriba
        if(filaDestino == filaActual -1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el oro se mueve abajo
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }

        //el oro se mueve abajo izquierda
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el oro se mueve abajo derecha
        if(filaDestino == filaActual +1 && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }

        //el oro se mueve a la izquierda
        if(filaDestino == filaActual && columnaDestino == columnaActual-1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        //el oro se mueve a la derecha
        if(filaDestino == filaActual && columnaDestino == columnaActual+1){
          if(table[filaDestino] [columnaDestino].color== 'n' ||table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
      else{  //caballo
        if(filaDestino == filaActual +2 && columnaDestino == columnaActual +1){    //el caballo se mueve abajo a la derecha
          if(table [filaDestino][columnaDestino].color== 'n' || table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        if(filaDestino == filaActual +2 && columnaDestino == columnaActual-1){    //el caballo se mueve arriba a la izquierda
          if(table [filaDestino][columnaDestino].color== 'n' || table[filaDestino] [columnaDestino].color=='x'){
            if(come_reemplaza(table[filaActual] [columnaActual].ficha, filaActual, columnaActual, filaDestino, columnaDestino)){
              printf("\n\t>>>>Se realizo una jugada satisfactoria, el jugador='%c' movio su ficha '%c' de %c,%d a %c,%d\n",juega, table[filaDestino][columnaDestino].ficha, filaActual+'a',9-columnaActual ,filaDestino+'a',9-columnaDestino);
              return 0;
            }
            else
              return 1;
          }
          else{
            printf("\n Esta posicion de destino esta ocupada por una de tus fichas!\n");
            //Accion para que vuelva elegir posicion
            return 1;
          }
        }
        else{
          printf("\n La posicion es invalida\n");
          //Accion para que vuelva elegir posicion
          return 1;
        }
      }
    }
    else if(opcion==2){
      //El Humano desea rendirse
      printf("\nEl humano se rindio! gano PC\n");
      //fin_juego();
      return -1;
    }
  }
  else{ //Juega PC
    puts("Jugara pc");

    if(rand()%8){ //si da cualquier numero distinto de 0 decide jugar
      opcion=inteligenciaPC(juega);
      //printf("\nPc=%d\n", opcion);
    }
    else{
      //La pc desea rendirse
      printf("\nLa PC se rindio! Gano Humano\n");
      return -2;
    }
  }
}

//Inteligencia de pc ve donde estan sus fichas y dependiendo que sea esa ficha intenta comer algo y si no encuentra se mueve solo 1 lugar (si puede)
int inteligenciaPC(char juega){
  int retorno=0;
  int i, j, k,l;
  //Si alguna ficha puede comer algo
  for(i=0; i<9 ;i++){
    for(j=0; j<9 ;j++){
      if(table[i][j].color == juega){
        //movimientos para cada una de las fichas
        if(table[i][j].ficha == 'p'){

          if(juega=='n'){
            if(i-1>=0 && table[i-1][j].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j);
              return 1;
            }
          }
          else{
            if(i+1<9 && table[i+1][j].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j);
              return 1;
            }
          }
        }
        if(table[i][j].ficha == 'A'){

          for(k=1;i+k<9 && j+k<9 ;k++){
            if(table[i+k][j+k].color!=juega && table[i+k][j+k].ficha!='-'){
              come_reemplaza(table[i][j].ficha, i, j, i+k, j+k);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+k, 9-j-k);
              return 1;
            }
            if(table[i+k][j+k].color==juega){
              break;
            }
          }
          for(k=1;i-k>=0 && j-k>=0 ;k++){
            if(table[i-k][j-k].color!=juega && table[i-k][j-k].ficha!='-'){
            come_reemplaza(table[i][j].ficha, i, j, i-k, j-k);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-k, 9-j+k);
            return 1;
            }
            if(table[i-k][j-k].color==juega){
              break;
            }
          }
          for(k=1;i-k>=0 && j+k<9 ;k++){
            if(table[i-k][j+k].color!=juega && table[i-k][j+k].ficha!='-'){
            come_reemplaza(table[i][j].ficha, i, j, i-k, j+k);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-k, 9-j-k);
            return 1;
            }
            if(table[i-k][j+k].color==juega){
              break;
            }
          }
          for(k=1;i+k<9 && j-k>=0 ;k++){
            if(table[i+k][j-k].color!=juega && table[i+k][j-k].ficha!='-'){
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+k, 9-j+k);
            return 1;
            }
            if(table[i+k][j-k].color==juega){
              break;
            }
          }
        }
        if(table[i][j].ficha == 'T'){

          for(k=1;j+k<9 ;k++){
            if(table[i][j+k].color!=juega && table[i][j+k].ficha!='-'){
              come_reemplaza(table[i][j].ficha, i, j, i, j+k);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i, 9-j-k);
              return 1;
            }
            if(table[i][j+k].color==juega){
              break;
            }
          }
          for(k=1;j-k>=0 ;k++){
            if(table[i][j-k].color!=juega && table[i][j-k].ficha!='-'){
            come_reemplaza(table[i][j].ficha, i, j, i, j-k);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i, 9-j+k);
            return 1;
            }
            if(table[i][j-k].color==juega){
              break;
            }
          }
          for(k=1;i-k>=0;k++){
            if(table[i-k][j].color!=juega && table[i-k][j].ficha!='-'){
            come_reemplaza(table[i][j].ficha, i, j, i-k, j);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-k, 9-j);
            return 1;
            }
            if(table[i-k][j].color==juega){
              break;
            }
          }
          for(k=1;i+k<9;k++){
            if(table[i+k][j].color!=juega && table[i+k][j].ficha!='-'){
            come_reemplaza(table[i][j].ficha, i, j, i+k, j);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+k, 9-j);
            return 1;
            }
            if(table[i+k][j].color==juega){
              break;
            }
          }
        }
        if(table[i][j].ficha == 'P'){

          if(juega=='n'){
            if(i-1>=0 && i-1<9 && table[i-1][j-1].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j+1);
              return 1;
            }
            if(i-1>=0 && j+1<9 && table[i-1][j+1].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j-1);
              return 1;
            }
            if(i+1<9 && j-1>=0 && table[i+1][j-1].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j+1);
              return 1;
            }
            if(i+1<9 && j+1<9 && table[i+1][j+1].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j-1);
              return 1;
            }
            if(i-1>=0 && table[i-1][j].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j);
              return 1;
            }
          }
          else{
            if(i-1>=0 && i-1<9 && table[i-1][j-1].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j+1);
              return 1;
            }
            if(i-1>=0 && j+1<9 && table[i-1][j+1].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j-1);
              return 1;
            }
            if(i+1<9 && j-1>=0 && table[i+1][j-1].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j+1);
              return 1;
            }
            if(i+1<9 && j+1<9 && table[i+1][j+1].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j-1);
              return 1;
            }
            if(i+1<9 && table[i+1][j].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j);
              return 1;
            }
          }
        }
        if(table[i][j].ficha == 'O'){

          if(juega=='n'){
            if(i-1>=0 && i-1>=0 && table[i-1][j-1].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j+1);
              return 1;
            }
            if(i-1>=0 && j+1<9 && table[i-1][j+1].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j-1);
              return 1;
            }
            if(i-1>=0 && table[i-1][j].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j);
              return 1;
            }
            if(j-1>=0 && table[i][j-1].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i, 9-j+1);
              return 1;
            }
            if(j+1<9 && table[i][j-1].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i, 9-j-1);
              return 1;
            }
            if(i+1<9 && table[i+1][j].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j);
              return 1;
            }

          }
          else{
            if(i-1>=0 && table[i-1][j].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j);
              return 1;
            }
            if(j-1>=0 && table[i][j-1].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i, 9-j+1);
              return 1;
            }
            if(j+1<9 && table[i][j-1].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i, 9-j-1);
              return 1;
            }
            if(i+1<9 && table[i+1][j].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j);
              return 1;
            }
            if(i+1<9 && j-1>=0 && table[i+1][j-1].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j+1);
              return 1;
            }
            if(i+1<9 && j+1<9 && table[i+1][j+1].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j-1);
              return 1;
            }
          }
        }
        if(table[i][j].ficha == 'C'){

          if(juega=='n'){
            if(i-2>=0 && j+1 <9 && table[i-2][j+1].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i-2, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-2, 9-j-1);
              return 1;
            }
            if(i-2>=0 && j-1 >=0 && table[i-2][j-1].color!='n'){
              come_reemplaza(table[i][j].ficha, i, j, i-2, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-2, 9-j+1);
              return 1;
            }
          }
          else{
            if(i+2<9 && j+1 <9 && table[i+2][j+1].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i+2, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+2, 9-j-1);
              return 1;
            }
            if(i+2<9 && j-1 >=0 && table[i+2][j-1].color!='b'){
              come_reemplaza(table[i][j].ficha, i, j, i+2, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+2, 9-j+1);
              return 1;
            }
          }
        }
        if(table[i][j].ficha == 'L'){

          if(juega=='n'){
            for(k=1;i-k>=0;k++){
              if(table[i-k][j].color!=juega && table[i-k][j].ficha!='-'){
              come_reemplaza(table[i][j].ficha, i, j, i-k, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-k, 9-j);
              return 1;
              }
              if(table[i-k][j].color==juega){
                break;
              }
            }
          }
          else{
            for(k=1;i+k<9;k++){
              if(table[i+k][j].color!=juega && table[i+k][j].ficha!='-'){
              come_reemplaza(table[i][j].ficha, i, j, i+k, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+k, 9-j);
              return 1;
              }
              if(table[i+k][j].color==juega){
                break;
              }
            }
          }
        }
        if(table[i][j].ficha == 'R'){

          if(i-1>=0 && j-1>=0 && table[i-1][j-1].color!=juega){
            come_reemplaza(table[i][j].ficha, i, j, i-1, j-1);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j+1);
            return 1;
          }
          if(i-1>=0 && j+1<9 && table[i-1][j+1].color!=juega){
            come_reemplaza(table[i][j].ficha, i, j, i-1, j+1);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j-1);
            return 1;
          }
          if(i-1>=0 && table[i-1][j].color!=juega){
            come_reemplaza(table[i][j].ficha, i, j, i-1, j);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j);
            return 1;
          }
          if(j-1>=0 && table[i][j-1].color!=juega){
            come_reemplaza(table[i][j].ficha, i, j, i, j-1);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i, 9-j+1);
            return 1;
          }
          if(j+1<9 && table[i][j-1].color!=juega){
            come_reemplaza(table[i][j].ficha, i, j, i, j+1);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i, 9-j-1);
            return 1;
          }
          if(i+1<9 && table[i+1][j].color!=juega){
            come_reemplaza(table[i][j].ficha, i, j, i+1, j);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j);
            return 1;
          }
          if(i+1<9 && j-1>=0 && table[i+1][j-1].color!=juega){
            come_reemplaza(table[i][j].ficha, i, j, i+1, j-1);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j+1);
            return 1;
          }
          if(i+1<9 && j+1<9 && table[i+1][j+1].color!=juega){
            come_reemplaza(table[i][j].ficha, i, j, i+1, j+1);
            printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j-1);
            return 1;
          }
        }
      }
    }
  }
  //si la ficha no puede solo avanza 1
  for(i=0; i<9 ;i++){
    for(j=0; j<9 ;j++){
       if(table[i][j].color == juega){
        //movimientos para cada una de las fichas
        if(table[i][j].ficha == 'A'){
            if(i+1<9 && j+1<9 && table[i+1][j+1].color!=juega){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j-1);
              return 1;
            }
            if(i-1>=0 && j-1>=0 && table[i-1][j-1].color!=juega){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j+1);
              return 1;
            }
            if(i+1<9 && j-1>=0 && table[i+1][j-1].color!=juega){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j+1);
              return 1;
            }
            if(i-1>=0 && j+1<9 && table[i+1][j+1].color!=juega){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j-1);
              return 1;
            }
          }
        if(table[i][j].ficha == 'T'){
            if(i+1<9 && table[i+1][j].color!=juega){
              come_reemplaza(table[i][j].ficha, i, j, i+1, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j);
              return 1;
            }
            if(i-1>=0 && table[i-1][j].color!=juega){
              come_reemplaza(table[i][j].ficha, i, j, i-1, j);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j);
              return 1;
            }
            if(j-1>=0 && table[i][j-1].color!=juega){
              come_reemplaza(table[i][j].ficha, i, j, i, j-1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i, 9-j+1);
              return 1;
            }
            if(j+1<9 && table[i+1][j+1].color!=juega){
              come_reemplaza(table[i][j].ficha, i, j, i, j+1);
              printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i, 9-j-1);
              return 1;
            }
          }
        if(table[i][j].ficha == 'L'){
            if(juega=='n'){
              if(i-1>=0 && table[i-1][j].color!=juega){
                come_reemplaza(table[i][j].ficha, i, j, i-1, j);
                printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i-1, 9-j);
                return 1;
              }
            }
            else{
              if(i+1<9 &&  table[i+1][j].color!=juega){
                come_reemplaza(table[i][j].ficha, i, j, i+1, j);
                printf("\n\t<<<Pc se movio de %c-%d a %c-%d \n", 'a'+i, 9-j,'a'+i+1, 9-j);
                return 1;
              }
            }
          }
      }
    }
  }


  return retorno;
}
