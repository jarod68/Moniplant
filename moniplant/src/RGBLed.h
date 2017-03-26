/*
 * RGBLed.h
 *
 *  Created on: 19 mars 2017
 *      Author: Matt
 */
#pragma once

#ifndef __RGBLED_H_
#define __RGBLED_H_

#include <stdint.h>

/**
 * RGBLed class declaration. This class intend to control an RGB LED.
 */
class RGBLed
{

public:

	/**
	 * Enumeration for colors
	 */
	enum Color
	{
		OFF, RED, GREEN, BLUE, WHITE, YELLOW, CYAN, MAGENTA,
	};

	/**
	 * Enumeration for LED polarity (LOW is for common anode, HIGH for common cathode)
	 */
	enum Polarity
	{
		LED_LOW = 0x0, LED_HIGH = 0x1
	};

public:
	/**
	 * Constructor, specified pin would be set as output with the wanted polarity
	 */
	RGBLed(uint8_t _redPin, uint8_t _greenPin, uint8_t _bluePin, Polarity _polarity = Polarity::LED_HIGH);

	/**
	 * Destructor
	 */
	virtual ~RGBLed();

	/**
	 * Set the LED in the specified color
	 */
	void setColor(Color _color);

private:
	/**
	 * Get the value to set the port to LOW depending on the LED polarity set in constructor
	 */
	const RGBLed::Polarity getLowPolarity();

	/**
	 * Get the value to set the port to HIGH depending on the LED polarity set in constructor
	 */
	const RGBLed::Polarity getHighPolarity();

private:
	const uint8_t redPin;
	const uint8_t greenPin;
	const uint8_t bluePin;
	const uint8_t polarity;

};

#endif /* SRC_RGBLED_H_ */
