#include <16F819.h>
#device adc=8

#FUSES INTRC_IO                 //Internal RC Osc, no CLKOUT
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage programing
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES PROTECT                  //Code not protected from reading

#DEFINE  PORTA 0x05
#DEFINE  PORTB 0x06
#DEFINE  STATUS 0x03
#DEFINE  RP0   5
#DEFINE  TRISA   0x85
#DEFINE  TRISB   0x86

#define  CR 0x0D
#define  LF 0x0A