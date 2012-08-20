/*
 Los estados del sitemas son 
 -  0 Programador
 -  1 Super PWM
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
int Frecuencia = 1;

void setup() {

  pinMode(0,INPUT);
  digitalWrite(0,HIGH);

  for(int Led = 0; Led < TotalLed; Led++)
    pinMode(Pin[Led],OUTPUT);

  Limpiar();

}//Funcion de inicializacion de variables

void loop() {
  switch( EEPROM.read(Aura)){
  case 1:
    E1_SuperPWM();
    break;
  case 15:  
    E15_DiscoDisco();
    break;
  default:
    EEPROM.write(Aura,1);
    return;
    break;
  }
  Leer();
}//Funcion que se repitira en el sistema

void Limpiar(){
  for(int Led = 0; Led < TotalLed; Led++)
    nivel[Led] = 0;
  Frecuencia = 1;
}//Funcion que pone todos los led apagados

void Actualizar(){
  for(int t = 0; t < 10*Frecuencia; t++){
    for(int Led = 0; Led < TotalLed; Led++){
      if(nivel[Led]*Frecuencia <=  t)
        digitalWrite(Pin[Led], LOW);
      else
        digitalWrite(Pin[Led], HIGH);     
    }
    delay(1);
  }
}//Enciende los led dependidendo del nivel que estes

void Leer(){
  Limpiar();
  Actualizar();
  int cont = 0;
  float t0 = millis();
  float t1 = t0;
  int BPasado = 0;
  int BPresente = 0;
  do{
    if( t1 == t0){
      for( int Led = 0; Led < TotalLed; Led++){
        nivel[Led] = ( Led + 1 <= EEPROM.read(Aura)) ? 10 : 0;
      } 
    }

    t1 = millis();
    BPresente = digitalRead(0);

    if(BPresente > BPasado){
      EEPROM.write(Aura, EEPROM.read(Aura) + 1);
      cont = 0;
      if( EEPROM.read(Aura) > TotalLed){
        EEPROM.write(Aura, 1);
      }
      t0 = t1;  
    }

    BPasado = BPresente; 

    Actualizar();
    if( (t1 - t0) >= 1000){
      t0 = t1;
      cont++;
      Limpiar();
      for( int i = 0; i<20;i++){
        Actualizar();
      }
    }

  }
  while( cont <= 3);
}

void E1_SuperPWM(){
  int LedNivel = 0;
  int v = -1;
  float t0 = millis();
  float t1 = t0;
  Limpiar();
  do{
    t1 = millis();

    if( t1 - t0 >= 200){
      t0 = millis();
      for(int Led = 0; Led < TotalLed; Led++){
        nivel[Led] = LedNivel;
      }

      if( LedNivel == -1 || LedNivel == 12)
        v = -v;
      LedNivel = LedNivel + v;  
    }
    Actualizar();
  }
  while(digitalRead(0) == 1);
}//El primer esta un pwm de todos los LED

void E15_DiscoDisco(){
  Limpiar();
  Frecuencia = 10;
  for(int Led = 0; Led < TotalLed; Led++){
    nivel[Led] = 6;
  }
  do{
    Actualizar();
  }
  while(digitalRead(0) == 1);
}//El primer esta un pwm de todos los LED


