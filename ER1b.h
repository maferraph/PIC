#include <16F628.h>
#device *=16
#use delay(clock=20000000)
#fuses NOWDT,INTRC_IO, PUT, NOPROTECT, MCLR
#use rs232(baud=9600,parity=N,xmit=PIN_A3,rcv=PIN_A2,bits=9)

