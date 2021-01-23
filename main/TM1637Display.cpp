/**
 * Author: avishorp@gmail.com
 * Site: https://github.com/avishorp/TM1637
 *
 * Modified by: https://github.com/spanner-and-code
 * Refactored, changed to support 6 digit TM1637 and cut down to minimal needs
 * Can show a signed value between -999.99 and 999.99
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "TM1637Display.h"
#include <Arduino.h>

namespace TM1637
{
  /** 
   * Display digit segments
   */
  const uint8_t digitToSegment[] PROGMEM = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
  };

  /**
   * Setup the display pins
   */
  void setup()
  {
    DDRB &= ~(1 << DISPLAY_CLOCK_PIN); // Pin mode INPUT
    DDRB &= ~(1 << DISPLAY_DIO_PIN); // Pin mode INPUT
    PORTB &= ~(1 << DISPLAY_CLOCK_PIN); // Set to LOW
    PORTB &= ~(1 << DISPLAY_DIO_PIN); // Set to LOW
  }
  
  /**
   * Delay for display commands
   */
  void delay()
  {
    delayMicroseconds(100);
  }
  
  /**
   * Start display command
   */
  void start()
  {
    DDRB |= (1 << DISPLAY_DIO_PIN); // Pin mode OUTPUT
    delay();
  }
  
  /**
   * Stop display command
   */
  void stop()
  {
    DDRB |= (1 << DISPLAY_DIO_PIN); // Pin mode OUTPUT
    delay();
    DDRB &= ~(1 << DISPLAY_CLOCK_PIN); // Pin mode INPUT
    delay();
    DDRB &= ~(1 << DISPLAY_DIO_PIN); // Pin mode INPUT
    delay();
  }
  
  /**
   * Write byte to display
   * 
   * @param data[in] byte to write
   */
  void writeByte(uint8_t b)
  {
    for (uint8_t i = 0; i < 8; i++) {
      DDRB |= (1 << DISPLAY_CLOCK_PIN); // Pin mode OUTPUT
      delay();
  
      if (b & 0x01) {
        DDRB &= ~(1 << DISPLAY_DIO_PIN); // Pin mode INPUT
      } else {
        DDRB |= (1 << DISPLAY_DIO_PIN); // Pin mode OUTPUT
      }
      delay();
  
      DDRB &= ~(1 << DISPLAY_CLOCK_PIN); // Pin mode INPUT
      delay();
      b >>= 1;
    }
  
    DDRB |= (1 << DISPLAY_CLOCK_PIN); // Pin mode OUTPUT
    DDRB &= ~(1 << DISPLAY_DIO_PIN); // Pin mode INPUT
    delay();
  
    DDRB &= ~(1 << DISPLAY_CLOCK_PIN); // Pin mode INPUT
    delay();
  
    if ((PINB & (1 << DISPLAY_DIO_PIN)) == 0) { // if LOW
      DDRB |= (1 << DISPLAY_CLOCK_PIN); // Pin mode OUTPUT
    }
    delay();
    
    DDRB |= (1 << DISPLAY_CLOCK_PIN); // Pin mode OUTPUT
    delay();
  }
  
  /**
   * Update the value on the display
   * 
   * @param value[in] new value to display
   * @param negative[in] is the value negative
   */
  void showValue(uint32_t value, bool negative)
  {
    start();
    writeByte(0x40); // Write data to display register command
    stop();
  
    start();
    writeByte(0xC3); // Auto address command
  
    uint8_t digits[] = { 0, 0, 0, 0, 0, 0 }; // 6 Zero's to reset display
    uint8_t length;
  
    // How many digits
    if (value >= 10000) {
      length = 5;
    } else if (value >= 1000) {
      length = 4;
    } else { // Minimum of 3
      length = 3;
    }
  
    // Map digits from `value` to the `digits` array
    for (uint8_t pos = 0; pos < length; pos++) {
      digits[pos] = pgm_read_byte(&digitToSegment[value % 10]);
      value /= 10;
    }
  
    digits[2] |= 0x80; // We always want the decimal dot on digit 3
  
    // If we're negative then add it to the end
    if (negative) {
      digits[length] = 0x40;
    }
  
    // Write the digits to the display
    for (int b = 0; b < 6; b++) {
      writeByte(digits[b]);
    }
    
    stop();
  
    start();
    writeByte(0x8E); // Display on and 13/16 Brightness
    stop();
  }
}
