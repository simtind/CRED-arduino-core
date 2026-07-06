/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610


#include <WVariant.h>

// General definitions
// -------------------

// Frequency of the board main oscillator
#define VARIANT_MAINOSC (32768ul)

// Master clock frequency
#define VARIANT_MCK     (48000000ul)

// Pins
// ----

// Number of pins defined in PinDescription array
#ifdef __cplusplus
extern "C" unsigned int PINCOUNT_fn();
#endif
#define PINS_COUNT           (PINCOUNT_fn())
#define NUM_DIGITAL_PINS     (31u)
#define NUM_ANALOG_INPUTS    (8u)
#define NUM_ANALOG_OUTPUTS   (1u)

// Low-level pin register query macros
// -----------------------------------
#define digitalPinToPort(P)      (&(PORT->Group[g_APinDescription[P].ulPort]))
#define digitalPinToBitMask(P)   (1 << g_APinDescription[P].ulPin)
//#define analogInPinToBit(P)    ()
#define portOutputRegister(port) (&(port->OUT.reg))
#define portInputRegister(port)  (&(port->IN.reg))
#define portModeRegister(port)   (&(port->DIR.reg))
#define digitalPinHasPWM(P)      (g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER)

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)


// LEDs
// ----
#define PIN_LED_YELLOW       5
#define PIN_LED_RED          6
#define PIN_LED_GREEN        7
#define LED_BUILTIN PIN_LED_GREEN

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define PIN_SPI_MISO         (4u)
#define PIN_SPI_SCK          (3u)
#define PIN_SPI_MOSI         (2u)
#define PIN_SPI_SS           (5u)
#define PERIPH_SPI           sercom0
#define PAD_SPI_TX           SPI_PAD_0_SCK_1
#define PAD_SPI_RX           SERCOM_RX_PAD_2

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 2

// "Internal" PMIC /RTC  i2c interface
#define PIN_WIRE_SDA        (15u)
#define PIN_WIRE_SCL        (16u)
#define PERIPH_WIRE         sercom1
#define WIRE_IT_HANDLER     SERCOM1_Handler
static const uint8_t SDA = PIN_WIRE2_SDA;
static const uint8_t SCL = PIN_WIRE2_SCL;

// "Internal" PMIC /RTC  i2c interface
#define PIN_WIRE1_SDA         (22u)
#define PIN_WIRE1_SCL         (23u)
#define PERIPH_WIRE1          sercom3
#define WIRE1_IT_HANDLER      SERCOM3_Handler
static const uint8_t SDA1 = PIN_WIRE_SDA;
static const uint8_t SCL1 = PIN_WIRE_SCL;

// USB
// ---
#define PIN_USB_DM          (31ul)
#define PIN_USB_DP          (32ul)

// Serial ports
// ------------
#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"

// Instances of SERCOM
extern SERCOM sercom0;
extern SERCOM sercom1;  // spi
extern SERCOM sercom2;  // spi nina
extern SERCOM sercom3;  // serial2
extern SERCOM sercom4;  // wire
extern SERCOM sercom5;  // serial1

// Serial1
extern Uart Serial1;
#define PIN_SERIAL1_RX       (0ul)
#define PIN_SERIAL1_TX       (1ul)
#define PAD_SERIAL1_TX       (UART_TX_PAD_0)
#define PAD_SERIAL1_RX       (SERCOM_RX_PAD_1)

#endif // __cplusplus



// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         SerialUSB
#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1

// Alias Serial to SerialUSB
#define Serial                      SerialUSB

// LORA interface
#define LORA_SPI         SPI
#define LORA_MOSI        PIN_SPI_MOSI
#define LORA_MISO        PIN_SPI_MISO
#define LORA_SCK         PIN_SPI_SCK
#define LORA_CS          PIN_SPI_CS
#define LORA_INT         6
#define LORA_RESET       7

// PMIC interface
#define PMIC_WIRE        WIRE1
#define PMIC_GPIO1       22
#define PMIC_GPIO2       21
#define PMIC_GPIO3       20
#define PMIC_GPIO4       19

// RTC interface
#define RTC_WIRE         WIRE1
#define RTC_INT          24
#define RTC_RESET        23

// OneWire interfaces
#define ONEWIRE_DATA     13
#define ONEWIRE1_DATA    14
