// // #include "LEDHandler.h"

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// LEDHandler<LEDTYPE, PIN>::LEDHandler(uint16_t numLeds) : m_NumLeds(numLeds)
// {
// 	leds = new CRGB[numLeds]();
// 	FastLED.addLeds<LEDTYPE, PIN>(leds, numLeds);
// }

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// LEDHandler<LEDTYPE, PIN>::~LEDHandler()
// {
// 	delete[] leds;
// }

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// CRGB &LEDHandler<LEDTYPE, PIN>::get(unsigned int index)
// {
// 	return leds[index % m_NumLeds];
// }

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// void LEDHandler<LEDTYPE, PIN>::set(unsigned int index, CRGB c)
// {
// 	leds[index % m_NumLeds] = c;
// 	// leds[index % m_NumLeds].r = c.g;
// 	// leds[index % m_NumLeds].g = c.r;
// 	// leds[index % m_NumLeds].b = c.b;
// }

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// void LEDHandler<LEDTYPE, PIN>::setAll(CRGB c)
// {
// 	for (int i = 0; i < m_NumLeds; i++)
// 	{
// 		set(i, c);
// 	}
// }

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// void LEDHandler<LEDTYPE, PIN>::setAll(byte *data, int size)
// {
// 	if (size < m_NumLeds * 3)
// 		return;
// 	for (int i = 0; i < m_NumLeds * 3; i += 3)
// 	{
// 		set(i, CRGB(data[i], data[i + 1], data[i + 2]));
// 	}
// }

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// void LEDHandler<LEDTYPE, PIN>::brightness(uint8_t value)
// {
// 	FastLED.setBrightness(value);
// }

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// void LEDHandler<LEDTYPE, PIN>::reset()
// {
// 	setAll(CRGB(0, 0, 0));
// 	show();
// }

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// void LEDHandler<LEDTYPE, PIN>::show()
// {
// 	FastLED.show();
// }

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// void LEDHandler<LEDTYPE, PIN>::animateWifi(bool reset)
// {
// 	static int width = 8;
// 	static int iterator = 0;
// 	iterator = reset ? 0 : iterator + 1;

// 	leds[(iterator - 1) % m_NumLeds] = CRGB::Black;
// 	for (int i = 0; i < width; i++)
// 	{
// 		set((iterator + i) % m_NumLeds, CRGB::Green);
// 	}

// 	show();
// }

// template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
// void LEDHandler<LEDTYPE, PIN>::wifiConnected()
// {
// 	for (int i = 0; i < 7; i++)
// 	{
// 		setAll(CRGB::Green);
// 		show();
// 		delay(80);
// 		reset();
// 		delay(80);
// 	}
// }
