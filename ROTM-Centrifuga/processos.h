#include "config.h"

void setToDefaults();
void programaEstagios();
void setHalted();
void setEnded();
void setAbortConfirmed();
boolean ciclando();
int choice(char * msg, int position0);
int choice(char * msg, int position0, int delta, int minimo, int maximo);
void testaRPM(int vel, int vel2, long tempo);
void startGiro(int pvel);
boolean onRPM(int vel2, long tempo);
float g2Rpm(float ng);

#ifdef PROCESSOS_MASTER

extern int vel;

int nciclos = NCICLOS;
int tempoH = TEMP_CI;
int velH = VEL_CI;
int velL = VEL_CII;
int tempoL = TEMP_CII;



void setToDefaults(){ 
  nciclos = NCICLOS;
  tempoH = TEMP_CI;
  tempoL = TEMP_CII;  
  velH = VEL_CI;
  velL = VEL_CII;      
  }

void programaEstagios()
{ 
      nciclos = choice("Quantos Ciclos",nciclos);
      velH = choice("Fase I(em g)",velH ,100,1,30);
      tempoH = choice("Tempo I(em min)",tempoH);
      velL = choice("Fase II(em g)",velL,100,1,30);
      tempoL = choice("Tempo II(em min)",tempoL);
      lcd.setCursor(0,1);
      lcd.print("Programado, OK!");    
      lcd.print("       ");  
      delay(750);    
}

void testaMotor()
{ 
      testaRPM(117, 118, 10);
 
}

void setHalted(){
    Serial.println("Halted");      
      lcd.setCursor(0,1);
      lcd.print("Halted!");    
      lcd.print("         ");      
}

void setEnded()
{
      lcd.clear();
      lcd.print("Terminado");    
      lcd.print("         ");       
      lcd.setCursor(0,1);
      lcd.print("Clique para sair");    
      lcd.print(" ");       
      lcd.print("         ");       
}

int iCiclo = 0;

void setAbortConfirmed()
{
      lcd.setCursor(0,0);
      lcd.print("Interrompido");    
      lcd.print("         ");       
      lcd.setCursor(0,1);
      lcd.print("Clique para sair");    
      lcd.print(" ");       
      Serial.println("Interrompido");
      onRPM(0,0);
      iCiclo = 0;
}


int choice(char * msg, int position0)
{
      encoder.setPosition(position0);
      int val = encoder.getPosition();
      lcd.clear(); lcd.print(msg);
      lcd.setCursor(0,1); lcd.print(val);
      
      while(!debounce(pinClick)) 
            if(val != encoder.getPosition()){
                  val = encoder.getPosition();
                  if (val <= 0 ){
                      val = 1;
                      encoder.setPosition(val);
                  }
                  lcd.setCursor(0,1); lcd.print(val);lcd.print("         ");
            }
      return encoder.getPosition();
}

int choice(char * msg, int position0, int delta, int minimo, int maximo)
{
      encoder.setPosition(position0/delta);
      int val = encoder.getPosition();
      lcd.clear(); lcd.print(msg);
      lcd.setCursor(0,1); lcd.print(val*delta);   
      while(!debounce(pinClick)) 
            if(val != encoder.getPosition()){
                  val = encoder.getPosition();
                  if (val < minimo ){
                      val = minimo;
                      encoder.setPosition(val);
                  }
                 if (val > maximo ){
                      val = maximo;
                      encoder.setPosition(val);
                  }
                  lcd.setCursor(0,1); lcd.print(val*delta);lcd.print("         ");
            }
      return encoder.getPosition()*delta;
}

boolean ciclando()
{
     if(iCiclo==0&&false){
         lcd.clear();  lcd.print ("Partindo ");  
         startGiro(150);
     }        
     if(iCiclo++ < nciclos ){
        lcd.clear();  lcd.print ("Ciclo ");  
        lcd.print(iCiclo);  
        lcd.print("/");  
        lcd.print(nciclos);  
        lcd.setCursor(0,1);   
        lcd.print("1 ");  
        lcd.print(velH);  
        lcd.print("x");  
        lcd.print(tempoH);  
        lcd.print(" ");  
        if(!onRPM(g2Rpm(velH),tempoH))
            return false;
        lcd.setCursor(0,1);   
        lcd.print("2 ");  
        lcd.print(velL);  
        lcd.print("x");  
        lcd.print(tempoL);  
        lcd.print(" ");  
        onRPM(g2Rpm(velL),tempoL);
        return false;
    }
    onRPM(0,0);
    iCiclo = 0;
    return true;
}

float g2Rpm(float ng)
{
#define R 50.
      float a = (120.-30.)/(7143. - 1188.);
      float b = 30 - a*1188;
      float f = sqrt(ng/(1.1178620909604E-06*R));
      return a*f + b;

}



#endif
