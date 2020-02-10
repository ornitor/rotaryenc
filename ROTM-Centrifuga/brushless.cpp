#include <Arduino.h>
#include <Servo.h>
#include "display.h"

Servo esc;

int pinomotor = 9;

#define TROTTLEMIN   750   // 75
#define TROTTLEMAX  2000   //  170

void varia(int vel2);
void pisca(int n);
void testaRPM(int vel, int vel2, long tempo);


void setupBrushless()
{
    esc.attach(pinomotor);
    esc.writeMicroseconds(TROTTLEMAX);
    delay(4000);
    esc.writeMicroseconds(TROTTLEMIN);
    delay(4000);

}


void setupBrushlessOthon()
{
    esc.attach(9);
    esc.write(TROTTLEMAX);
    delay(5000); // espera o ESC apitar
    esc.write(TROTTLEMIN);
    delay(1000); // espera o ESC apitar
}

void loopBrushless()
{

    varia(150);
    delay(10000); // espera o ESC apitar
    pisca(2);
    varia(80);
    delay(10000); // espera o ESC apitar
}



int vel = 0;

void onRPM(int vel2, long tempo)
{
      int deltaT = 15;//30;
      for(; vel<vel2;vel++){
          esc.write(vel);
          delay(deltaT); // 
      }
      for(; vel>vel2;vel--){
          esc.write(vel);
          delay(deltaT); // 
      }
      //lcd.print("..."); 
      delay(1000*tempo);
}

void startGiro(int pvel)
{
          //vel = pvel;
          for(; vel<pvel;vel++){
              esc.write(vel);
              delay(100); // 
          }
          delay(1000);
}

void varia(int vel2)
{

      for(; vel<vel2;vel++){
          esc.write(vel);
          delay(100); // espera o ESC apitar
      }
      for(; vel>vel2;vel--){
          esc.write(vel);
          delay(50); // espera o ESC apitar
      }
}     


void pisca(int n)
{
      for(int i=0; i<n;i++){
              digitalWrite(LED_BUILTIN,HIGH);
              delay(140); 
              digitalWrite(LED_BUILTIN,LOW);
              delay(140); 
              }
}
  
