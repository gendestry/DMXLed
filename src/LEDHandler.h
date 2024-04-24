#pragma once
#include <FastLED.h>

template <template <uint8_t DATA_PIN, EOrder RGB_ORDER> class LEDTYPE, uint8_t PIN>
class LEDHandler
{
public:
    LEDHandler(uint16_t numLeds) : m_NumLeds(numLeds)
    {
        leds = new CRGB[numLeds]();
        FastLED.addLeds<LEDTYPE, PIN>(leds, numLeds);
    }

    ~LEDHandler()
    {
        delete[] leds;
    }

    inline CRGB *getLeds() { return leds; }

    CRGB &get(unsigned int index)
    {
        return leds[index % m_NumLeds];
    }

    CRGB &operator[](unsigned int index) { return get(index); }

    void set(unsigned int index, CRGB c)
    {
        leds[index % m_NumLeds] = c;
        // leds[index % m_NumLeds].r = c.g;
        // leds[index % m_NumLeds].g = c.r;
        // leds[index % m_NumLeds].b = c.b;
    }

    void setAll(CRGB c)
    {
        for (int i = 0; i < m_NumLeds; i++)
        {
            set(i, c);
        }
    }

    void setAll(byte *data, int size)
    {
        if (size < m_NumLeds * 3)
            return;

        for (int i = 0; i < m_NumLeds * 3; i += 3)
        {
            set(i, CRGB(data[i], data[i + 1], data[i + 2]));
        }
    }

    inline uint16_t getNumLeds() const { return m_NumLeds; }

    inline void brightness(uint8_t value)
    {
        FastLED.setBrightness(value);
    }

    void reset()
    {
        setAll(CRGB(0, 0, 0));
        show();
    }

    inline void show()
    {
        FastLED.show();
    }

    // void artnetCallback(const uint8_t *data, const uint16_t size);

    void animateWifi(bool reset = false)
    {
        static int width = 8;
        static int iterator = 0;
        iterator = reset ? 0 : iterator + 1;

        leds[(iterator - 1) % m_NumLeds] = CRGB::Black;
        for (int i = 0; i < width; i++)
        {
            set((iterator + i) % m_NumLeds, CRGB::Green);
        }

        show();
    }

    void wifiConnected()
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

private:
    uint16_t m_NumLeds;
    uint8_t m_DataPin = PIN;

    CRGB *leds;
};