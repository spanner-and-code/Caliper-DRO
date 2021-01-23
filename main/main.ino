/**
 * Author: https://github.com/spanner-and-code
 * 
 * Digital caliper code based off the example here https://sites.google.com/site/marthalprojects/home/arduino/arduino-reads-digital-caliper
 * Display uses modified version of https://github.com/avishorp/TM1637
 */

#include "Caliper.h"
#include "TM1637Display.h"

// Caliper pins
const uint8_t CALIPER_CLOCK_PIN = 3;
const uint8_t CALIPER_DATA_PIN = 4;

// Display pins
const uint8_t DISPLAY_CLOCK_PIN = 0;
const uint8_t DISPLAY_DIO_PIN = 1;

/**
 * Setup
 */
void setup()
{
  // Setup the caliper inputs
  Caliper::setup();

  // Setup the display
  TM1637::setup();
}

/**
 * Loop
 */
void loop()
{
  // Wait for a new value from the caliper 
  Caliper::waitForChange([](uint32_t result, bool negative) {
    // New value so update the display
    TM1637::showValue(result, negative);
  });
}
