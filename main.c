#define F_CPU 20000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#define ID_SIZE 4

const char key[ID_SIZE] = "1234";

#define MOT_PORT PORTD
#define MOT_DDR DDRD
#define MOT_IN1 3
#define MOT_IN2 4

#define BAUD 9600                               // define baud
#define UBRR ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR

// function to initialize UART
void uart_init (void)
{
	UBRR0 = UBRR;							 // set baud rate
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);   // enable receiver and transmitter
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // 8bit data format
}

void usart_transmit (uint8_t data)
{
	/* Wait for empty transmit buffer */
	while (! (UCSR0A & (1 << UDRE0)));
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void usart_transmit_str (const char* str)
{
	int len = strlen(str);
	int i;
	
	for (i = 0; i < len; i++)
	{
		usart_transmit (str[i]);
	}
}

uint8_t usart_receive_char()
{
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void init_motor()
{
	MOT_DDR  |= (1<<MOT_IN1) | (1<<MOT_IN2);
	MOT_PORT |= (1<<MOT_IN1) | (1<<MOT_IN2);
}

void spin_motor_right()
{
	MOT_PORT |= (1<<MOT_IN1);
	MOT_PORT &=~(1<<MOT_IN2);
}

void spin_motor_left()
{
	MOT_PORT &= ~(1<<MOT_IN1);
	MOT_PORT |=  (1<<MOT_IN2);
}

void stop_motor()
{
	MOT_PORT |= (1<<MOT_IN1) | (1<<MOT_IN2);
}


int main(void)
{
	const char state_cmd[6]= "state?";
	char data [5];
	const char data_cmd[5]= "data?";
	uint8_t wrong =1;
	
	
	uart_init();
	init_motor();
	
	while (1)
	{
		/* check status : 0 = no card, 1 = card found */
		usart_transmit_str(state_cmd);
		data[0] = usart_receive_char();
		
		if(data[0] == '1' ) /* if state ok */
		{
			usart_transmit_str(data_cmd);
			for(int i = 1; i<=ID_SIZE; i++)
			data[i] = usart_receive_char();

			for(int i=0; i<ID_SIZE; i++)
			{
				if(data[i+1] != key[i])  /* wrong id */
				{
					wrong = 1;
					break;
				}
				wrong = 0; /* went through all bytes, all ok */
				
			}
			
			if(wrong == 0)
			{
				spin_motor_left();
				_delay_ms(1000);
				stop_motor();
				_delay_ms(2000);
				spin_motor_right();
				_delay_ms(1000);
				stop_motor();
			}
		}
		/* reset info */
		memset(data,0,5*sizeof(char));
		wrong =1;
		_delay_ms(100);
	}
}
