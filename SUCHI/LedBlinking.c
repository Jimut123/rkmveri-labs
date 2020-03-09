#define F_CPU 11059200UL
#define USART_BAUDRATE 4800
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

#define setbit(port,bit)(port)|=(1<<(bit))
#define clearbit(port,bit)(port)&=~(1<<(bit))

#define kyescanspeed 300
#define ipscanspeed	200
#define scandelay 1000

#include<avr/io.h>
#include<util/delay.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <stdio.h>

void lcd_init();
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_string(unsigned char *str);
void UART_init(long baudrate);
unsigned char UART_RxChar();
void UART_TxChar(char ch);
void gsm_command(char *cmd);
int is_call_active();
char scan(int wait_time);

void main()
{
	int i=0,a=0;
	char admin[16],user[9];
	char c,wrong_pass,gsm_rdy=' ',go_default,adm,usr,timeout=' ',onstate=' ',point=' ';

	DDRA=0xff;
	_delay_ms(2);
	DDRB=0x03;
	_delay_ms(2);
	DDRC=0xff;
	_delay_ms(2);
	DDRD=0x1E;
	_delay_ms(2);

init:

	lcd_init();
	lcd_string("INITIALIZING....");
	lcd_cmd(0xC0);

	i=0;
	while(i<200)
	{
		_delay_ms(80);
		i++;
	}
	i=0;
	
	UART_init(4800);

gsm_init:

	lcd_cmd(0x01);
	lcd_string("INITIALIZING....");
	lcd_cmd(0xC0);
	lcd_string("CHECKING GSM");

	gsm_command("AT");

	c=UART_RxChar();
	while(i<2)
	{	
		if(c!='\r' && c!='\n')
		{
			if(i==0 && c=='O')
			{
				gsm_rdy='-';
			}
			if(i==1 && c=='K')
			{
				if(gsm_rdy=='-')
				{
					gsm_rdy='X';
				}
			}
			i++;
		}
		c=UART_RxChar();
	}
	i=0;

	if(gsm_rdy!='X')
	{
		goto gsm_init;
		lcd_cmd(0x01);
		lcd_string("GSM NOT READY!!");
		_delay_ms(400);
	}

waitcall:
	
	if(timeout=='X')
	{
		PORTC=0b11010011;
		_delay_ms(100);
		PORTC=0b00000000;
		while((PIND & 0b10000000)==0b00000000)
		{
			if(is_call_active())
			{
				;
			}
		}
		if(is_call_active())
		{
			gsm_command("ATH");
		}
		timeout=' ';
	}

	adm=' ';
	usr=' ';
	wrong_pass=' ';
	onstate=' ';
	point=' ';

	memset(admin,0,16);
	eeprom_busy_wait();
	eeprom_read_block(admin,0,16);
	_delay_ms(100);
	
	memset(user,16,9);
	eeprom_busy_wait();
	eeprom_read_block(user,16,9);
	_delay_ms(100);
	
	if(admin[0]>'5' && admin[0]<='9')
	{
		go_default=' ';
	}
	else
	{
		go_default='X';
	}
	
	if(go_default==' ')
	{
		if(user[5]=='1')
		{
			setbit(PORTD,PD3);
		}
		else
		{
			clearbit(PORTD,PD3);
		}
		if(user[6]=='1')
		{
			setbit(PORTD,PD4);
		}
		else
		{
			clearbit(PORTD,PD4);
		}
		if(user[7]=='1')
		{
			setbit(PORTD,PD5);
		}
		else
		{
			clearbit(PORTD,PD5);
		}
		if(user[8]=='1')
		{
			setbit(PORTD,PD6);
		}
		else
		{
			clearbit(PORTD,PD6);
		}
	}
	if(go_default==' ')
	{
		gsm_command("AT+CLIP=1");
		_delay_ms(10);
	}

	lcd_cmd(0x01);
	lcd_string("   DTMF BASED   ");
	lcd_cmd(0xC0);
	lcd_string(" REMOTE CONTROL ");

	while(1)
	{
		if((PINB | 0b11111011)==0b11111011)
		{
			_delay_ms(3000);
			if(go_default=='X')
			{
				lcd_cmd(0x01);
				lcd_string("CALL IN PROGRESS");
				lcd_cmd(0xC0);
				gsm_command("ATA");
				_delay_ms(1000);

				PORTC=0b11000001;
				_delay_ms(1000);
				PORTC=0b00000000;
				while((PIND & 0b10000000)==0b00000000)
				{
					if(is_call_active())
					{
						;
					}
					else
					{
						goto waitcall;
					}
				}
				_delay_ms(scandelay);

				for(i=0;i<10;i++)
				{
					admin[i]=scan(ipscanspeed);
					if(admin[i]=='Y')
					{
						timeout='X';
						goto waitcall;
					}
					if(admin[i]=='X')
					{
						goto waitcall;
					}
					if(admin[i]=='*' || admin[i]=='#' || admin[0]<'6')
					{
						PORTC=0b11010001;
						_delay_ms(1000);
						PORTC=0b00000000;
						while((PIND & 0b10000000)==0b00000000)
						{
							if(is_call_active())
							{
								;
							}
							else
							{
								goto waitcall;
							}
						}						
						gsm_command("ATH");
						goto waitcall;
					}
				}

				PORTC=0b11000010;
				_delay_ms(1000);
				PORTC=0b00000000;
				while((PIND & 0b10000000)==0b00000000)
				{
					if(is_call_active())
					{
						;
					}
					else
					{
						goto waitcall;
					}
				}
				_delay_ms(scandelay);

				for(i=10;i<16;i++)
				{
					admin[i]=scan(ipscanspeed);
					if(admin[i]=='Y')
					{
						timeout='X';
						goto waitcall;
					}
					if(admin[i]=='X')
					{
						goto waitcall;
					}
					if(admin[i]=='*' || admin[i]=='#')
					{
						PORTC=0b11010010;
						_delay_ms(1000);
						PORTC=0b00000000;
						while((PIND & 0b10000000)==0b00000000)
						{
							if(is_call_active())
							{
								;
							}
							else
							{
								goto waitcall;
							}
						}
						if(is_call_active())
						{
							gsm_command("ATH");
						}
						goto waitcall;
					}
				}

				eeprom_update_block(admin,0,16);
				_delay_ms(100);

				user[0]='1';
				user[1]='2';
				user[2]='3';
				user[3]='4';
				user[4]='0';

				for(i=5;i<9;i++)
				{
					user[i]='0';
				}

				eeprom_update_block(user,16,9);
				_delay_ms(100);

				PORTC=0b11000011;
				_delay_ms(1000);
				PORTC=0b00000000;
				while((PIND & 0b10000000)==0b00000000)
				{
					a=is_call_active();
					if(a==1)
					{
						;
					}
					else
					{
						goto init;
					}
				}
				if(is_call_active())
				{
					gsm_command("ATH");
				}
				goto init;
			}
			else
			{
				lcd_cmd(0x01);
				lcd_string("CALL IN PROGRESS");
				lcd_cmd(0xC0);
				i=0;
				while(i<21)
				{
					c=UART_RxChar();
					if(c=='\r')
					{
						;
					}
					else if(c=='\n')
					{
						;
					}
					else
					{
						if(i==0)
						{
							if(c=='+')
							{
								i++;
							}
						}
						else
						{
							if(i>10)
							{
								if(c==admin[i-11])
								{
									adm='X';
								}
								else
								{
									adm=' ';
									usr='X';
								}
							}
							i++;
						}
					}
				}

				if(adm=='X')
				{
					gsm_command("ATA");
					_delay_ms(1000);

					PORTC=0b11000100;
					_delay_ms(1000);
					PORTC=0b00000000;
					while((PIND & 0b10000000)==0b00000000)
					{
						if(is_call_active())
						{
							;
						}
						else
						{
							goto waitcall;
						}
					}
					_delay_ms(scandelay);

					for(i=10;i<16;i++)
					{
						c=scan(ipscanspeed);
						if(c!=admin[i])
						{
							if(c=='Y')
							{
								timeout='X';
								goto waitcall;
							}
							if(c=='X')
							{
								goto waitcall;
							}
							
							PORTC=0b11000101;
							_delay_ms(1000);
							PORTC=0b00000000;
							while((PIND & 0b10000000)==0b00000000)
							{		
								if(is_call_active())
								{
									;
								}
								else
								{
									goto waitcall;
								}
							}
							gsm_command("ATH");
							goto waitcall;
						}
					}
				
					PORTC=0b11000111;
					_delay_ms(1000);
					PORTC=0b00000000;
					
					while((PIND & 0b10000000)==0b00000000)
					{
						if(is_call_active())
						{
							;
						}
						else
						{
							goto waitcall;
						}
					}
					_delay_ms(scandelay);

					c=scan(ipscanspeed);
					if(c=='Y')
					{
						timeout='X';
						goto waitcall;
					}
					if(c=='X')
					{
						goto waitcall;
					}
					if(c=='*' || c=='#' || c>'3')
					{
						PORTC=0b11010100;
						_delay_ms(1000);
						PORTC=0b00000000;
					
						while((PIND & 0b10000000)==0b00000000)
						{
							if(is_call_active())
							{
								;
							}
							else
							{
								goto waitcall;
							}
						}
						gsm_command("ATH");
						goto waitcall;
					}
					
					switch(c)
					{
						case '1':
							
							PORTC=0b11001000;
							_delay_ms(1000);
							PORTC=0b00000000;
							while((PIND & 0b10000000)==0b00000000)
							{
								if(is_call_active())
								{
									;
								}
								else
								{
									goto waitcall;
								}
							}
							_delay_ms(scandelay);
						
							for(i=0;i<10;i++)
							{
								admin[i]=scan(ipscanspeed);
								if(admin[i]=='Y')
								{
									timeout='X';
									goto waitcall;
								}
								if(admin[i]=='X')
								{
									goto waitcall;
								}
								if(admin[i]=='*' || admin[i]=='#' || admin[0]<'6')
								{
									PORTC=0b11010001;
									_delay_ms(1000);
									PORTC=0b00000000;
									while((PIND & 0b10000000)==0b00000000)
									{
										if(is_call_active())
										{
											;
										}
										else
										{
											goto waitcall;
										}
									}						
									gsm_command("ATH");
									goto waitcall;
								}
							}
												
							eeprom_update_block(admin,0,16);
							_delay_ms(100);

							PORTC=0b11000011;
							_delay_ms(1000);
							PORTC=0b00000000;
							while((PIND & 0b10000000)==0b00000000)
							{
								if(is_call_active())
								{
									;
								}
								else
								{
									goto waitcall;
								}
							}						
							gsm_command("ATH");
							goto waitcall;

						case '2':
							
							PORTC=0b11001001;
							_delay_ms(1000);
							PORTC=0b00000000;
					
							while((PIND & 0b10000000)==0b00000000)
							{
								if(is_call_active())
								{
									;
								}
								else
								{
									goto waitcall;
								}
							}
							_delay_ms(scandelay);

							for(i=10;i<16;i++)
							{
								admin[i]=scan(ipscanspeed);
								if(admin[i]=='Y')
								{
									timeout='X';
									goto waitcall;
								}
								if(admin[i]=='X')
								{
									goto waitcall;
								}
								if(admin[i]=='*' || admin[i]=='#')
								{
									PORTC=0b11010010;
									_delay_ms(1000);
									PORTC=0b00000000;
					
									while((PIND & 0b10000000)==0b00000000)
									{
										if(is_call_active())
										{
											;
										}
										else
										{
											goto waitcall;
										}
									}
									
									gsm_command("ATH");
									goto waitcall;
								}
							}

							eeprom_update_block(admin,0,16);
							_delay_ms(100);

							PORTC=0b11001010;
							_delay_ms(1000);
							PORTC=0b00000000;
				
							while((PIND & 0b10000000)==0b00000000)
							{
								if(is_call_active())
								{
									;
								}
								else
								{
									goto waitcall;
								}
							}

							gsm_command("ATH");
							goto init;
							break;

						case '3':

							user[0]='1';
							user[1]='2';
							user[2]='3';
							user[3]='4';
							user[4]='0';
							eeprom_update_block(user,16,9);
							_delay_ms(100);
							
							PORTC=0b11001011;
							_delay_ms(1000);
							PORTC=0b00000000;
				
							while((PIND & 0b10000000)==0b00000000)
							{
								if(is_call_active())
								{
									;
								}
								else
								{
									goto waitcall;
								}
							}

							gsm_command("ATH");
							goto init;
							break;

						default:
							break;
					}								 
				}
				else
				{
					gsm_command("ATA");
					_delay_ms(1000);

					if(user[4]=='3')
					{
						goto userlocked;
					}

					PORTC=0b11000100;
					_delay_ms(1000);
					PORTC=0b00000000;
				
					while((PIND & 0b10000000)==0b00000000)
					{
						if(is_call_active())
						{
							;
						}
						else
						{
							goto waitcall;
						}
					}
					_delay_ms(scandelay);
					
					a=0;
					if(user[4]=='1')
					{
						a=1;	
					}
					if(user[4]=='2')
					{
						a=2;	
					}

wrongpass:			wrong_pass=' ';
					for(i=0;i<4;i++)
					{
						c=scan(ipscanspeed);
						if(c!=user[i])
						{
							if(c=='Y')
							{
								timeout='X';
								goto waitcall;
							}
							if(c=='X')
							{
								goto waitcall;
							}
							wrong_pass='X';
						}
					}
					if(wrong_pass=='X')
					{
						a++;
						if(a==1)
						{
							user[4]='1';
						}
						if(a==2)
						{
							user[4]='2';
						}
						if(a==3)
						{
							user[4]='3';
						}
						eeprom_update_block(user,16,9);
						_delay_ms(100);

						if(a<3)
						{
							PORTC=0b11000101;
							_delay_ms(1000);
							PORTC=0b00000000;
							while((PIND & 0b10000000)==0b00000000)
							{		
								if(is_call_active())
								{
									;
								}
								else
								{
									goto waitcall;
								}
							}
							goto wrongpass;
						}
						else
						{
userlocked:					PORTC=0b11000110;
							_delay_ms(1000);
							PORTC=0b00000000;
							while((PIND & 0b10000000)==0b00000000)
							{		
								if(is_call_active())
								{
									;
								}
								else
								{
									goto waitcall;
								}
							}
							gsm_command("ATH");
							goto waitcall;
						}
					}
					else
					{
						user[4]='0';
						eeprom_update_block(user,16,9);
						_delay_ms(100);

						PORTC=0b11001100;
						_delay_ms(1000);
						PORTC=0b00000000;
						while((PIND & 0b10000000)==0b00000000)
						{		
							if(is_call_active())
							{
								;
							}
							else
							{
								goto waitcall;
							}
						}
						_delay_ms(scandelay);

						c=scan(ipscanspeed);
						if(c=='Y')
						{
							timeout='X';
							goto waitcall;
						}
						if(c=='X')
						{
							goto waitcall;
						}
						if(c=='*' || c=='#' || c>'2')
						{
							PORTC=0b11010100;
							_delay_ms(1000);
							PORTC=0b00000000;
					
							while((PIND & 0b10000000)==0b00000000)
							{
								if(is_call_active())
								{
									;
								}
								else
								{
									goto waitcall;
								}
							}
							gsm_command("ATH");
							goto waitcall;
						}
						
						switch(c)
						{
							case '1':
								
								PORTC=0b11001001;
								_delay_ms(1000);
								PORTC=0b00000000;
					
								while((PIND & 0b10000000)==0b00000000)
								{
									if(is_call_active())
									{
										;
									}
									else
									{
										goto waitcall;
									}
								}
								_delay_ms(scandelay);
								
								for(i=0;i<4;i++)
								{
									c=scan(ipscanspeed);
									if(c=='Y')
									{
										timeout='X';
										goto waitcall;
									}
									if(c=='X')
									{
										goto waitcall;
									}
									if(c=='*' || c=='#')
									{
										PORTC=0b11010010;
										_delay_ms(1000);
										PORTC=0b00000000;
					
										while((PIND & 0b10000000)==0b00000000)
										{
											if(is_call_active())
											{
												;
											}
											else
											{
												goto waitcall;
											}
										}
									
										gsm_command("ATH");
										goto waitcall;
									}
									user[i]=c;
								}

								eeprom_update_block(user,16,9);
								_delay_ms(100);

								PORTC=0b11001010;
								_delay_ms(1000);
								PORTC=0b00000000;
				
								while((PIND & 0b10000000)==0b00000000)
								{
									if(is_call_active())
									{
										;
									}
									else
									{
										goto waitcall;
									}
								}

								gsm_command("ATH");
								goto waitcall;
								break;

							case '2':
								
								PORTC=0b11001101;
								_delay_ms(1000);
								PORTC=0b00000000;
				
								while((PIND & 0b10000000)==0b00000000)
								{
									if(is_call_active())
									{
										;
									}
									else
									{
										goto waitcall;
									}
								}
								_delay_ms(scandelay);
								
								point=scan(ipscanspeed);
								if(point=='Y')
								{
									timeout='X';
									goto waitcall;
								}
								if(point=='X')
								{
									goto waitcall;
								}
								if(point=='*' || point=='#' || point>'4')
								{
									PORTC=0b11010100;
									_delay_ms(1000);
									PORTC=0b00000000;
						
									while((PIND & 0b10000000)==0b00000000)
									{
										if(is_call_active())
										{
											;
										}	
										else
										{
											goto waitcall;
										}
									}
									gsm_command("ATH");
									goto waitcall;
								}

								switch(point)
								{
									case '1':
										if(user[5]=='0')
										{
											onstate='N';
										}
										if(user[5]=='1')
										{
											onstate='Y';
										}
										break;

									case '2':
										if(user[6]=='0')
										{
											onstate='N';
										}
										if(user[6]=='1')
										{
											onstate='Y';
										}
										break;

									case '3':
										if(user[7]=='0')
										{
											onstate='N';
										}
										if(user[7]=='1')
										{
											onstate='Y';
										}
										break;

									case '4':
										if(user[8]=='0')
										{
											onstate='N';
										}
										if(user[8]=='1')
										{
											onstate='Y';
										}
										break;

									default:
										break;
								}

								if(onstate=='Y')
								{
									PORTC=0b11001110;
									_delay_ms(1000);
									PORTC=0b00000000;
						
									while((PIND & 0b10000000)==0b00000000)
									{
										if(is_call_active())
										{
											;
										}	
										else
										{
											goto waitcall;
										}
									}
								}
								if(onstate=='N')
								{
									PORTC=0b11001111;
									_delay_ms(1000);
									PORTC=0b00000000;
						
									while((PIND & 0b10000000)==0b00000000)
									{
										if(is_call_active())
										{
											;
										}	
										else
										{
											goto waitcall;
										}
									}
								}
								_delay_ms(scandelay);

								c=scan(ipscanspeed);
								if(c=='Y')
								{
									timeout='X';
									goto waitcall;
								}
								if(c=='X')
								{
									goto waitcall;
								}
								if(c=='*' && onstate=='N')
								{
									switch(point)
									{
										case '1':
											user[5]='1';
											PIND=PIND || 0b00010000;
											break;
										case '2':
											user[6]='1';
											PIND=PIND || 0b00001000;
											break;
										case '3':
											user[7]='1';
											PIND=PIND || 0b00000100;
											break;
										case '4':
											user[8]='1';
											PIND=PIND || 0b00000010;
											break;
										default:
											break;
									}

								}
								else if(c=='#' && onstate=='Y')
								{
									switch(point)
									{
										case '1':
											user[5]='0';
											PIND=PIND && 0b11101111;
											break;
										case '2':
											user[6]='0';
											PIND=PIND && 0b11110111;
											break;
										case '3':
											user[7]='0';
											PIND=PIND && 0b11111011;
											break;
										case '4':
											user[8]='0';
											PIND=PIND && 0b11111101;
											break;
										default:
											break;
									}
								}
								else
								{
									PORTC=0b11010100;
									_delay_ms(1000);
									PORTC=0b00000000;
							
									while((PIND & 0b10000000)==0b00000000)
									{
										if(is_call_active())
										{
											;
										}
										else
										{
											goto waitcall;
										}
									}
									gsm_command("ATH");
									goto waitcall;
								}
								eeprom_update_block(user,16,9);
								_delay_ms(100);

								PORTC=0b11010000;
								_delay_ms(1000);
								PORTC=0b00000000;
							
								while((PIND & 0b10000000)==0b00000000)
								{
									if(is_call_active())
									{
										;
									}
									else
									{
										goto waitcall;
									}
								}
								gsm_command("ATH");
								goto waitcall;								

							default:
								break;
						}	
					}
				}
			}
		}
	}
}

void lcd_cmd(unsigned char cmd)
{
	PORTA=cmd;
	clearbit(PORTB,PB0);
	setbit(PORTB,PB1);
	_delay_ms(1);
	clearbit(PORTB,PB1);
	_delay_ms(1);
}
void lcd_data(unsigned char data)
{
	PORTA=data;
	setbit(PORTB,PB0);
	setbit(PORTB,PB1);
	_delay_ms(1);
	clearbit(PORTB,PB1);
	_delay_ms(1);
}
void lcd_init()
{
	lcd_cmd(0x38);
	_delay_ms(1);
	lcd_cmd(0x01);
	_delay_ms(1);
	lcd_cmd(0x0E);
	_delay_ms(1);
	lcd_cmd(0x80);
	_delay_ms(1);
}
void lcd_string(unsigned char *str)
{
	while(*str)
	{
		lcd_data(*str++);
	}
}
void UART_init(long baudrate)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL= BAUD_PRESCALE;
	UBRRH=(BAUD_PRESCALE >> 8);
}
unsigned char UART_RxChar()
{
	while((UCSRA & (1 << RXC))==0);
	{
		return(UDR);
	}
}

void UART_TxChar(char ch)
{
	while (!(UCSRA&(1<<UDRE)));
	{
		UDR=ch ;
	}	
}
void gsm_command(char *cmd)
{
	while(*cmd)
	{
		UART_TxChar(*cmd++);
	}
	UART_TxChar('\r');
	UART_TxChar('\n');
}
int is_call_active()
{
	int a=0;
	char flag=' ';
	unsigned char resp;
	gsm_command("AT+CPAS");
	while(a<8)
	{
		resp=UART_RxChar();
		if(resp!='\r' && resp!='\n')
		{
			if(resp=='+')
			{
				flag='X';
			}
			if(flag=='X')
			{
				a++;
			}
		}
	}
	if(resp=='4')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
char scan(int wait_time)
{
	int i=0;
	char c=' ';
	while(i<wait_time)
	{
		if(((PINB & 0b10000000)==0b10000000) && ((PIND & 0b10000000)==0b10000000))
		{
			_delay_ms(100);
			switch(PINB | 0b10000111)
			{
				case 0b10001111:
					PORTC=0b11010101;
					_delay_ms(kyescanspeed);
					PORTC=0b00000000;
					c='1';
					break;
				
				case 0b10010111:
					PORTC=0b11010110;
					_delay_ms(kyescanspeed);
					PORTC=0b00000000;
					c='2';
					break;
				
				case 0b10011111:
					PORTC=0b11010111;
					_delay_ms(kyescanspeed);
					PORTC=0b00000000;
					c='3';
					break;

				case 0b10100111:
					PORTC=0b11011000;
					_delay_ms(kyescanspeed);
					PORTC=0b00000000;
					c='4';
					break;

				case 0b10101111:
					PORTC=0b11011001;
					_delay_ms(kyescanspeed);
					PORTC=0b00000000;
					c='5';
					break;
				
				case 0b10110111:
					PORTC=0b11011010;
					_delay_ms(kyescanspeed);
					PORTC=0b00000000;
					c='6';
					break;

				case 0b10111111:
					PORTC=0b11011011;
					_delay_ms(kyescanspeed);
					PORTC=0b00000000;
					c='7';
					break;

				case 0b11000111:
					PORTC=0b11011100;
					_delay_ms(kyescanspeed);
					PORTC=0b00000000;
					c='8';
					break;

				case 0b11001111:
					PORTC=0b11011101;
					_delay_ms(kyescanspeed);
					PORTC=0b00000000;
					c='9';
					break;

				case 0b11010111:
					PORTC=0b11011110;
					_delay_ms(kyescanspeed);
					PORTC=0b00000000;
					c='0';
					break;
				
				case 0b11011111:
					_delay_ms(kyescanspeed);
					c='*';
					break;
	
				case 0b11100111:
					_delay_ms(kyescanspeed);
					c='#';
					break;
				
				default:
					break;
			}
			if(c!=' ')
			{
				while((PIND & 0b10000000)==0b00000000)
				{
					;
				}
				_delay_ms(500);
				return c;
			}
		}
		else
		{
			if(is_call_active())
			{
				_delay_ms(1);
				i++;
			}
			else
			{
				return 'X';
			}
		}
	}
	return 'Y';
}
