/***********************************************************************************************************************************
mfr_lcd.h   -   Biblioteca com funções para LCD
Data da criação: 01/06/2006
Autor: Engº Mauricio Fernandes Raphael
***********************************************************************************************************************************/

//esta constante deverá ficar nesta biblioteca e ajustada conforme utilização por outro script, dependendo da porta utilizada
const		CT_NOME_PORTA = 'D' ;		

//Este código deverá ser alterado conforme script/circuito que usar esta biblioteca como include.
#define		LCD_PINO_E					PIN_E1
#define		LCD_PINO_RS					PIN_E0	
#define		LCD_PINO_RW					PIN_E2
#define		LCD_PINOS_DADOS				PIN_DADOS

//DEFINIÇÕES DE VARIÁVEIS
#define		LCD_COMANDO_LIMPALCD		0b00000001
#define		LCD_COMANDO_HOME			0b00000011

int TEMP_LCD ;

// FUNÇÕES PARA LCD

void lcd_pino_enable( boolean HABILITA )
{
	if( HABILITA == true ) output_high( LCD_PINO_E ) ; 
	else output_low( LCD_PINO_E ) ;
}

void lcd_pino_rs( boolean HABILITA )
{
	if( HABILITA == true ) output_high( LCD_PINO_RS ) ; 
	else output_low( LCD_PINO_RS ) ;
}

void lcd_pino_rw( boolean HABILITA )
{
	if( HABILITA == true ) output_high( LCD_PINO_RW ) ; 
	else output_low( LCD_PINO_RW ) ;
}

void lcd_escreve_porta( int DADO_OU_COMANDO , char TIPO , int UNIDADE_TEMPO , int16 VALOR_TEMPO )
{
	lcd_pino_enable( false ) ;
	if( TIPO == 'C' ) //comando
	{
		lcd_pino_rs( false ) ;
		lcd_pino_rw( false ) ;
	} else
	if( TIPO == 'E' ) //escrita
	{
		lcd_pino_rs( true ) ;
		lcd_pino_rw( false ) ;
	} else
	if( TIPO == 'L' ) //leitura
	{
		lcd_pino_rs( true ) ;
		lcd_pino_rw( true ) ;
	}
	//verifica tipo de escrita
	if( CT_NOME_PORTA == 'A' ) Output_A( DADO_OU_COMANDO ) ; else
	if( CT_NOME_PORTA == 'B' ) Output_B( DADO_OU_COMANDO ) ; else
	if( CT_NOME_PORTA == 'C' ) Output_C( DADO_OU_COMANDO ) ; else
	if( CT_NOME_PORTA == 'D' ) Output_D( DADO_OU_COMANDO ) ; else
	if( CT_NOME_PORTA == 'E' ) Output_E( DADO_OU_COMANDO ) ; else
	if( CT_NOME_PORTA == 'F' ) Output_F( DADO_OU_COMANDO ) ; else
	if( CT_NOME_PORTA == 'G' ) Output_G( DADO_OU_COMANDO ) ; else
	if( CT_NOME_PORTA == 'H' ) Output_H( DADO_OU_COMANDO ) ; else
	if( CT_NOME_PORTA == 'I' ) Output_I( DADO_OU_COMANDO ) ; else
	if( CT_NOME_PORTA == 'J' ) Output_J( DADO_OU_COMANDO ) ; else
	if( CT_NOME_PORTA == 'K' ) Output_K( DADO_OU_COMANDO ) ;
	lcd_pino_enable( true ) ;
	lcd_pino_enable( false ) ;
	if( UNIDADE_TEMPO == 3 ) delay_ms( VALOR_TEMPO ) ; else //delay em milisegundos
	if( UNIDADE_TEMPO == 6 ) delay_us( VALOR_TEMPO ) ; //delay em microsegundos
}

void lcd_limpa_display() //clear display
{
	lcd_escreve_porta( LCD_COMANDO_LIMPALCD , 'C' , 3 , 2 ) ;
}

void lcd_cursor_home() //return mode
{
	lcd_escreve_porta( LCD_COMANDO_HOME , 'C' , 3 , 2 ) ;
}

void lcd_modo_operacao( int1 DESLOCAMENTO_MSG , int1 CURSOR_PARA_DIREITA ) //entry mode set
{
	TEMP_LCD = 0b00000100 ;
	TEMP_LCD.0 = DESLOCAMENTO_MSG ;
	TEMP_LCD.1 = CURSOR_PARA_DIREITA ;
	lcd_escreve_porta( TEMP_LCD , 'C' , 6 , 50 ) ;
}

void lcd_modo_display_cursor( int1 CURSOR_PISCANTE , int1 CURSOR_VISIVEL_LINHA , int1 LIGA_DISPLAY ) //display/control ON/OFF
{
	TEMP_LCD = 0b00001000 ;
	TEMP_LCD.0 = CURSOR_PISCANTE ;
	TEMP_LCD.1 = CURSOR_VISIVEL_LINHA ;
	TEMP_LCD.2 = LIGA_DISPLAY ;
	lcd_escreve_porta( TEMP_LCD , 'C' , 6 , 50 ) ;
}

void lcd_deslocamento_cursor_mensagem( int1 DUASLINHAS , int1 BARRAMENTO8BITS ) //function set
{
	TEMP_LCD = 0b00010000 ;
	TEMP_LCD.2 = DUASLINHAS ;
    TEMP_LCD.3 = DUASLINHAS ;
	TEMP_LCD.4 = BARRAMENTO8BITS ;
	lcd_escreve_porta( TEMP_LCD , 'C' , 6 , 50 ) ;
}

void lcd_posiciona_cursor_16x2( int LINHA , int COLUNA )
{
	if( LINHA > 2 || COLUNA > 16 ) return ;
	int POSICAO ;
	if( LINHA == 1 ) POSICAO = 0x80 + ( COLUNA - 1 ) ; 
	else POSICAO = 0xC0 + ( COLUNA - 1 ) ;
	lcd_escreve_porta( POSICAO , 'C' , 6 , 50 ) ;
}

void lcd_escreve_texto( char TEXTO )
{
	int TAMANHO ;
	TAMANHO = strlen( TEXTO ) ;
	for( X=0 , X <= TAMANHO , X++ )
	{
		lcd_escreve_porta( TAMANHO[X] , 'E' , 6 , 60 ) ;
	}
}
