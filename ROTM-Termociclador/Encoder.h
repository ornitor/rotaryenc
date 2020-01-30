#include <RotaryEncoder.h>
#include <Arduino.h>

#define pinClick 0

#ifdef ENCODER_MAIN
        RotaryEncoder encoder(12, 13);
        int posEncoder = 0;
        
#else 
        extern  RotaryEncoder encoder;
        extern int posEncoder;
#endif

void setupRotaryEncoder();
int debounce(int pin);
int positivando(int valor, int n);
