#include <LiquidCrystal_I2C.h>

#define ENCODER_MAIN
#include "Encoder.h"
#include <Arduino.h>


void setupRotaryEncoder()
{
  // You may have to modify the next 2 lines if using other pins than A2 and A3
 //     PCICR |= (1 << PCIE1);    // This enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
  //    PCMSK1 |= (1 << PCINT10) | (1 << PCINT11);  // This enables the interrupt for pin 2 and 3 of Port C.   a2 Clock A3 data
      PCICR |= (1 << PCIE0);    // This enables Pin Change Interrupt 0 that covers D8 a D13
      PCMSK0 |= (1 << PCINT4) | (1 << PCINT5);  // This enables the interrupt for pin D12 and D13 of Port  ....   12 Clock 13 data
      encoder.setPosition(0); // nao esquecer de parametrizar em RotaryEncoder encoder(12, 13);
      pinMode(pinClick,INPUT_PULLUP);
} 


// The Interrupt Service Routine for Pin Change Interrupt 1
// This routine will only be called on any signal change on A2 and A3: exactly where we need to check.
ISR(PCINT0_vect) 
{
      encoder.tick(); // just call tick() to check the state.
}



int debounce(int pin)
{
  int i;
  if(digitalRead(pin)==HIGH) 
      return 0;
  long timestart = millis();
  for(i=0;digitalRead(pin) == LOW ;i++)delay(1);
  if (i<3) 
      return 0;  // menor que 3 e um ruido no canal errado
  long timeend = millis();
  if(timeend - timestart > 500)
        return 10;
  else
        return 1;
}
