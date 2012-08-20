/*
 Los estados del sitemas son 
 -  0 
 -  1
 -  2
 -  3
 -  4
 -  5
 -  6
 -  7
 -  8
 -  9
 - 10
 - 11
 - 12
 - 13
 - 14
 - 15 Disco Disco
 - 16
 - 17
 - 18
 - 19
 */

#include <EEPROM.h>

int TotalLed = 19;//Cantidad de LED
char Pin[19] = {
  A5,A4,A3,A2,A1,A0,12,13,11,10,9,8,7,6,5,4,3,2,1};//Posiciones de led
char nivel[19];
int Aura = 7;

void setup() {

  pinMode(0,INPUT);
  digitalWrite(0,HIGH);

  for(int Led = 0; Led < TotalLed; Led++)
    pinMode(Pin[Led],OUTPUT);

  Limpiar();

  }//Funcion de inicializacion de variables

  void loop() {
    E15_SuperPWM();
  }//Funcion que se repitira en el sistema

void Limpiar(){
  for(int Led = 0; Led < TotalLed; Led++)
    nivel[Led] = 0;
}//Funcion que pone todos los led apagados

void Actualizar(){
 // nivel[0]=20;
  for(int t = 0; t < 100; t++){
    for(int Led = 0; Led < TotalLed; Led++){
      if(nivel[Led] <=  t)
        digitalWrite(Pin[Led], LOW);
      else
        digitalWrite(Pin[Led], HIGH);
     /* if( t % 2 == 0){
      digitalWrite(Pin[Led], LOW);  
      }*/
      
    }
    delay(1);
  }
}//Enciende los led dependidendo del nivel que estes

void E15_SuperPWM(){
  int j = 0;
  int v = -1;
  int i;
  float t0 = millis();
  float t1 = t0;
  Limpiar();
  do{
    t1 = millis();

    if( t1 - t0 >= 200){
      t0 = millis();
      for(i = 0; i < TotalLed; i++){
        nivel[i] = j;
      }

      if( j == -1 || j == 102)//102
        v = -v;
      j = j + v;  
    }

    Actualizar();

  }
  while(digitalRead(0) == 1);
}//El primer esta un pwm de todos los LED

