#include <Wire.h> 
#include "Encoder.h"
#include "LiquidCrystal_I2C.h" // Needed for operating the LCD screen
#include "Arduino.h"
#include <math.h>   // loads a library with more advanced math functions
#include "sensors-18B20.h"
#include "xchar.h"


#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)
 
/* Useful Macros for getting elapsed time */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)  
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)  

LiquidCrystal_I2C lcd(0x3F,16,2);

String printDigits2(int digits){
  // utility function for digital clock display: prints colon and leading 0
  String returnval = "";
  if(digits < 10)
    returnval += "0";
  returnval += digits;          
  return returnval; 
}


String time2(int val){  
  // calculate number of days, hours, minutes and seconds
  int days = elapsedDays(val);
  int hours = numberOfHours(val);
  int minutes = numberOfMinutes(val);
  int seconds = numberOfSeconds(val);
            
  String returnval = "";
            
  // digital clock display of current time 
  returnval = printDigits2(minutes) + ":" + printDigits2(seconds) + "   ";
  
  // return value      
  return returnval;
}



void displayInit(char *title1, char *title2)
{
        lcd.init();
        lcd.backlight();
        charsetFour(lcd);  // escolhe o set de ecarateres a expandir
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(title1);
        lcd.setCursor(0,1);
        lcd.print(title2);
        delay(1000);
        lcd.clear();
  
}

void displayInt(int linha, char *label, int valor)
{
        lcd.setCursor(0,linha); // Display the settings on the LCD
        lcd.print(label);
        lcd.setCursor(strlen(label)+2,linha);
        lcd.print(valor);
        lcd.print("  ");
}

void displayTime(int linha, char *label, int valor)
{
        lcd.setCursor(0,linha); // Display the settings on the LCD
        lcd.print(label);
        lcd.setCursor(strlen(label)+2,linha);
        lcd.print(time2(valor));
        lcd.print("  ");
}

void show(char *title )
{
        lcd.setCursor(0,0);
        lcd.print(title);
        lcd.print("     ");
        lcd.setCursor(0,1);
        LE18B20();
        lcd.print(THERMOMETER); lcd.print(temp[0]); lcd.print(DEGREE);  lcd.print("C ");lcd.print(CLOCK); lcd.print(BEDTEMP);lcd.print(UPLEVEL);lcd.print(REFRESH);lcd.print(FOLDER);lcd.print(FEEDRATE); 

}
/*
  lcd.createChar(DEGREE, degree);
  lcd.createChar(BEDTEMP,bedTemp);
  lcd.createChar(THERMOMETER, thermometer);
  lcd.createChar(UPLEVEL, uplevel);
  lcd.createChar(REFRESH, refresh);
  lcd.createChar(FOLDER, folder);
  lcd.createChar(FEEDRATE, feedrate);
  lcd.createChar(CLOCK, xclock);*/

void menu(char *title, char *itens[], int n)
{
        if(posEncoder == encoder.getPosition()) 
                return;
        posEncoder = positivando(encoder.getPosition(), n);
        encoder.setPosition(posEncoder);
        int selected = posEncoder%n;
        lcd.setCursor(0,0);
        lcd.print(title);
        lcd.print("     ");
        lcd.setCursor(0,1);

        for(int i=0; i<3;i++){
            if(i==0){
                  lcd.print("[");
                  lcd.print(itens[(selected+i)%n]);
                  lcd.print("]");
            } else {
                  lcd.print(" ");
                  lcd.print(itens[(selected+i)%n]);
                  lcd.print(" ");
           }
        }  
        lcd.print("  ");   
}

void menu2(char *title, char *itens[], int n)
{
        if(posEncoder == encoder.getPosition()) 
                return;
        posEncoder = positivando(encoder.getPosition(), n);
        encoder.setPosition(posEncoder);
        int selected = posEncoder%n;
        Serial.println(title);
        lcd.setCursor(0,0);
        lcd.print(title);
        lcd.print("     ");
        lcd.setCursor(0,1);

        for(int i=0; i<n;i++){
            if(selected == i)
                  lcd.print("[");
            else
                  lcd.print(" ");
            lcd.print(itens[i]);
            if(selected == i)
                  lcd.print("]");
            else 
                  lcd.print(" ");
        }  
        lcd.print("  ");   
}

void menu3(char *title, char *itens[], int n)
{
        if(posEncoder == encoder.getPosition()) 
                return;
        posEncoder = positivando(encoder.getPosition(), n);
        encoder.setPosition(posEncoder);
        int selected = posEncoder%n;
        Serial.println(title);
        for(int i=0; i<n;i++){
            if(selected == i)
                  Serial.print("[");
            else
                  Serial.print(" ");
            Serial.print(itens[i]);
            if(selected == i)
                  Serial.print("]");
            else 
                  Serial.print(" ");
        }  
        Serial.println("");   
}


int positivando(int valor, int n)
{
      while(valor < 0)
          valor += n;
      return valor;
}
