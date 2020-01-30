#include <RotaryEncoder.h>

#ifdef ENCODER_MAIN
        RotaryEncoder encoder(A2, A3);
        int posEncoder = 0;
#else 
        extern  RotaryEncoder encoder;
        extern int posEncoder;
#endif

void setupRotaryEncoder();
int debounce(int pin);
int positivando(int valor, int n);
