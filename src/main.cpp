#include <Arduino.h>
#include <esp_dmx.h>
#include "LEDHandler.h"

int transmitPin = 17;
int receivePin = 16;
int enablePin = 21;

dmx_port_t dmxPort = 1;
byte data[DMX_PACKET_SIZE];

bool dmxIsConnected = false;
unsigned long lastUpdate = millis();

LEDHandler<WS2811, 23> leds(34);
// LEDHandler<WS2812B, 23> leds(100);

void setup()
{
    Serial.begin(9600);
    // led setup
    leds.setAll(CRGB(255, 0, 0));
    leds.show();
    sleep(2);

    // dmx setup
    dmx_config_t config = DMX_CONFIG_DEFAULT;
    dmx_personality_t personalities[] = {{3, "RGB"}};
    int personality_count = 1;
    dmx_driver_install(dmxPort, &config, personalities, personality_count);
    dmx_set_pin(dmxPort, transmitPin, receivePin, enablePin);
}

void loop()
{
    dmx_packet_t packet;

    if (dmx_receive(dmxPort, &packet, DMX_TIMEOUT_TICK))
    {
        unsigned long now = millis();

        if (!packet.err)
        {
            /* If this is the first DMX data we've received, lets log it! */
            if (!dmxIsConnected)
            {
                Serial.println("DMX is connected!");
                dmxIsConnected = true;
            }

            dmx_read(dmxPort, data, packet.size);
            for (int i = 0; i < leds.getNumLeds(); i++)
            {
                unsigned int index = i * 3;
                leds[i].r = data[index + 1];
                leds[i].g = data[index + 2];
                leds[i].b = data[index + 3];
            }

            leds.show();
            // ledHandler.setAll(data + 1, packet.size);
            // ledHandler.show();

            // if (now - lastUpdate > 10000)
            // {
            //   /* Print the received start code - it's usually 0. */
            //   for (int i = 0; i < packet.size; i++)
            //   {
            //     if (i % 16 == 0)
            //       Serial.println();
            //     Serial.printf("0x%02X ", data[i]);
            //   }
            //   lastUpdate = now;
            // }
        }
        else
        {
            Serial.println("A DMX error occurred.");
        }
    }
    else if (dmxIsConnected)
    {
        /* If DMX times out after having been connected, it likely means that the
        DMX cable was unplugged. When that happens in this example sketch, we'll
        uninstall the DMX driver. */
        Serial.println("DMX was disconnected.");
        dmx_driver_delete(dmxPort);

        /* Stop the program. */
        while (true)
            yield();
    }
}