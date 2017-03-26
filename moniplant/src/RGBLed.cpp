/*
 * RGBLed.cpp
 *
 *  Created on: 19 mars 2017
 *      Author: Matt
 */

#include "RGBLed.h"
#include "Arduino.h"

RGBLed::RGBLed(uint8_t _redPin, uint8_t _greenPin, uint8_t _bluePin, Polarity _polarity) :
		redPin(_redPin), greenPin(_greenPin), bluePin(_bluePin), polarity(_polarity)
{

	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);

}

RGBLed::~RGBLed()
{

}

const RGBLed::Polarity RGBLed::getLowPolarity()
{

	if (this->polarity == Polarity::LED_HIGH)
		return Polarity::LED_LOW;

	return Polarity::LED_HIGH;
}

const RGBLed::Polarity RGBLed::getHighPolarity()
{

	if (this->polarity == Polarity::LED_HIGH)
		return Polarity::LED_HIGH;

	return Polarity::LED_LOW;

}

void RGBLed::setColor(Color _color)
{

	switch (_color)
	{

	case Color::BLUE:
		digitalWrite(redPin, getLowPolarity());
		digitalWrite(greenPin, getLowPolarity());
		digitalWrite(bluePin, getHighPolarity());
		break;

	case Color::CYAN:
		digitalWrite(redPin, getLowPolarity());
		digitalWrite(greenPin, getHighPolarity());
		digitalWrite(bluePin, getHighPolarity());
		break;

	case Color::GREEN:
		digitalWrite(redPin, getLowPolarity());
		digitalWrite(greenPin, getHighPolarity());
		digitalWrite(bluePin, getLowPolarity());
		break;

	case Color::MAGENTA:
		digitalWrite(redPin, getHighPolarity());
		digitalWrite(greenPin, getLowPolarity());
		digitalWrite(bluePin, getHighPolarity());
		break;

	case Color::OFF:
		digitalWrite(redPin, getLowPolarity());
		digitalWrite(greenPin, getLowPolarity());
		digitalWrite(bluePin, getLowPolarity());
		break;

	case Color::RED:
		digitalWrite(redPin, getHighPolarity());
		digitalWrite(greenPin, getLowPolarity());
		digitalWrite(bluePin, getLowPolarity());
		break;

	case Color::WHITE:
		digitalWrite(redPin, getHighPolarity());
		digitalWrite(greenPin, getHighPolarity());
		digitalWrite(bluePin, getHighPolarity());
		break;

	case Color::YELLOW:
		digitalWrite(redPin, getHighPolarity());
		digitalWrite(greenPin, getHighPolarity());
		digitalWrite(bluePin, getLowPolarity());
		break;

	default:
		break;
	}

}
