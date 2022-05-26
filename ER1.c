#include "C:\Codigos\PICs\ER1\ER1.h"
#include <LCD.C>
  #include <float.h>
  #include <math.h>
  #include <stdio.h>
  #include <string.h>
#int_RTCC
RTCC_isr() 
{

}

#int_TBE
TBE_isr() 
{

}

#int_RDA
RDA_isr() 
{

}

#int_PSP
PSP_isr() 
{

}



void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_ENABLED);
   setup_spi(FALSE);
   setup_counters(RTCC_INTERNAL,RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   lcd_init();
   enable_interrupts(INT_RTCC);
   enable_interrupts(INT_TBE);
   enable_interrupts(INT_RDA);
   enable_interrupts(INT_PSP);
   enable_interrupts(global);

}
