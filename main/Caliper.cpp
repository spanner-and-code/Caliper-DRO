/**
 * Author: https://github.com/spanner-and-code
 * 
 * Based on the original example here: https://sites.google.com/site/marthalprojects/home/arduino/arduino-reads-digital-caliper by Martin Thalheimer
 * Modified with permission from Martin
 */
 
#include "Caliper.h"
#include <Arduino.h>

namespace Caliper
{
  uint32_t previous = UINT32_MAX;

  /**
   * Setup the caliper pins
   */
  void setup()
  {
    DDRB &= ~(1 << CALIPER_CLOCK_PIN); // Pin mode INPUT
    DDRB &= ~(1 << CALIPER_DATA_PIN); // Pin mode INPUT
  }
  
  /**
   * Read 24 bits from the caliper
   * 
   * @param[out] caliper value
   * @param[out] is it a negative value
   */
  void readCaliper(uint32_t& value, bool& negative)
  {
    for (uint8_t i = 0; i < 23; i++) { // Read 24 bits
      while (PINB & (1 << CALIPER_CLOCK_PIN)) { } // while HIGH
  
      while ((PINB & (1 << CALIPER_CLOCK_PIN)) == 0) { } // while LOW
  
      if ((PINB & (1 << CALIPER_DATA_PIN)) == 0) { // if LOW
        if (i < 20) {
          value |= 1 << i;
        } else if (i == 20) { // If bit 21 is set we're a negative value
          negative = true;
        }
      }
    }
  }
  
  /**
   * Wait for a change in reading from the caliper
   * 
   * @param[in] lambda function that receives the updated value
   */
  void waitForChange(caliperChange onChange)
  {
    while (PINB & (1 << CALIPER_CLOCK_PIN)) { } // while HIGH
  
    uint32_t wait = millis();
  
    while ((PINB & (1 << CALIPER_CLOCK_PIN)) == 0) { } // while LOW
  
    if ((millis() - wait) > 32) {
      uint32_t result = 0;
      bool negative = false;
      readCaliper(result, negative);
  
      if (result != previous) {
        onChange(result, negative);
        previous = result;
      }
    }
  }
}
