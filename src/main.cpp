#include <Arduino.h>
#include <esp_dmx.h>
#include <FastLED.h>
// #include "LEDHandler.h"

int transmitPin = 17;
int receivePin = 16;
int enablePin = 21;

dmx_port_t dmxPort = 1;
byte data[DMX_PACKET_SIZE];

bool dmxIsConnected = false;
unsigned long lastUpdate = millis();

// LEDHandler ledHandler;
#define NUM_LEDS 34
CRGB *leds = new CRGB[NUM_LEDS];

void setup()
{
  Serial.begin(9600);

  FastLED.addLeds<WS2811, 23>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255, 0, 0);
  }

  FastLED.show();
  sleep(5);
  // ledHandler.reset();
  // ledHandler.brightness(255);
  // ledHandler.wifiConnected();

  /* Now we will install the DMX driver! We'll tell it which DMX port to use,
    what device configuration to use, and what DMX personalities it should have.
    If you aren't sure which configuration to use, you can use the macros
    `DMX_CONFIG_DEFAULT` to set the configuration to its default settings.
    This device is being setup as a DMX responder so it is likely that it should
    respond to DMX commands. It will need at least one DMX personality. Since
    this is an example, we will use a default personality which only uses 1 DMX
    slot in its footprint. */
  dmx_config_t config = DMX_CONFIG_DEFAULT;
  dmx_personality_t personalities[] = {
      {3, "RGB"}};
  int personality_count = 1;
  dmx_driver_install(dmxPort, &config, personalities, personality_count);

  /* Now set the DMX hardware pins to the pins that we want to use and setup
    will be complete! */
  dmx_set_pin(dmxPort, transmitPin, receivePin, enablePin);
}

void loop()
{
  dmx_packet_t packet;

  if (dmx_receive(dmxPort, &packet, DMX_TIMEOUT_TICK))
  {
    /* If this code gets called, it means we've received DMX data! */

    unsigned long now = millis();

    /* We should check to make sure that there weren't any DMX errors. */
    if (!packet.err)
    {
      /* If this is the first DMX data we've received, lets log it! */
      if (!dmxIsConnected)
      {
        Serial.println("DMX is connected!");
        dmxIsConnected = true;
      }

      dmx_read(dmxPort, data, packet.size);
      for (int i = 0; i < NUM_LEDS; i++)
      {
        unsigned int index = i * 3;
        leds[i].r = data[index + 1];
        leds[i].g = data[index + 2];
        leds[i].b = data[index + 3];
      }

      FastLED.show();
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