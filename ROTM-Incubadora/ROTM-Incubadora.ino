/*
    Esta sketch:
      le temperaturas 18B20 conectado num barramento
      SOMENTE TEMPERATURAS
      NAO FOI VALIDADO A MULTIPLICAÇAO DOS pids
*/


#include <OneWire.h>
#include <DallasTemperature.h>
#include "sensors-18B20.h"
#include "Encoder.h"
#include "display.h"
#define PROCESSOS_MASTER
#include "processos.h"

#define ST_STANDBY  0
#define ST_MENU  1
#define ST_PROGRAMING  2
#define ST_CYCLING  3
#define ST_HALTED  4
#define ST_ENDED  5


char *mainMenu[3] = {"Prog","Ciclo","Retorna"};
char *progMenu[3] = {"Padrao","Custom", "Retorna"};
char *haltMenu[2] = {"RESUME","STOP  "};

int gstate = ST_STANDBY;
void menu(char *title, char *itens[], int n);

// Hardware
// barramento onewire no D4 ok 
// roxo D5  amarelo D6   verde D7   azul D8


void setup() 
{

      displayInit("Incubadora BH", "Bom dia!");
      Serial.begin(115200);
      delay(200);
      //Serial.println("\r\n\r\nIncubadora BH");
      //Serial.println("Bom dia!\r\n");
      pinMode(pinClick,INPUT_PULLUP);
      setupRotaryEncoder();
      posEncoder++;
      pinMode(BUILTIN_LED, OUTPUT);     // Inicializa pino BUILTIN_LED como output
      pinMode(5, OUTPUT);
      pinMode(6, OUTPUT);
      pinMode(7, OUTPUT);
      pinMode(8, OUTPUT);
      setupTemp18B20();
      gstate = ST_STANDBY;
}




void loop()
{
      if(gstate == ST_STANDBY){
          show("Incubadora BH");
          if (debounce(pinClick)){
              gstate = ST_MENU;                       
          }
      } else if(gstate == ST_MENU){
          menu("Incubadora BH", mainMenu , 3);
          if (debounce(pinClick)){
              if( posEncoder%3 == 0)
                    gstate = ST_PROGRAMING;
              if(posEncoder%3 == 1){
                    gstate = ST_CYCLING;
                    iCiclo = 0;
                    setpoint[0] = tempSettings[0];
              }
             if(posEncoder%3 == 2)
                    gstate = ST_STANDBY;
              posEncoder++;                 
          }
      } else if (gstate == ST_PROGRAMING){
          menu("Programando", progMenu, 3 );
          if (debounce(pinClick)){
              if(posEncoder%3 == 0)
                    setToDefaults();
              if( posEncoder%3 == 1)
                    programaEstagios(); 
              if( posEncoder%3 == 2)
                    ;  // NOP
             gstate = ST_STANDBY;               
             posEncoder++;
         }
      } else if (gstate == ST_CYCLING){ 
          // nao tem menu, inputs fim do processo ou click
          if(iCiclo == 0 ) lcd.clear();
          if ( ciclando()){   // retorna true quando terminar a ciclagem
              gstate = ST_ENDED;  
              setEnded();
          }
          else if (debounce(pinClick)){
              gstate = ST_HALTED;  
              setHalted();
          }
         posEncoder++;
      }else if (gstate == ST_HALTED){
          menu("Tem certeza?", haltMenu,2 );
          if (debounce(pinClick)){
              if(posEncoder%2 == 0)
                    gstate = ST_CYCLING;
              if(posEncoder%2 == 1){
                    gstate = ST_ENDED;
                    setAbortConfirmed();
              }
              posEncoder++;
          }
      } else if (gstate == ST_ENDED){ 
         // nao tem menu, input é o click
          if (debounce(pinClick)){
              gstate = ST_STANDBY;
              posEncoder++;                
          }
      } 
 
}
