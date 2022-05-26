#include "C:\Codigos\PICs\ER1-LCD\ER1-LCD.h"
#include <string.h>
#include "C:\Codigos\PICs\ER1-LCD\LCD-16F628.h"

/***********************************************************************************************************************************
PLACA DE CIRCUITO IMPRESSO - APLICAÇÃO DE CADA PINO DO PIC
Pino 01: (MCLRb) reset do processador
Pino 02:
Pino 03:
Pino 04:
Pino 05:
Pino 06:
Pino 07:
Pino 08: (RDb) controle de leitura da comunicação paralela com LCD, bit RW
Pino 09: (WRb) controle de escrita da comunicação paralela com LCD, bit RS
Pino 10: (Eb) controle de cable select da comunicação paralela com LCD, bit E
Pino 11: VDD
Pino 12: VSS
Pino 13: (OSC1) ligação do cristal de 20MHz
Pino 14: (OSC2) ligação do cristal de 20MHz
Pino 15:
Pino 16:
Pino 17:
Pino 18:
Pino 19: (PSP0) porta D para comunicação paralela com LCD, bit D0
Pino 20: (PSP1) porta D para comunicação paralela com LCD, bit D1
Pino 21: (PSP2) porta D para comunicação paralela com LCD, bit D2
Pino 22: (PSP3) porta D para comunicação paralela com LCD, bit D3
Pino 23:
Pino 24:
Pino 25: (CK) comunicação serial sincrono entre PICs (mestre e escravos) do sistema, clock
Pino 26: (DT) comunicação serial sincrono entre PICs (mestre e escravos) do sistema, leitura/escrita de dados
Pino 27: (PSP4) porta D para comunicação paralela com LCD, bit D4
Pino 28: (PSP5) porta D para comunicação paralela com LCD, bit D5
Pino 29: (PSP6) porta D para comunicação paralela com LCD, bit D6
Pino 30: (PSP7) porta D para comunicação paralela com LCD, bit D7
Pino 31: VSS
Pino 32: VDD
Pino 33: -
Pino 34: (RB1) entrada do sinal do encoder angular, sinal A (fio laranja)
Pino 35: (RB2) entrada do sinal do encoder angular, sinal B (fio amarelo)
Pino 36: -
Pino 37: (RB4) entrada do sinal do encoder angular, sinal Ab (fio azul)
Pino 38: (RB5) entrada do sinal do encoder angular, sinal Bb (fio violeta)
Pino 39: (PGC) via de clock da comunicação serial in-circuit (ICSP)
Pino 40: (PGD) via de dados da comunicação serial in-circuit (ICSP)
Cristal de 20MHz -> 1/(Fosc/4) -> 1 ciclo de instrução = 0,0000002 s
***********************************************************************************************************************************/

//função principal
void main()
{
	//********* CONFIGURAÇÃO DO PIC **********
	//liga interrupções que serão utilizadas
    enable_interrupts(GLOBAL);
	//desliga interrupções que não serão utilizadas
	disable_interrupts( INT_RTCC | INT_RB | INT_EXT | INT_TBE | INT_RDA | INT_TIMER1 | INT_TIMER2 | INT_CCP1 | INT_LCD | INT_COMP | INT_EEPROM | INT_TIMER0 ) ;
	//desativa ADC
    setup_vref(FALSE);
	//destiva comparação / captura / PWM
    setup_comparator(NC_NC_NC_NC);
	setup_ccp1( CCP_OFF ) ;
    setup_timer_1(T1_DISABLED);
    setup_timer_2(T2_DISABLED,0,1);
	// configuração da direção de E/S dados das portas (0=saida e 1=entrada)
	//set_tris_a( 0b11100011 ) ; // pinos RB1, RB2, RB4 e RB5 definidos como entrada
//	set_tris_a( 0b00000 ) ; // pinos B definidos como saída
//	set_tris_b( 0b00000000 ) ; // pinos B definidos como saída
	output_b( 0b00000000 ) ; // zero pinos

	//configuração do LCD
	mfr_lcd_inicializacao() ;
	//escreve primeira mensagem de abertura
	mfr_lcd_posiciona_cursor_16x2( 1 , 1 ) ;
	sprintf( TEXTO , "CONESTEEL.com" ) ;
	mfr_lcd_escreve_texto() ;
	mfr_lcd_posiciona_cursor_16x2( 2 , 1 ) ;
	sprintf( TEXTO , "Valida Prototipo" ) ;
	mfr_lcd_escreve_texto() ;
	delay_ms( 3000 ) ;
	//escreve segunda mensagem de abertura
	mfr_lcd_limpa_display() ;
	mfr_lcd_posiciona_cursor_16x2( 1 , 1 ) ;
	sprintf( TEXTO , "Projeto de" ) ;
	mfr_lcd_escreve_texto() ;
	mfr_lcd_posiciona_cursor_16x2( 2 , 1 ) ;
	sprintf( TEXTO , "Eng.Mauricio FR" ) ;
	mfr_lcd_escreve_texto() ;
	delay_ms( 3000 ) ;
/*
	INT_TAMANHO = 40 ;
	while(true)
	{
		output_low( 40 ) ;
		output_low( 41 ) ;
		output_low( 42 ) ;
		output_low( 43 ) ;
		output_low( 44 ) ;
		output_low( 45 ) ;
		output_low( 46 ) ;
		output_low( 47 ) ;
		output_low( 48 ) ;
		output_low( 49 ) ;
		output_low( 50 ) ;
		output_low( 51 ) ;
		output_low( 52 ) ;
		output_low( 53 ) ;
		output_low( 54 ) ;
		output_low( 55 ) ;
		if( INT_TAMANHO == 40 ) output_high( 40 ) ;
		else if( INT_TAMANHO == 41 ) output_high( 41 ) ;
		else if( INT_TAMANHO == 42 ) output_high( 42 ) ;
		else if( INT_TAMANHO == 43 ) output_high( 43 ) ;
		else if( INT_TAMANHO == 44 ) output_high( 44 ) ;
   		else if( INT_TAMANHO == 45 ) output_high( 45 ) ;
		else if( INT_TAMANHO == 46 ) output_high( 46 ) ;
		else if( INT_TAMANHO == 47 ) output_high( 47 ) ;
		else if( INT_TAMANHO == 48 ) output_high( 48 ) ;
		else if( INT_TAMANHO == 49 ) output_high( 49 ) ;
		else if( INT_TAMANHO == 50 ) output_high( 50 ) ;
		else if( INT_TAMANHO == 51 ) output_high( 51 ) ;
		else if( INT_TAMANHO == 52 ) output_high( 52 ) ;
		else if( INT_TAMANHO == 53 ) output_high( 53 ) ;
		else if( INT_TAMANHO == 54 ) output_high( 54 ) ;
		else if( INT_TAMANHO == 55 ) output_high( 55 ) ;
		delay_ms( 50 ) ;
		INT_TAMANHO++ ;
		if( INT_TAMANHO == 56 ) INT_TAMANHO = 40 ;
	}
*/
	//faz loop de varredura do sensor
	while ( TRUE ) ;
}

//DEMAIS FUNÇÕES

void escreve_valor_lcd()
{
	//"Graus   Volta SV"
	//"360.000 10.01 HA"
	//display com 1 digito
	mfr_lcd_posiciona_cursor_16x2( 2 , 1 ) ;
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
//	sprintf( TEXTO , "%02.3f %02.2f %C%C" , FLOAT_ANGULO , FLOAT_VOLTAS , CHAR_VALVULA_SENTIDO , CHAR_VALVULA_ABRINDO ) ;

//	sprintf( TEXTO , "%03.1f" , FLOAT_CONTADOR_DE_PULSO ) ;

//	sprintf( TEXTO , "%D %D %D %D %D %D %D %D" , ST_SENSOR.nA , ST_SENSOR.nB , ST_SENSOR.nAb , ST_SENSOR.nBb , ST_SENSOR.vA , ST_SENSOR.vB , ST_SENSOR.vAb , ST_SENSOR.vBb ) ;

	mfr_lcd_escreve_texto() ;
}

/*
// TRATA INTERRUPÇÕES
#int_TBE
void TBE_isr() 
{

}

#int_RDA
void RDA_isr() 
{

}
*/
