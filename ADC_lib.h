#ifndef __AVR_ATmega328__
#define __AVR_ATmega328__
#endif

#include <avr/io.h>
#include <util/delay.h>

int ADC_Read_Ch(uint8_t pinC){
    int Ain;
    ADMUX = pinC;             // ADC input pin
    ADMUX |= (1 << REFS0);    // AVcc jako napiecie referencji
    ADMUX &= ~(1 << ADLAR);   // 10 bit

    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 8Mhz
    ADCSRA |= (1 << ADEN);    // ADC

    ADCSRA |= (1 << ADSC);    // konwersja ADC
    while( ADCSRA & (1 << ADSC) ){}
    _delay_us(100);

    Ain = ADCL;
    Ain += (int) (ADCH << 8);
    return Ain;
}
