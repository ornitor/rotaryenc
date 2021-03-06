
#include "LiquidCrystal_I2C.h" // Needed for operating the LCD screen
#include "Arduino.h"
#include <math.h>   // loads a library with more advanced math functions
#include "xchar.h"


extern LiquidCrystal_I2C lcd;

String time2(int val);
void displayInit(char *title1, char *title2);
void displayTime(int linha, char *label, int valor);
void menu(char *title, char *itens[], int n);
int positivando(int valor, int n);

void show(char *title );
