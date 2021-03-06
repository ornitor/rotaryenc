// PARAMETROS DE CICLO DEFAULT
#define NCICLOS 5;
#define TEMP_CI 10;
#define TEMP_CII 10;
#define VEL_CI 3000;
#define VEL_CII 100;
#define UNIDADE_TEMPO_MS 60000


//  Pinos I2C
#define I2C_SDA  A4
#define I2C_SCL  A5
// Pino do ESC para o MOTOR
#define PINESC 9
// Pinos do Rotary Encoder
#define PINENC_SW 3
// Comente linha abaixo se desejar utlizar digital Pins 12 e 13 INT 0  ( Default A2 A3 INT1)
//#define ANALOGPINS
#ifdef ANALOGPINS    // funçao da configuração do hardware
#define PINENC_CLOCK  A2
#define PINENC_DATA A3
#else
#define PINENC_CLOCK  12
#define PINENC_DATA 13
#endif

  
