#include "C:\Codigos\PICs\ER1-S\ER1-S.h"
#include <string.h>

//PROTÓTIPOS DE FUNÇÕES
void varredura_sensor_aux_horario() ;
void varredura_sensor_aux_antihorario() ;
void atualiza_valores_velhos_sensor() ;
void zera_contagem_pulsos() ;
void envia_dados_porta_serial() ;

//função principal
void main()
{
	//********* CONFIGURAÇÃO DO PIC **********
    enable_interrupts( INT_RB ) ;
    enable_interrupts( INT_RDA ) ;
	disable_interrupts( INT_RTCC | INT_EXT | INT_TBE | INT_TIMER0 | INT_TIMER1 | INT_TIMER2 | INT_CCP1 | INT_LCD | INT_COMP | INT_EEPROM ) ;
    enable_interrupts( GLOBAL ) ;
    setup_vref( FALSE ) ;
    setup_comparator( NC_NC_NC_NC ) ;
	setup_ccp1( CCP_OFF ) ;
    setup_timer_1(T1_DISABLED) ;
    setup_timer_2(T2_DISABLED,0,1) ;
	// configuração da direção de E/S dados das portas (0=saida e 1=entrada)
//	set_tris_b( 0b00000000 ) ; // pinos B definidos como saída
	zera_contagem_pulsos() ;
	while ( TRUE ) ;
}

//DEMAIS FUNÇÕES
void varredura_sensor_aux_horario()
{
//	if( CHAR_VALVULA_SENTIDO == DEF_VALVULA_ANTIHORARIO ) FLOAT_CONTADOR_DE_PULSO = 0 ;
	CHAR_VALVULA_SENTIDO = DEF_VALVULA_HORARIO ;
	CHAR_VALVULA_ABRINDO = DEF_VALVULA_ABRINDO ;
	FLOAT_CONTADOR_DE_PULSO += 1 ; // o encoder tem 1024 pulsos por volta
	if( FLOAT_CONTADOR_DE_PULSO == 1025 ) 
	{
		FLOAT_VOLTASINTEIRAS += 1 ;
		FLOAT_CONTADOR_DE_PULSO = 0 ;
	}
	//calcula novas posicoes
	FLOAT_ANGULO = FLOAT_CONTADOR_DE_PULSO * FLOAT_ANGULO_POR_PASSO ;
	FLOAT_VOLTAS = FLOAT_VOLTASINTEIRAS + ( FLOAT_ANGULO / 360 ) ;
	atualiza_valores_velhos_sensor() ;
}

void varredura_sensor_aux_antihorario()
{
//	if( CHAR_VALVULA_SENTIDO == DEF_VALVULA_HORARIO ) FLOAT_CONTADOR_DE_PULSO = 0 ;
	CHAR_VALVULA_SENTIDO = DEF_VALVULA_ANTIHORARIO ;
	CHAR_VALVULA_ABRINDO = DEF_VALVULA_FECHANDO ;
	FLOAT_CONTADOR_DE_PULSO -= 1 ;
	if( FLOAT_CONTADOR_DE_PULSO == -1025 ) // o encoder tem 1024 pulsos por volta
	{
		FLOAT_VOLTASINTEIRAS -= 1 ;
		FLOAT_CONTADOR_DE_PULSO = 0 ;
	}
	//calcula novas posicoes
	FLOAT_ANGULO = FLOAT_CONTADOR_DE_PULSO * FLOAT_ANGULO_POR_PASSO ;
	FLOAT_VOLTAS = FLOAT_VOLTASINTEIRAS + ( FLOAT_ANGULO / 360 ) ;
	atualiza_valores_velhos_sensor() ;
}

void zera_contagem_pulsos()
{
	ST_SENSOR.nA = input( DEF_PINO_SENSOR_FIO_A ) ;
	ST_SENSOR.nB = input( DEF_PINO_SENSOR_FIO_B ) ;
	ST_SENSOR.nAb = input( DEF_PINO_SENSOR_FIO_Ab ) ;
	ST_SENSOR.nBb = input( DEF_PINO_SENSOR_FIO_Bb ) ;
	atualiza_valores_velhos_sensor() ;
	FLOAT_CONTADOR_DE_PULSO = 0 ;
	FLOAT_ANGULO = 0 ;
	FLOAT_VOLTAS = 0 ;
	FLOAT_ANGULO_POR_PASSO = 0.3515625 ;
	FLOAT_VOLTASINTEIRAS = 0 ;
	CHAR_VALVULA_SENTIDO = '-' ;
	CHAR_VALVULA_ABRINDO = '-' ;
	INT16_CONTADOR = 0 ;
}

void atualiza_valores_velhos_sensor()
{
	//atualiza os valores velhos
	ST_SENSOR.vA = ST_SENSOR.nA ;
	ST_SENSOR.vB = ST_SENSOR.nB ;
	ST_SENSOR.vAb = ST_SENSOR.nAb ;
	ST_SENSOR.vBb = ST_SENSOR.nBb ;
}

void envia_dados_porta_serial()
{
	//"Graus   Volta SV"
	//"360.000 10.01 HA"
	//display com 1 digito
/*	if( FLOAT_ANGULO < 10 || FLOAT_ANGULO >= 0 )
	{
		sprintf( TEXTO , "%01.3f   %01.2f  %C%C" , FLOAT_ANGULO , FLOAT_VOLTAS , CHAR_VALVULA_SENTIDO , CHAR_VALVULA_ABRINDO ) ;
	}
	//display com 2 digito
	else if( ( FLOAT_ANGULO < 100 && FLOAT_ANGULO >= 10 ) || ( FLOAT_ANGULO > -9 && FLOAT_ANGULO < 0 ) )
	{
		sprintf( TEXTO , "%02.3f %02.2f %C%C" , FLOAT_ANGULO , FLOAT_VOLTAS , CHAR_VALVULA_SENTIDO , CHAR_VALVULA_ABRINDO ) ;
	}
	//display com 3 digito
	else if( FLOAT_ANGULO > 100 || FLOAT_ANGULO < -100 )
	{
		sprintf( TEXTO , "%03.3f %02.2f %C%C" , FLOAT_ANGULO , FLOAT_VOLTAS , CHAR_VALVULA_SENTIDO , CHAR_VALVULA_ABRINDO ) ;
	}
*/
	sprintf( TEXTO , "%02.3f %02.2f %C%C" , FLOAT_ANGULO , FLOAT_VOLTAS , CHAR_VALVULA_SENTIDO , CHAR_VALVULA_ABRINDO ) ;
	//envia dados para a porta serial
	puts( TEXTO ) ;
}

// TRATA INTERRUPÇÕES
#int_RB //quando RB4-RB7 tem alguma alteração
void interrupcao_RB() 
{
	ST_SENSOR.nA = input( DEF_PINO_SENSOR_FIO_A ) ;
	ST_SENSOR.nB = input( DEF_PINO_SENSOR_FIO_B ) ;
	ST_SENSOR.nAb = input( DEF_PINO_SENSOR_FIO_Ab ) ;
	ST_SENSOR.nBb = input( DEF_PINO_SENSOR_FIO_Bb ) ;
	/* pega valores dos pulsos do sensor, verifica se mudou o pulso do sensor, ou seja, teve movimento
       O encoder rotativo funciona da seguinte forma, temos 4 cabos com sinais A, B, Ainv e Binv, na seguinte ordem:
 	       A    B   Ainv Binv	
	   1)  1    0   0    1		
	   2)  1    1   0    0		
	   3)  0    1   1    0		
	   4)  0    0   1    1		
	   Se a sequência de pulsos for de 1 até 4, sentido horário, caso contrário, sentido antihorário. 
	   O encoder já começa marcando pulso, nunca todos os fios em zero.
       Sentido horário será positivo e antihorário será negativo
	*/
	if( ST_SENSOR.nA == 1 && ST_SENSOR.nB == 0 && ST_SENSOR.nAb == 0 && ST_SENSOR.nBb == 1 ) 
	{
		if( ST_SENSOR.vA == 0 && ST_SENSOR.vB == 0 && ST_SENSOR.vAb == 1 && ST_SENSOR.vBb == 1 ) varredura_sensor_aux_antihorario() ; 
		else if( ST_SENSOR.vA == 1 && ST_SENSOR.vB == 1 && ST_SENSOR.vAb == 0 && ST_SENSOR.vBb == 0 ) varredura_sensor_aux_horario() ;
	}
	else if( ST_SENSOR.nA == 1 && ST_SENSOR.nB == 1 && ST_SENSOR.nAb == 0 && ST_SENSOR.nBb == 0 )
	{
		if( ST_SENSOR.vA == 1 && ST_SENSOR.vB == 0 && ST_SENSOR.vAb == 0 && ST_SENSOR.vBb == 1 ) varredura_sensor_aux_antihorario() ; 
		else if( ST_SENSOR.vA == 0 && ST_SENSOR.vB == 1 && ST_SENSOR.vAb == 1 && ST_SENSOR.vBb == 0 ) varredura_sensor_aux_horario() ;
	}
	else if( ST_SENSOR.nA == 0 && ST_SENSOR.nB == 1 && ST_SENSOR.nAb == 1 && ST_SENSOR.nBb == 0 )
	{
		if( ST_SENSOR.vA == 1 && ST_SENSOR.vB == 1 && ST_SENSOR.vAb == 0 && ST_SENSOR.vBb == 0 ) varredura_sensor_aux_antihorario() ; 
		else if( ST_SENSOR.vA == 0 && ST_SENSOR.vB == 0 && ST_SENSOR.vAb == 1 && ST_SENSOR.vBb == 1 ) varredura_sensor_aux_horario() ;
	}
	else if( ST_SENSOR.nA == 0 && ST_SENSOR.nB == 0 && ST_SENSOR.nAb == 1 && ST_SENSOR.nBb == 1 )
	{
		if( ST_SENSOR.vA == 0 && ST_SENSOR.vB == 1 && ST_SENSOR.vAb == 1 && ST_SENSOR.vBb == 0 ) varredura_sensor_aux_antihorario() ; 
		else if( ST_SENSOR.vA == 1 && ST_SENSOR.vB == 0 && ST_SENSOR.vAb == 0 && ST_SENSOR.vBb == 1 ) varredura_sensor_aux_horario() ;
	}
}

#int_RDA //quando algum dado é recebido pela USART
void interrupcao_RDA() 
{
	gets( TEXTO_USART ) ;
//	fprintf( TEXTO_USART , PORTA_SERIAL ) ;
//	INT_TEMP = strcmp( TEXTO_USART , "#ZERAR" ) ;
	if( INT_TEMP == 0 ) zera_contagem_pulsos() ;
//	else if( TEXTO_USART[] == "#ENVIARPULSOS" ) envia_dados_porta_serial() ;
}
