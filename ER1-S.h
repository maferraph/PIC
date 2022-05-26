#include <16F628.h>
#device *=16
#fuses INTRC_IO , NOPROTECT , NOWDT , NOLVP , PUT , NOBROWNOUT , NOCPD
#use delay( clock=4000000 )
#use rs232( baud=256000 , parity=O , xmit=PIN_B2 , rcv=PIN_B1 , bits=8 , STREAM = PORTA_SERIAL )

//declaração de variáveis globais
char			TEXTO [17] ;
char			TEXTO_USART [20] ;
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

//declaração de DEFINES globais
#define			DEF_PINO_SENSOR_FIO_A		PIN_B4
#define			DEF_PINO_SENSOR_FIO_AB		PIN_B3
#define			DEF_PINO_SENSOR_FIO_B		PIN_B5
#define			DEF_PINO_SENSOR_FIO_BB		PIN_B0
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
