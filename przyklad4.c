#ifndef __AVR_ATmega328__
#define __AVR_ATmega328__
#endif

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "ADC_lib.h"

float Kd = 0.5f;
float Ti = 0.5f;
volatile int setpoint;
volatile int devation;
const int sum_max = 10000;

float scale(int val) {
    return ((float) val) / 1024;
}

int sum(int val) {
    static int _SUM = 0;
    if (abs(_SUM += val) > sum_max)
        _SUM = sum_max;
    return _SUM;
}

int regulator(int value) {
    int diff = setpoint - value;
    int out = (int) (Kd*diff + sum(diff)*Ti);
    return out < 0xff ? (out < 0 ? 0 : out) : 0xff;
}

void Timer0_Init() {
    TCCR1A  = _BV(WGM10);       // Fast PWM
    TCCR1B  = _BV(WGM11);       // ...
    TCCR1A |= _BV(COM1A1);      // wyjście PWM = PB
    TCCR1B |= _BV(CS00) | _BV(CS01); // clk / 64
    TIMSK1 |= (1 << OCIE0A);    // Uaktywnienie przerwania
}

ISR(TIMER1_COMPA_vect) {
    OCR1A = regulator(ADC_Read_Ch(5));
}

int main() {
    DDRB |= _BV(PB1); 		    // Wyjscia: PB1
    DDRC = 0;                   // Wejscia: PC0-PC7

    Timer0_Init();
    sei();

    while (1) {
        Kd = scale(ADC_Read_Ch(0));
        Ti = scale(ADC_Read_Ch(1));

        setpoint = 20;
        _delay_ms(100);
        setpoint = 2200;
        _delay_ms(100);
    }
}
