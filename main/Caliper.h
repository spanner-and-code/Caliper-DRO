/**
 * Author: https://github.com/spanner-and-code
 * 
 * Based on the original example here: https://sites.google.com/site/marthalprojects/home/arduino/arduino-reads-digital-caliper by Martin Thalheimer
 * Modified with permission from Martin
 */

#ifndef CALIPER_H
#define CALIPER_H

#include <inttypes.h>

extern const uint8_t CALIPER_CLOCK_PIN;
extern const uint8_t CALIPER_DATA_PIN;

namespace Caliper
{
  typedef void (*caliperChange)(uint32_t result, bool negative);

  void setup();
  void waitForChange(caliperChange onChange);
}

#endif // CALIPER_H
