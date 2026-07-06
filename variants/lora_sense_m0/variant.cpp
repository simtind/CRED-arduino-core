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


#include "variant.h"
#include "Arduino.h"

/*
 * Pins descriptions
 */
const PinDescription g_APinDescription[] = {
  // 0/1 - SERCOM/UART
  { PORTB,  3, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL                              ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // RX:   SERCOM5/PAD[1]
  { PORTB,  2, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL                              ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // TX:   SERCOM5/PAD[0]
  // 2..7
  // LORA interface
  { PORTA,  4, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel4,   PWM0_CH0,   TCC0_CH0,     EXTERNAL_INT_NONE }, // MOSI: SERCOM0/PAD[0]
  { PORTA,  5, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel5,   PWM0_CH1,   TCC0_CH1,     EXTERNAL_INT_NONE }, // SCK:  SERCOM0/PAD[1]
  { PORTA,  6, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL                                ), ADC_Channel6,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MISO: SERCOM0/PAD[2]
  { PORTA,  7, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // CS:   SERCOM0/PAD[3]
  { PORTA,  8, PIO_DIGITAL,    (PIN_ATTR_DIGITAL                                ), ADC_Channel16,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NMI  }, // INT:  NMI
  { PORTB,  9, PIO_DIGITAL,    (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // RESET
  // 8..12
  // LEDs / Buttons
  { PORTA,  2, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG /*DAC*/        ), ADC_Channel0,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2  }, // BTN1
  { PORTA,  3, PIO_DIGITAL,   (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3  }, // BTN2, DAC/VREFP
  { PORTA,  9, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel7,   PWM1_CH1,   TCC1_CH1,     EXTERNAL_INT_9  }, // LED1
  { PORTA, 10, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM5_CH0,   TC5_CH0,      EXTERNAL_INT_10 }, // LED2
  { PORTA, 11, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM5_CH1,   TC5_CH1,      EXTERNAL_INT_11 }, // LED3
  // 13..14
  // 1-Wire
  { PORTA, 12, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM2_CH0,   TCC2_CH0,     EXTERNAL_INT_12  },
  { PORTA, 13, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM2_CH1,   TCC2_CH1,     EXTERNAL_INT_13  },
  // 15..18
  // I2C  buses
  { PORTA, 16, PIO_SERCOM,    (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM2_CH0,   TCC2_CH0,     EXTERNAL_INT_0    }, // QWIIC I2C SDA SERCOM1/PAD[0]
  { PORTA, 17, PIO_SERCOM,    (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1    }, // QWIIC I2C SCL SERCOM1/PAD[1]
  { PORTA, 22, PIO_SERCOM,    (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // INT I2C SDA   SERCOM3/PAD[0]   
  { PORTA, 23, PIO_SERCOM,    (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // INT I2C SCL   SERCOM3/PAD[1]
  // 19..22
  // PMIC
  { PORTA, 18, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM3_CH0,   TC3_CH0,      EXTERNAL_INT_2    }, // PMIC GPIO4
  { PORTA, 19, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM3_CH1,   TC3_CH1,      EXTERNAL_INT_3    }, // PMIC GPIO3
  { PORTA, 20, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH6,   TCC0_CH6,     EXTERNAL_INT_4    }, // PMIC GPIO2
  { PORTA, 21, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH7,   TCC0_CH7,     EXTERNAL_INT_5    }, // PMIC GPIO1
  // 23..24
  // RTC
  { PORTA, 14, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM3_CH0,   TC3_CH0,      EXTERNAL_INT_14   }, // RTC_RESET
  { PORTA, 15, PIO_DIGITAL,   (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM3_CH1,   TC3_CH1,      EXTERNAL_INT_15   }, // RTC_INT
/*
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  NANO Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 |            |        USB       |        |                 |        |     |     |     |     |         |         |        |        |          |          |
 | 29         |                  |  PA22  |                 |  *06   |     |     | X10 |     |   3/00  |   5/00  |* TC4/0 | TCC0/4 |          | GCLK_IO6 |
 | 30         |                  |  PA23  |                 |  *07   |     |     | X11 |     |   3/01  |   5/01  |* TC4/1 | TCC0/5 | USB/SOF  | GCLK_IO7 |
 | 31         |                  |  PA24  | USB_N           |   12   |     |     |     |     |   3/02  |   5/02  |  TC5/0 | TCC1/2 | USB/DM   |          |
 | 32         |                  |  PA25  | USB_P           |   13   |     |     |     |     |   3/03  |   5/03  |  TC5/1 | TCC1/3 | USB/DP   |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
*/

  // 25..26 - USB
  { PORTA, 24, PIO_COM, PIN_ATTR_NONE                                        , No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DM
  { PORTA, 25, PIO_COM, PIN_ATTR_NONE                                        , No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DP
/*
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  NANO Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 |            | 32768Hz Crystal  |        |                 |        |     |     |     |     |         |         |        |        |          |          |
 | 34         |                  |  PA00  | XIN32           |   00   |     |     |     |     |         |   1/00  | TCC2/0 |        |          |          |
 | 35         |                  |  PA01  | XOUT32          |   01   |     |     |     |     |         |   1/01  | TCC2/1 |        |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 | 33         | AREF             |  PA03  |                 |   03   |  01 |     | Y01 |     |         |         |        |        |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 | 34         |                  |  PA30  |                 |   10   |     |     |     |     |         |   1/00  |        |        |   SWCLK  |          |
 | 35         |                  |  PA31  |                 |   11   |     |     |     |     |         |   1/03  |        |        |   SWDIO  |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 */
  { PORTA,  0, PIO_DIGITAL,    (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  1, PIO_DIGITAL,    (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
} ;

extern "C" {
    unsigned int PINCOUNT_fn() {
        return (sizeof(g_APinDescription) / sizeof(g_APinDescription[0]));
    }
}

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 } ;

void initVariant() {
  
}

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
SERCOM sercom4( SERCOM4 ) ;
SERCOM sercom5( SERCOM5 ) ;

Uart Serial1( &sercom5, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX ) ;

void SERCOM5_Handler()
{
  Serial1.IrqHandler();
}


