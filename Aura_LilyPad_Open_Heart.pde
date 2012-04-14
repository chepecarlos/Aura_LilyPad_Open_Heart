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
 - 15
 - 16
 - 17
 - 18
 - 19
*/ 

#include <EEPROM.h>

int TotalLed = 19;//Cantidad de LED
char Pin[19] = {A5,A4,A3,A2,A1,A0,12,13,11,10,9,8,7,6,5,4,3,2,1};//Posiciones de led
char nivel[19];
int Aura = 7;

void setup() {
  
  pinMode(0,INPUT);
  digitalWrite(0,HIGH);
  
  for(int Led = 0; Led < TotalLed; Led++)
    pinMode(Pin[Led],OUTPUT);
    
}//Funcion de inicializacion de variables

void loop() {
  
}//Funcion que se repitira en el sistema

void Limpiar(){
  for(int Led = 0; Led < TotalLed; Led++)
    nivel[Led] = 0;
    
}
