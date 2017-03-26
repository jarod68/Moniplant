/*
 * moniplant.cpp
 *
 *  Created on: 19 mars 2017
 *      Author: Matt
 */

// ATmega imports
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

// Arduino imports
#include "Arduino.h"

// Project imports
#include "RGBLed.h"

// Most Arduino boards already have a LED attached to pin 13 on the board itself
#define LED_PIN 13

#define LED_PIN_RED 7
#define LED_PIN_GREEN 8
#define LED_PIN_BLUE 9

static uint16_t unusedPorts[] =
{ 1, 2, 3, 4, 5, 6, 10, 11, 12, 13 };

static RGBLed theLed(LED_PIN_RED, LED_PIN_GREEN, LED_PIN_BLUE, RGBLed::Polarity::LED_HIGH);

// watchdog interrupt
ISR(WDT_vect)
{

	// disable watchdog
	wdt_disable();
}

void sleepWDT(const byte interval)
{

	// deactivate interputs
	cli();

	// reset various flags
	MCUSR = 0;

	// see docs, set WDCE, WDE
	WDTCSR |= 0b00011000;

	// set WDIE, and appropriate delay
	WDTCSR = 0b01000000 | interval;

	wdt_reset();

	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	sei();

	// now goes to Sleep and waits for the interrupt
	sleep_mode()
	;

}

void setup()
{

	// Change clock, freq is atmega328 8MHz / 4 = 31.250 KHz

	// Enable change of the clock prescaler
	CLKPR = _BV(CLKPCE);

	// Divide frequency by 4
	CLKPR = _BV(CLKPS2) | _BV(CLKPS1);

	// Disable some peripherals
	power_timer1_disable();
	power_timer0_disable();
	power_spi_disable();
	power_usart0_disable();
	power_twi_disable();

	// Unused port are out low state
	for (uint8_t i; i < sizeof(unusedPorts); i++)
	{
		pinMode(unusedPorts[i], OUTPUT);
		digitalWrite(unusedPorts[i], LOW);
	}
}

void loop()
{

	int value = analogRead(0);

	RGBLed::Color color;

	if (value < 100)
		color = RGBLed::Color::RED;
	else
		color = RGBLed::Color::GREEN;

	for (uint8_t i = 0; i < 4; i++)
	{

		theLed.setColor(color);
		// 32ms
		sleepWDT(0b000001);

		theLed.setColor(RGBLed::Color::OFF);
		// 32ms
		sleepWDT(0b000001);

		theLed.setColor(color);
		// 32ms
		sleepWDT(0b000001);

		theLed.setColor(RGBLed::Color::OFF);
		// 8 seconds
		sleepWDT(0b100001);
		// 8 seconds
		sleepWDT(0b100001);

		// sleep bit patterns:
		//  1 second:  0b000110
		//  2 seconds: 0b000111
		//  4 seconds: 0b100000
		//  8 seconds: 0b100001
	}

}
