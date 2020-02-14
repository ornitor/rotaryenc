
#include "Encoder.h"
#include "display.h"
#define PROCESSOS_MASTER
#include "processos.h"

#define ST_STANDBY  1
#define ST_PROGRAMING  2
#define ST_CYCLING  3
#define ST_HALTED  4
#define ST_ENDED  5

char *mainMenu[3] = {"Prog ","Ciclo", "Reset"};
char *progMenu[3] = {"Padrao","Custom","Retorna"};
char *haltMenu[2] = {"RESUME","STOP  "};

int gstate = ST_STANDBY;


void menu(char *title, char *itens[], int n);
void setupBrushless();
void onRPM(int vel2, long tempo);

void setup() 
{
      displayInit("Centrifuga BH", "Bom dia!");
      setupBrushless();
      Serial.begin(115200);
      delay(200);
      Serial.println("\r\n\r\nCentrifuga BH");
      Serial.println("Bom dia!\r\n");
      pinMode(pinClick,INPUT_PULLUP);
      setupRotaryEncoder();
      posEncoder++;
      pinMode(5, OUTPUT);
      pinMode(6, OUTPUT);
      pinMode(7, OUTPUT);
      pinMode(8, OUTPUT);
      delay(2000);
}

void loop()
{
      if(gstate == ST_STANDBY){
          menu("Centrifuga BH", mainMenu , 3);
          if (debounce(pinClick)){
              if( posEncoder%3 == 0)
                    gstate = ST_PROGRAMING;
              if(posEncoder%3 == 1)
                    gstate = ST_CYCLING;
              if(posEncoder%3 == 2)
                    setup();
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
