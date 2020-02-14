#include <Arduino.h>
#include <Servo.h>
#include "display.h"

Servo esc;

int throttlePin = 0;

#define TROTTLEMIN   75
#define TROTTLEMAX  170

void varia(int vel2);
void pisca(int n);
void testaRPM(int vel, int vel2, long tempo);


void setupBrushless()
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



int vel = TROTTLEMIN;

void onRPM(int vel2, long tempo)
{
      int deltaT = 30;
      if (vel <= TROTTLEMIN){
          deltaT = 150;
      }
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
void testaRPM(int vel1, int vel2, long tempo)
{
      int deltaT = 1000*tempo;
      vel = TROTTLEMIN;
      for(vel=vel1; vel<vel2;vel++){
          Serial.print(vel); 
          esc.write(vel);
          delay(deltaT); // espera o ESC apitar
          Serial.print(" ... "); 
          esc.write(70);
          //delay(deltaT); // espera o ESC apitar
      }

 //     Serial.println("..."); 
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
              delay(140); // espera o ESC apitar
              digitalWrite(LED_BUILTIN,LOW);
              delay(140); // espera o ESC apitar
              }
            
}
  
