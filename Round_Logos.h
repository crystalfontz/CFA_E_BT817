#ifndef __ROUND_LOGOS_H__
#define __ROUND_LOGOS_H__

//============================================================================
// Crystalfontz America, Inc. example firmware for:
// https://www.crystalfontz.com/products/eve-accelerated-tft-displays.php
//===========================================================================
// See LICENSE.md for software licensing information.
//===========================================================================

#include <Arduino.h>

//compressed logo
#define LOGO_SIZE_ARGB2   (2316)
#define LOGO_WIDTH_ARGB2  (320)
#define LOGO_HEIGHT_ARGB2 (320)
//original logo
#define LOGO_SIZE_PNG     (6849)

#if (LOGO_DEMO == 1) && (LOGO_PNG_0_ARGB2_1 == 1)
extern const uint8_t CFA_E_ARGB2_LOGO[LOGO_SIZE_ARGB2] PROGMEM;
#endif
#if (LOGO_DEMO == 1) && (LOGO_PNG_0_ARGB2_1 == 0)
extern const uint8_t CFA_E_PNG_LOGO[LOGO_SIZE_PNG] PROGMEM;
#endif

#endif
