#ifndef __AVR_ATmega32__
#define __AVR_ATmega32__
#endif

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>

uint8_t sine_wave[0xff];
uint8_t T = 0;

ISR(TIMER0_OVF_vect) {
	OCR0 = sine_wave[T];
	++T;
}

void Timer0_Init() {
	/// Konfiguracja timera0, jako Fast PWM, clk / 64 na porcie B3
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01) | (1 << CS00);
	TIMSK = (1 << TOIE0);
}

int main(void) {
	DDRB |= 0b1000; 		// Ustawia B3, jako wyjscie
	OCR0 = 0;				// Wartość początkowa PWM

	const float length = (2 * 3.1416) / 0xff;  // Dlugosc fali

	/// Wyliczenie wartości sinusa
	short int t = 0;
	while (t < 0xff) {
		sine_wave[t] = sin(length * t) * 128 + 127;
		++t;
	}

	/// Uruchomienie przerwań
	sei();

	/// Petla programu
	while (1) {}
}
