void setToDefaults();
void programaEstagios();
void setHalted();
void setEnded();
void setAbortConfirmed();
boolean ciclando();
int choice(char * msg, int position0);
void testaRPM(int vel, int vel2, long tempo);
void startGiro(int pvel);

#ifdef PROCESSOS_MASTER

int nciclos = 1;
int tempoH = 10;
int velH = 150;
int velL = 140;
int tempoL = 3;

void onRPM(int vel2, long tempo);

void setToDefaults(){ 
  Serial.println("default: 3:10x3");  
  nciclos = 1;
  tempoH = 10;
  tempoL = 3;  
  int velH = 150;
  int velL = 140;      
  lcd.setCursor(0,1);
  lcd.print("default: 1x10:3");      
  lcd.print(" ");   
  delay(750);   
}

void programaEstagios()
{ 
      nciclos = choice("Quantos Ciclos",nciclos);
      velH = choice("Veloc. rapida",velH );
      tempoH = choice("Tempo rapido",tempoH);
      velL = choice("Velocidade lenta",velL);
      tempoL = choice("Tempo lento",tempoL);
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
      onRPM(69,0);
      iCiclo = 0;
}


int choice(char * msg, int position0)
{
      encoder.setPosition(position0);
      int val = 1;
      lcd.clear(); lcd.print(msg);
      lcd.setCursor(0,1); lcd.print(val);
      
      while(!debounce(4)) 
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

boolean ciclando()
{
     if(iCiclo==0){
         lcd.clear();  lcd.print ("Partindo ");  
         startGiro(150);
     }        
     if(iCiclo++ < nciclos ){
        lcd.clear();  lcd.print ("Ciclo ");  
        lcd.print(iCiclo);  
        lcd.print("/");  
        lcd.print(nciclos);  
        lcd.setCursor(0,1);   
        lcd.print(velH);  
        lcd.print("x");  
        lcd.print(tempoH);  
        lcd.print(" ");  
        onRPM(velH,tempoH);
        lcd.print(velL);  
        lcd.print("x");  
        lcd.print(tempoL);  
        onRPM(velL,tempoL);
        lcd.clear();  
        return false;
    }
    onRPM(69,0);
    iCiclo = 0;
    return true;
}

extern int vel;




#endif
