#include <16F628.h>
//#device *=16
//#device adc=8
//#fuses DEBUG,XT,NOPROTECT,NOWDT,NOLVP,NOPUT,NOBROWNOUT,NOCPD,NOWRT
#fuses INTRC_IO,NOPROTECT,NOWDT,NOLVP,PUT,NOBROWNOUT,NOCPD
#use delay(clock=4000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_A0,rcv=PIN_A1,bits=9)
//#use fast_io(A)

//declaração de variáveis globais
char			TEXTO [17] ;
int				INT_TEMP ;
int 			INT_TAMANHO ;

