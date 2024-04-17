#pragma once
#include <FastLED.h>

#define NUM_LEDS 143
#define DATA_PIN 23

class LEDHandler
{
public:
	static int id;

	LEDHandler();
	~LEDHandler();

	inline CRGB *getLeds() { return leds; }
	CRGB &get(unsigned int index);
	void set(unsigned int index, CRGB c);
	void setAll(CRGB c);
	void setAll(byte *data, int size);

	void brightness(uint8_t value);
	void reset();
	void show();

	void artnetCallback(const uint8_t *data, const uint16_t size);

	void animateWifi(bool reset = false);
	void wifiConnected();

private:
	CRGB *leds;
};