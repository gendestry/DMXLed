#include "LEDHandler.h"

LEDHandler::LEDHandler()
{
	leds = new CRGB[NUM_LEDS]();
	FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
}

LEDHandler::~LEDHandler()
{
	delete[] leds;
}

CRGB &LEDHandler::get(unsigned int index)
{
	return leds[index];
}

void LEDHandler::set(unsigned int index, CRGB c)
{
	leds[index % NUM_LEDS].r = c.g;
	leds[index % NUM_LEDS].g = c.r;
	leds[index % NUM_LEDS].b = c.b;
}

void LEDHandler::setAll(CRGB c)
{
	for (int i = 0; i < NUM_LEDS; i++)
	{
		set(i, c);
	}
}

void LEDHandler::setAll(byte *data, int size)
{
	if (size < NUM_LEDS * 3)
		return;
	for (int i = 0; i < NUM_LEDS * 3; i++)
	{
		set(i, CRGB(data[i], data[i], data[i]));
	}
}

void LEDHandler::brightness(uint8_t value)
{
	FastLED.setBrightness(value);
}

void LEDHandler::reset()
{
	setAll(CRGB(0, 0, 0));
	show();
}

void LEDHandler::show()
{
	FastLED.show();
}

void LEDHandler::animateWifi(bool reset)
{
	static int width = 8;
	static int iterator = 0;
	iterator = reset ? 0 : iterator + 1;

	leds[(iterator - 1) % NUM_LEDS] = CRGB::Black;
	for (int i = 0; i < width; i++)
	{
		set((iterator + i) % NUM_LEDS, CRGB::Green);
	}

	show();
}

void LEDHandler::wifiConnected()
{
	for (int i = 0; i < 7; i++)
	{
		setAll(CRGB::Green);
		show();
		delay(80);
		reset();
		delay(80);
	}
}