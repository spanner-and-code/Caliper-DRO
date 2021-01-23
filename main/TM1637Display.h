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

#ifndef TM1637DISPLAY_H
#define TM1637DISPLAY_H

#include <inttypes.h>

extern const uint8_t DISPLAY_CLOCK_PIN;
extern const uint8_t DISPLAY_DIO_PIN;

namespace TM1637
{
  void setup();
  void showValue(uint32_t value, bool negative);
}

#endif // TM1637DISPLAY_H
