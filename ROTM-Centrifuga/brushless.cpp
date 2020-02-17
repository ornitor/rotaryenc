#include <Arduino.h>
#include <Servo.h>
#include "config.h"
#include "display.h"
#include "Encoder.h"

Servo esc;

int pinomotor = PINESC;

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


void loopBrushless()
{

    varia(150);
    delay(10000); // espera o ESC apitar
    pisca(2);
    varia(80);
    delay(10000); // espera o ESC apitar
}



int vel = 0;

boolean onRPM(int vel2, long tempo)
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
      long t0 = millis();
      long corrido = 0;
      while( corrido < UNIDADE_TEMPO_MS*tempo){
            if (onClick(PINENC_SW))
                return false;
            else{
              sprintf(buffer,"%02d:%02d", corrido/60000,1);
              lcd.setCursor(11,1);
              sprintf(buffer,"%02d", corrido/60000);
              lcd.print(buffer);
              lcd.print(":");
              sprintf(buffer,"%02d", (corrido/1000)%60);
              lcd.print(buffer);
            }
            corrido = millis() - t0;
      }
       lcd.setCursor(16-2,1);
       lcd.print("   ");
      return true;
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
  
