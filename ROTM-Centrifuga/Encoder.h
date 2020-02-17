#include <RotaryEncoder.h>
#include "config.h"


#define pinClick PINENC_SW

#ifdef ENCODER_MAIN
        RotaryEncoder encoder(PINENC_CLOCK, PINENC_DATA);
        int posEncoder = 0;
#else 
        extern  RotaryEncoder encoder;
        extern int posEncoder;
#endif

void setupRotaryEncoder();
int debounce(int pin);
boolean onClick(int pin);
int positivando(int valor, int n);
