#ifndef __AVR_ATmega328__
#define __AVR_ATmega328__
#endif

#define F_CPU       8000000UL
#define LCD_Dir     DDRD
#define LCD_Port    PORTD
#define LCD_RS      PD0
#define LCD_EN      PD1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "ADC_lib.h"
#include "LCD_lib.h"

const int setpoint = 600;
const int half_hysteresis = 100;
volatile int value = -1;

Timer0_Init() {
    TCCR0A |= (1 << WGM01);  // Timer mode
    TCCR0B |= (1 << CS02);   // clk / 256
    OCR0A = 0xff;            // Counter max value

    TIMSK0 |= (1 << OCIE0A); //Set the ISR COMPA vect
}

ISR(TIMER0_COMPA_vect) {
    value = ADC_Read_Ch(5);
    int devation = value - setpoint;
    if (devation < -1 * half_hysteresis) PORTC |= 0b00000001;
    else if (devation > half_hysteresis) PORTC &= 0b11111110;

    PORTB ^= _BV(DDB5);
}

int main() {
    DDRC |= 0b1;   // Ustawia C0 - wyjscie, C5 - wejscie
    DDRB |= _BV(DDB5);

    Timer0_Init();
    LCD_Init();
    LCD_String("Wartosc pomiaru:");

    sei();
    char string[5];

    while (1) {
        LCD_GoTo2ndLine();
        itoa(value, string, 10);
        LCD_String(string);
        LCD_String("   ");

        _delay_ms(500);
    }
}
