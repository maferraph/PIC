#include "C:\Codigos\PICs\ER1b\ER1b.h"


void main()
{

   setup_counters(RTCC_INTERNAL,RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

}
