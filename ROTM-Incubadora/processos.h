void setToDefaults();
void programaEstagios();
void setHalted();
void setEnded();
void setAbortConfirmed();
boolean ciclando();
int PID ( float erro, float erro_1, float integral);

float  satura(float acao, int min, int max);
int choice(char * msg, int position0);
boolean cruzou(float ref, float t1, float t2);
void temperatures() ;

#define DENAT_TEMP  95
#define ANNEAL_TEMP 55
#define ELON_TEMP  75
#define DENAT_TIME  120
#define ANNEAL_TIME 120
#define ELON_TIME  120

#ifdef PROCESSOS_MASTER

int nciclos = 5;
char *stageNames[3] = { "Denat", "Anneal", "Elon" }; // Names of Stages
int tempSettings[3] = { DENAT_TEMP,ANNEAL_TEMP,ELON_TEMP}; // Temperatures of each stage
int timeSettings[3] = { DENAT_TIME,ANNEAL_TIME,ELON_TIME}; // Duration of each stage
int coolSettings[3] = { 1, 0, 0}; // Toggle to enable fan / cooling after stage (only after Denat stage)
int cycleSetting = 0;     // Max number of cycles




// Pins
#define fanPin 5       // The mosfet that drives the 80mm fan is connected to pin 6
#define heatPin 6      // Pin for the mosfet that controls the heating element
#define lidPin 7       // Pin for the mosfet that controls the lid heater
#define BUILTIN_LED 13
int driver[3] = {5,6,9};


// Temperature read
int val;               // Create an integer variable to temporarily store the thermistor read
long tempo;    // Variable to hold the current temperature value
double currentLidTemp; // Variable to hold the current lid temperature value
#define TempPin1 9     // DS18S20 Signal pin on digital 9
#define TempPin2 10    // DS18S20 Signal pin on digital 10

long iteration = 1;


void setToDefaults()
{ 
  Serial.println("Padrao:1 ciclos");
  nciclos = 5;
  tempSettings[0] = DENAT_TEMP;//95;
  timeSettings[0] = DENAT_TIME;
  tempSettings[1] = ANNEAL_TEMP;//55;
  timeSettings[1] = ANNEAL_TIME;
  tempSettings[2] = ELON_TEMP;// 75;
  timeSettings[2] = ELON_TIME;
  lcd.setCursor(0,1);
  lcd.print("Padrao:2 ciclos");
  lcd.print(" ");   
  delay(750);   
}

char msg[17];

void programaEstagios()
{ 
      nciclos = choice("Quantos Ciclos",nciclos);
      for(int i=0;i<3;i++){
             sprintf(msg,"Temp %s",stageNames[i]);
             tempSettings[i] = choice(msg,tempSettings[i]);
             sprintf(msg,"Time %s",stageNames[i]);
             timeSettings[i] = choice(msg,timeSettings[i]);
      }
      lcd.setCursor(0,1);
      lcd.print("Programado, OK!");    
      lcd.print("       ");  
      delay(750);    
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
      iCiclo = 0;
      analogWrite(driver[0],0);
}


int choice(char * msg, int position0)
{
      encoder.setPosition(position0);
      int val = 1;
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

int stage = 0; //0, 2 e 4 e rampa , 1, 3 e 5 é patamar.

boolean ciclando()
{  
     if(iCiclo==0) iCiclo = 1; 
     if(iCiclo <= nciclos ){
        lcd.setCursor(0,0);
        lcd.print ("Ciclo ");  
        lcd.print(iCiclo);  
        lcd.print("/");  
        lcd.print(nciclos);  
        lcd.print(" ");  
        lcd.print(stageNames[stage/2]);  
        temperatures();
        lcd.setCursor(0,1);   
        lcd.print(temp[0]);  
        lcd.print("/");  
        lcd.print((int)setpoint[0]);  
        lcd.print(":");  
        //lcd.print(atua[0]); 
        if( stage > 5 ){
              stage = 0;
              iCiclo++;
        } else if((stage%2 ==0 ) && cruzou(tempSettings[stage/2],temp[0],temp_1[0])){
              tempo = millis();
              stage++;
        } else if ((stage%2 ==0 ) && !cruzou(tempSettings[stage/2],temp[0],temp_1[0])){
              lcd.print("Rampa"); 
        } else if ( stage%2 == 1 && ((millis() - tempo)/1000 < timeSettings[stage/2]) ){
              lcd.print("Patamar"); 
        } else if ( stage%2 == 1 && ((millis() - tempo)/1000 >= timeSettings[stage/2]) ){
              stage++; 
              setpoint[0] = tempSettings[(stage/2)%3];    // para nao entrar com 6 antes de encerrar
        } else {
             lcd.print("??"); 
        }
        temp_1[0] = temp[0];
        return false;
    }
    iCiclo = 0;
    setpoint[0] = 0;
    analogWrite(driver[0],0);
    return true;
}


void temperatures()    /// loop faz muito pouco: reconecta se necessario e chama o loop() do cliente mqtt
{
        LE18B20();
        for(int i=0;i<ntemp && i<4;i++){
              float erro = setpoint[i]-temp[i];
              integral[i] = satura( integral[i] + erro, -0, 12);
              atua[i] = PID(erro, erro_1[i], integral[i]);
              analogWrite(driver[i],atua[i]);
              //if(i==1)analogWrite(BUILTIN_LED,1023-acao);   ///  range do esp8266 e diferente o arduino
              erro_1[i] = erro;
        }
        if(iteration%20==0)
              sendLine();
        delay(10);
        iteration++;
}


int PID ( float erro, float erro_1, float integral)
{
    //return (int) satura( satura(50.*erro - 20*erro_1,-100,100)  + 4*integral , 0, 255);  
    return (int) satura( satura(40.*erro - 20*erro_1,-100,100)  + 6*integral , 0, 255);  // muito bom.. oscilacao pouco amortecida mas amortecida diminuir Ki... aumentar Kb
    return (int) satura( satura(60.*erro - 40*erro_1,-100,100)  + 6*integral , 0, 255);  // pouvo alterou
    return (int) satura( satura(40*erro - 20*erro_1,-100,100)  + 6*integral , 0, 255);  // muito bom.. oscilacao pouco amortecida mas amortecida diminuir Ki... aumentar Kb
}

float  satura(float acao, int min, int max)
{
        if ( acao > max) return max;
        if ( acao < min ) return min;
        return acao;
}


boolean cruzou(float ref, float t1, float t2)
{
    return (ref-t1)*(ref-t2) <= 0;
}

extern int vel;

#endif
