# A simple DMX LED controller
Built in c++ using the Arduino framework.

## Porject composition
The project uses two libraries: 
 - **FastLED** for led control
 - **esp_dmx** for dmx interfacing

The hardware used is a ESP32 microcontroller. It might work with others.

For the DMX controller you can pick anything, I went with *MagicDMX Full* from ChamSys.

## Usage
Connect the leds to a pwm pin (23 in our case).

XLR must be connected to a serial interface. Since ESP32 has 2 serial interfaces, we will use the second one,
because we can use the first one for debugging. In ESP32's case that's pins *16* and *17* (we just care about pin 16).

We connect ESP32's gnd with XLR's pin 1 (which is ground) and ESP32's pin 16 to XLR's pin 3.
That is it.

## TODO
Currently if you disconnect the DMX does not reconnect and you have to restart the ESP32 and potentialy the DMX interface aswell.
