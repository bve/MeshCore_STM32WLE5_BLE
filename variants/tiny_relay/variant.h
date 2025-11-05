#pragma once

#include <variant_RAK3172_MODULE.h>

#define PB3                     0
#define PA15                    1
#define PA2                     2
#define PA3                     3
#define PA11                    PIN_A1
#define PA12                    PIN_A2
#define PA13                    PIN_A3
#define PA14                    PIN_A4
#define PA0                     8
#define PA1                     9
#define PA4                     10
#define PA5                     11
#define PA6                     12
#define PA7                     13
#define PA8                     14
#define PA9                     15
#define PA10                    16
#define PB0                     17
#define PB2                     PIN_A0
#define PB4                     19
#define PB5                     20
#define PB6                     21
#define PB7                     22
#define PB8                     23
#define PB12                    24
#define PC13                    25
#define PH3                     26
#define PC14                    27     // OSC32-IN
#define PC15                    28     // OSC32-OUT

//#define FORMAT_FS
#define LORAWAN_RFSWITCH_PINS PA8, PC13

//#define LORAWAN_RFSWITCH_PINS           PB8, PC13
#define LORAWAN_RFSWITCH_PIN_COUNT      2
#define LORAWAN_RFSWITCH_OFF_VALUES     LOW, LOW
#define LORAWAN_RFSWITCH_RX_VALUES      HIGH, LOW
#define LORAWAN_RFSWITCH_RFO_LP_VALUES  LOW, HIGH
#define LORAWAN_RFSWITCH_RFO_HP_VALUES  LOW, HIGH

#undef RNG
