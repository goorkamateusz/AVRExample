#ifndef __AVR_ATmega32__
#define __AVR_ATmega32__
#endif

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	// Konfiguracja timera0, jako Fast PWM
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00);
	DDRB  = 0b00111111;  // ustawia B6 i B7, jako wyjście, B3 jako wejście
	PORTB = 0b11000000;  // ustawia na B6 i B7 stan wysoki
	OCR0  = 125;         // Wartość początkowa PWM

	while (1) {
		if (!(PINB & 0b10000000)) {
			if (OCR0 != 0) --OCR0;
			_delay_ms(20);
		}

		if (!(PINB & 0b01000000)) {
			if (OCR0 != 255) ++OCR0;
			_delay_ms(20);
		}
	}
}
