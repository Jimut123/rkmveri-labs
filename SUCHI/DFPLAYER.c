#define F_CPU 11059200UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>
#include<stdlib.h>

void UART_init(long baudrate);
void UART_TxChar(uint8_t ch);
void UART_TxCmd(unsigned char cmd);

void main()
{
	DDRA=0x00;
	_delay_ms(2);
	DDRB=0b11111110;
	UART_init(9600);
	_delay_ms(2);

	UART_TxChar(0x7E);
	UART_TxChar(0xFF);
	UART_TxChar(0x04);
	UART_TxChar(0x0C);
	UART_TxChar(0x00);
	UART_TxChar(0x00);
	UART_TxChar(0x00);
	UART_TxChar(0xEF);
	_delay_ms(5);

	UART_TxChar(0x7E);
	UART_TxChar(0xFF);
	UART_TxChar(0x04);
	UART_TxChar(0x09);
	UART_TxChar(0x00);
	UART_TxChar(0x00);
	UART_TxChar(0x02);
	UART_TxChar(0xEF);
	_delay_ms(5);

	UART_TxChar(0x7E);
	UART_TxChar(0xFF);
	UART_TxChar(0x04);
	UART_TxChar(0x06);
	UART_TxChar(0x00);
	UART_TxChar(0x00);
	UART_TxChar(0x1E);
	UART_TxChar(0xEF);
	_delay_ms(1000);

scan:

	while(1)
	{
		if((PINA & 0b11000000)==0b11000000)
		{
			while((PINB & 0b00000001)==0b00000001)
			{	
				switch (PINA)
				{
					case 0b11000001:
					UART_TxCmd(0x01);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}
					break;

					case 0b11000010:
					UART_TxCmd(0x02);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}
					break;

					case 0b11000011:
					UART_TxCmd(0x03);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}
					break;

					case 0b11000100:
					UART_TxCmd(0x04);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}
					break;

					case 0b11000101:
					UART_TxCmd(0x05);
					_delay_ms(100);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}
					break;

					case 0b11000110:
					UART_TxCmd(0x06);
					_delay_ms(100);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}
					break;

					case 0b11000111:
					UART_TxCmd(0x07);
					_delay_ms(100);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11001000:
					UART_TxCmd(0x08);
					_delay_ms(100);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11001001:
					UART_TxCmd(0x09);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11001010:
					UART_TxCmd(0x0A);
					_delay_ms(100);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11001011:
					UART_TxCmd(0x0B);
					_delay_ms(100);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11001100:
					UART_TxCmd(0x0C);
					_delay_ms(100);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11001101:
					UART_TxCmd(0x0D);
					_delay_ms(100);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11001110:
					UART_TxCmd(0x0E);
					_delay_ms(100);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11001111:
					UART_TxCmd(0x0F);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11010000:
					UART_TxCmd(0x10);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11010001:
					UART_TxCmd(0x11);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11010010:
					UART_TxCmd(0x12);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}
					break;

					case 0b11010011:
					UART_TxCmd(0x13);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11010100:
					UART_TxCmd(0x14);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11010101:
					UART_TxCmd(0x15);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11010110:
					UART_TxCmd(0x16);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11010111:
					UART_TxCmd(0x17);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11011000:
					UART_TxCmd(0x18);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11011001:
					UART_TxCmd(0x19);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11011010:
					UART_TxCmd(0x1A);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11011011:
					UART_TxCmd(0x1B);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11011100:
					UART_TxCmd(0x1C);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11011101:
					UART_TxCmd(0x1D);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					case 0b11011110:
					UART_TxCmd(0x1E);
					_delay_ms(1000);
					while((PINB & 0b00000001)==0b00000000)
					{
						;
					}					
					break;

					default:
					break;
				}
				goto scan;
			}		
		}
	}
}

void UART_init(long baudrate)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL= BAUD_PRESCALE;
	UBRRH=(BAUD_PRESCALE >> 8);
}

void UART_TxChar(uint8_t ch)
{
	while (!(UCSRA&(1<<UDRE)));
	{
		UDR=ch ;
	}	
}

void UART_TxCmd(unsigned char cmd)
{
	UART_TxChar(0x7E);
	UART_TxChar(0xFF);
	UART_TxChar(0x06);
	UART_TxChar(0x0F);
	UART_TxChar(0x00);
	UART_TxChar(0x01);
	UART_TxChar(cmd);;
	UART_TxChar(0xEF);	
}
