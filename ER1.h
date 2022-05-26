#include <16F877A.h>
//#device *=16
//#device adc=8
//#fuses DEBUG,XT,NOPROTECT,NOWDT,NOLVP,NOPUT,NOBROWNOUT,NOCPD,NOWRT
#fuses NODEBUG,XT,NOPROTECT,NOWDT,NOLVP,PUT,NOBROWNOUT,NOCPD,NOWRT
#use delay(clock=2000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=9)
//#use fast_io(A)

//declaração de variáveis globais
char			TEXTO [17] ;
float			FLOAT_CONTADOR_DE_PULSO ;
float			FLOAT_ANGULO ;
float			FLOAT_VOLTAS ;
char			CHAR_VALVULA_SENTIDO ;
char			CHAR_VALVULA_ABRINDO ;
float			FLOAT_ANGULO_POR_PASSO ;
int				INT_TEMP ;
int 			INT_TAMANHO ;
int16			INT16_CONTADOR ;
float			FLOAT_VOLTASINTEIRAS ;
BOOLEAN			BOOLEAN_ESCREVEU_LCD ;

//declaração de DEFINES globais
#define			DEF_PINO_SENSOR_FIO_A		PIN_A0
#define			DEF_PINO_SENSOR_FIO_AB		PIN_A2
#define			DEF_PINO_SENSOR_FIO_B		PIN_A1
#define			DEF_PINO_SENSOR_FIO_BB		PIN_A3
#define			DEF_VALVULA_ABRINDO			'A'
#define			DEF_VALVULA_FECHANDO		'F'
#define			DEF_VALVULA_HORARIO			'H'
#define			DEF_VALVULA_ANTIHORARIO		'A'

//estruturas
struct STRUCT_CONDICAO_SENSOR
{
	int		nA 	: 1 ;
	int		nB 	: 1 ;
	int		nAb	: 1 ;
	int		nBb	: 1 ;
	int		vA 	: 1 ;
	int		vB 	: 1 ;
	int		vAb	: 1 ;
	int		vBb	: 1 ;
} ST_SENSOR ;
