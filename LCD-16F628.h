/***********************************************************************************************************************************
LCD-16F628.h   -   Biblioteca com funções para LCD usando o PIC16F628
Data da criação: 26/07/2006
Autor: Engº Mauricio Fernandes Raphael
***********************************************************************************************************************************/

//Este código deverá ser alterado conforme script/circuito que usar esta biblioteca como include.
#define		LCD_PINO_E					PIN_A4
#define		LCD_PINO_RS					PIN_A2
#define		LCD_PINO_RW					PIN_A3

//DEFINIÇÕES
#define		LCD_COMANDO_LIMPALCD		0b00000001
#define		LCD_COMANDO_HOME			0b00000010
#define		LCD_LIN1COL1				0x80
#define		LCD_LIN2COL1				0xC0
	
//PROTÓTIPOS DE FUNÇÕES
void mfr_lcd_escreve_comando( int COMANDO ) ;
void mfr_lcd_escreve_dado( char DADO ) ;
void mfr_lcd_limpa_display() ;
void mfr_lcd_cursor_home() ;
void mfr_lcd_posiciona_cursor_16x2( int LINHA , int COLUNA ) ;
void mfr_lcd_escreve_texto() ;
void mfr_lcd_inicializacao() ;

// FUNÇÕES PARA LCD
void mfr_lcd_escreve_comando( int COMANDO )
{
	output_low( LCD_PINO_E ) ;
	output_low( LCD_PINO_RS ) ;
	output_low( LCD_PINO_RW ) ;
	output_b( COMANDO ) ;
 	output_high( LCD_PINO_E ) ;
	output_low( LCD_PINO_E ) ;
	delay_ms( 2 ) ; 
}

void mfr_lcd_escreve_dado( char DADO )
{
	output_low( LCD_PINO_E ) ;
	output_high( LCD_PINO_RS ) ;
	output_low( LCD_PINO_RW ) ;
	output_b( DADO ) ;
	output_high( LCD_PINO_E ) ;
	output_low( LCD_PINO_E ) ;
	delay_us( 60 ) ; 
}

//clear display
void mfr_lcd_limpa_display() 
{
	mfr_lcd_escreve_comando( LCD_COMANDO_LIMPALCD ) ;
}

//return mode
void mfr_lcd_cursor_home() 
{
	mfr_lcd_escreve_comando( LCD_COMANDO_HOME ) ;
}

void mfr_lcd_posiciona_cursor_16x2( int LINHA , int COLUNA ) //set DDRAM ADRESS
{
	int POSICAO ;
	if( LINHA > 2 || COLUNA > 16 ) return ;
//	if( LINHA == 1 ) POSICAO = LCD_LIN1COL1 | ( COLUNA - 1 ) ;
//	else POSICAO = LCD_LIN2COL1 | ( COLUNA - 1 ) ;
	if( LINHA == 1 ) POSICAO = LCD_LIN1COL1 ;
	else POSICAO = LCD_LIN2COL1 ;
	mfr_lcd_escreve_comando( POSICAO ) ;
}

void mfr_lcd_escreve_texto()
{
	INT_TAMANHO = strlen( TEXTO ) - 1 ;
	for( INT_TEMP=0 ; INT_TEMP <= INT_TAMANHO ; INT_TEMP++ )
	{
		mfr_lcd_escreve_dado( TEXTO[ INT_TEMP ] ) ;
	}
}

void mfr_lcd_inicializacao()
{
	//para valor de tensão estabilizar no LCD
	delay_ms( 40 ) ;
	//function set
	// 2 linhas, barramento de 8 bits
	mfr_lcd_escreve_comando( 0b00111100 ) ;
	//display/control on/off
	//sem curso piscante, sem underline no cursor, liga display
	mfr_lcd_escreve_comando( 0b00001100 ) ;
	//display clear
	mfr_lcd_escreve_comando( LCD_COMANDO_LIMPALCD ) ;
	//entry mode set
	//sem deslocar mensagem, cursor para a direita
	mfr_lcd_escreve_comando( 0b00000110 ) ;
}
