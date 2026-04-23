#ifndef __CFA_E_DEFINES_H__
#define __CFA_E_DEFINES_H__

//============================================================================
// Crystalfontz America, Inc. example firmware for:
// https://www.crystalfontz.com/products/eve-accelerated-tft-displays.php
//===========================================================================
// See LICENSE.md for software licensing information.
//===========================================================================
// clang-format off

// First we need to define the particular EVE chip that we have.
#define EVE_DEVICE (BT817)

// Now that the device is set, we can include the master (monster) EVE definitions header:
#include "EVE_defines.h"

//============================================================================
// SELECT YOUR DISPLAY — uncomment exactly one line
//============================================================================
// #include "DISPLAY_CFA480480E0040TN.h"      // 4"    480x480  non-touch
// #include "DISPLAY_CFA480480E0040TW.h"      // 4"    480x480  capacitive touch
// #include "DISPLAY_CFA480272E0043SN.h"      // 4.3"  480x272  non-touch
// #include "DISPLAY_CFA480272E0043SR.h"      // 4.3"  480x272  resistive touch
// #include "DISPLAY_CFA480272E0043SC.h"      // 4.3"  480x272  capacitive touch
// #include "DISPLAY_CFA800480E0043SN.h"      // 4.3"  800x480  non-touch
// #include "DISPLAY_CFA800480E0043SR.h"      // 4.3"  800x480  resistive touch
// #include "DISPLAY_CFA800480E0043SC.h"      // 4.3"  800x480  capacitive touch
// #include "DISPLAY_CFA800480E3050SN.h"      // 5.0"  800x480  non-touch
// #include "DISPLAY_CFA800480E3050SR.h"      // 5.0"  800x480  resistive touch
#include "DISPLAY_CFA800480E3050SC.h"      // 5.0"  800x480  capacitive touch
// #include "DISPLAY_CFA800480E3050SW.h"      // 5.0"  800x480  cap. touch, overhang glass
// #include "DISPLAY_CFAF1024600B0070SCA1.h"  // 7.0"  1024x600 capacitive touch


//============================================================================
// DEMO SELECTION
//============================================================================
// There is not enough RAM_G space to hold all of the scrolling background,
// logo, audio, and blue marble at the same time. However with the BT817,
// we can load elements into the flash from a uSD attached to the Arduino.
// Once the data files have been programmed to the flash, the uSD
// card is not needed anymore. Elements could also be loaded into the
// flash by using some PC host and the Eve Asset Builder tools provided by
// Bridgetek. Some elements can then be displayed directly from flash, other
// elements (notably the rotating blue marble) need to be copied to the
// faster RAM_G before displaying them.
//
// You would want to set this once, with the uSD card loaded with the
// appropriate files to program those images into the flash:
// bluemarb.a8z      12,665
// splash.a8z       135,852
// cloud.a8z        132,455
// Ice_400.avi   12,882,892

// If demos are enabled the require extra files, enabling this will first copy
// the data files to the flash.
#define PROGRAM_FLASH_FROM_USD	(0) // 0=data is in flash, 1=copy data from microsd to flash

// Demo selection (choose one or more)
#define BMP_DEMO					(0)			// Images must already be programmed into flash by using PROGRAM_FLASH_FROM_USD
#define BMP_SCROLL				(0)			// 1=scrolling background (cloud.a8z), 0=static image (splash.a8z)
#define SOUND_DEMO				(0)			// Uses uSD
#define 	SOUND_VOICE				(0)		// 1=VOI_8K.RAW, 0=MUS_8K.RAW
#define 	SOUND_PLAY_TIMES	(0)
#define LOGO_DEMO 				(1) 		// Spinning logo (the PNG or ARGB image data is stored in the Seeeduino's flash)
#define 	LOGO_PNG_0_ARGB2_1 (1)	// Compressed ARGB is 5408 bytes smaller
#define BOUNCE_DEMO 			(1)			// Ball-and-rubber-band demo.
#define MARBLE_DEMO 			(0)			// Marble must already be programmed into flash by using PROGRAM_FLASH_FROM_USD
#define TOUCH_DEMO				(1)			// Simple touch demo
#define VIDEO_DEMO				(0)			// Video must already be programmed into flash by using PROGRAM_FLASH_FROM_USD

//============================================================================
// SET THE DEBUGGING OUTPUT LEVEL
//============================================================================
// DEBUG_NONE   (0K flash, serial not used)
// DEBUG_STATUS (1.4K ~ 2.5K flash)
// DEBUG_GEEK   (6.4K ~ 7K flash)
// the debugging output is sent to the Arduino serial output which can be
// viewed in the the Arduino IDE console (Ctrl+Shift+M).
#define DEBUG_LEVEL (DEBUG_STATUS)

//============================================================================
// SET FLASH CONFIGURATION (if used)
//============================================================================
//*** WARNING: PLACEHOLDER VALUES — MUST BE UPDATED FOR YOUR HARDWARE ***
// Build once with PROGRAM_FLASH_FROM_USD=1 and copy the values printed to
// the serial console. The values below are stale examples and will not work.
#if (PROGRAM_FLASH_FROM_USD == 1)
#define FLASH_SECTOR_MARBLE (1UL)
#define FLASH_LENGTH_MARBLE (1409867791UL) // sectors: 344206
#define FLASH_SECTOR_SPLASH (1UL)
#define FLASH_LENGTH_SPLASH (96000UL) // sectors: 23
#define FLASH_SECTOR_CLOUDS (25UL)
#define FLASH_LENGTH_CLOUDS (-2147450880UL) // sectors: 524296
#define FLASH_SECTOR_ICE_FPV_512x300 (25UL)
#define FLASH_LENGTH_ICE_FPV_512x300 (4096UL) // sectors: 1
// Total sectors = 4096, free sectors = 4070
// Total flash = 16777216, free flash = 16670720
#endif

//============================================================================
// SEEEDUINO / ARDUINO PIN CONFIGURATION
//============================================================================
// Wiring for Seeeduino v4.2 (3.3v) connected to CFA10098 breakout for testing.
//   ARD      | Port | 10098/EVE           | Color
// -----------+------+---------------------|--------
//  #3/D3     |  PD3 | DEBUG_LED           | Green W/W
//  #7/D7     |  PD7 | EVE_INT             | Purple
//  #8/D8     |  PB0 | EVE_PD_NOT          | Blue
//  #9/D9     |  PB1 | EVE_CS_NOT          | Brown
// #10/D10    |  PB2 | SD_CS_NOT           | Grey
// #11/D11    |  PB3 | MOSI (hardware SPI) | Yellow
// #12/D12    |  PB4 | MISO (hardware SPI) | Green
// #13/D13    |  PB5 | SCK  (hardware SPI) | orange

#define EVE_INT 		(7) 	// interrupt from EVE to Arduino - input, not used in these examples
#define EVE_PD_NOT	(8) 	// PD_N from Arduino to EVE - effectively EVE reset
#define EVE_CS_NOT	(9) 	// SPI chip select - defined separately since it's manipulated with GPIO calls
#define SD_CS				(10)  // reserved for use with the SD card library
#define DEBUG_LED		(3)		// debug LED, or used for scope trigger or precise timing

//============================================================================
// EXTRA ARDUINO / EVE CONFIGURATIONS -- nothing should need to be modified
// below here
//============================================================================

// faster direct port access (specific to AVR)
#define CLR_EVE_PD_NOT (PORTB &= ~(0x01))
#define SET_EVE_PD_NOT (PORTB |= (0x01))
#define CLR_EVE_CS_NOT (PORTB &= ~(0x02))
#define SET_EVE_CS_NOT (PORTB |= (0x02))
#define CLR_SD_CS_NOT (PORTB &= ~(0x04))
#define SET_SD_CS_NOT (PORTB |= (0x04))
#define CLR_MOSI (PORTB &= ~(0x08))
#define SET_MOSI (PORTB |= (0x08))
#define CLR_MISO (PORTB &= ~(0x10))
#define SET_MISO (PORTB |= (0x10))
#define CLR_SCK (PORTB &= ~(0x20))
#define SET_SCK (PORTB |= (0x20))
#define CLR_DEBUG_LED (PORTD &= ~(0x08))
#define SET_DEBUG_LED (PORTD |= (0x08))

// these defines describe the circuit board and EVE accelerator
#define EVE_CLOCK_SOURCE (EVE_CLOCK_SOURCE_EXTERNAL)
#define EVE_CLOCK_MUL (EVE_EXTERNAL_CLOCK_MUL_x6_72MHz)
#define EVE_CLOCK_SPEED ((uint32_t) (EVE_CLOCK_MUL & 0x1F) * (uint32_t) 12000000)
#define EVE_PEN_UP_BUG_FIX (0)
// set this to force a calibration, then you can copy that matrix from the
// console and use it to populate touch_transform[]
#define EVE_TOUCH_CAL_NEEDED (0)
// Define active edge of PCLK. Observed by scope:
//  0: Data is put out coincident with falling edge of the clock.
//     Rising edge of the clock is in the middle of the data.
//  1: Data is put out coincident with rising edge of the clock.
//     Falling edge of the clock is in the middle of the data.
#define LCD_PCLKPOL (1)
// spread Spectrum on RGB signals. Probably not a good idea at higher PCLK
// frequencies.
#define LCD_PCLK_CSPREAD (0)
// these are 24-bit displays, so no need to dither.
#define LCD_DITHER (0)

// derived vertical display timing
#define LCD_HEIGHT (VLH)             // active height of LCD display
#define LCD_VSYNC0 (VFP)             // start of vertical sync pulse
#define LCD_VSYNC1 (VFP + VS)        // end of vertical sync pulse
#define LCD_VOFFSET (VFP + VS + VBP) // start of active screen
#define LCD_VCYCLE (VLH + VFP + VS + VBP + VLP) // total number of lines per screen

// pin drive settings for this particular board+display.
#if ((EVE_DEVICE == BT815) || (EVE_DEVICE == BT816) || (EVE_DEVICE == BT817) || \
    (EVE_DEVICE == BT818))
// Newer EVE chips have great granularity.
// This table sets every pin, but you can delete lines where the default drive
// is acceptable. Using a macro allows the pin drive to be defined here in the
// header file (which may be included multiple times across the project, but
// actually defined in the EVE_base.cpp file which is only compiled once.
#define PIN_DRIVE_TABLE                                                        \
	const uint8_t Pin_Drive_Table[22] PROGMEM = {                              \
	    (EVE_PINDRIVE_GPIO_0_HR | EVE_PINDRIVE_HR_5mA),                        \
	    (EVE_PINDRIVE_GPIO_1_HR | EVE_PINDRIVE_HR_5mA),                        \
	    (EVE_PINDRIVE_GPIO_2_HR | EVE_PINDRIVE_HR_5mA),                        \
	    (EVE_PINDRIVE_GPIO_3_HR | EVE_PINDRIVE_HR_5mA),                        \
	    (EVE_PINDRIVE_DISP_LR | EVE_PINDRIVE_LR_1p2mA),                        \
	    (EVE_PINDRIVE_DE_LR | EVE_PINDRIVE_LR_1p2mA),                          \
	    (EVE_PINDRIVE_VSYNC_HSYNC_LR | EVE_PINDRIVE_LR_1p2mA),                 \
	    (EVE_PINDRIVE_PCLK_LR | EVE_PINDRIVE_LR_3p6mA),                        \
	    (EVE_PINDRIVE_BACKLIGHT_LR | EVE_PINDRIVE_LR_1p2mA),                   \
	    (EVE_PINDRIVE_RGB_LR | EVE_PINDRIVE_LR_1p2mA),                         \
	    (EVE_PINDRIVE_AUDIO_L_HR | EVE_PINDRIVE_HR_5mA),                       \
	    (EVE_PINDRIVE_INT_N_HR | EVE_PINDRIVE_HR_5mA),                         \
	    (EVE_PINDRIVE_CTP_RST_N_HR | EVE_PINDRIVE_HR_5mA),                     \
	    (EVE_PINDRIVE_CTP_SCL_HR | EVE_PINDRIVE_HR_5mA),                       \
	    (EVE_PINDRIVE_CTP_SDA_HR | EVE_PINDRIVE_HR_5mA),                       \
	    (EVE_PINDRIVE_SPI_DATA_HR | EVE_PINDRIVE_HR_5mA),                      \
	    (EVE_PINDRIVE_SPIM_SCLK_HR | EVE_PINDRIVE_HR_10mA),                    \
	    (EVE_PINDRIVE_SPIM_SS_N_HR | EVE_PINDRIVE_HR_5mA),                     \
	    (EVE_PINDRIVE_SPIM_MISO_HR | EVE_PINDRIVE_HR_5mA),                     \
	    (EVE_PINDRIVE_SPIM_MOSI_HR | EVE_PINDRIVE_HR_5mA),                     \
	    (EVE_PINDRIVE_SPIM_IO2_HR | EVE_PINDRIVE_HR_5mA),                      \
	    (EVE_PINDRIVE_SPIM_IO3_HR | EVE_PINDRIVE_HR_5mA)}
#else
// older parts have less granularity. LCD drive strength: 0=5mA, 1=10mA
#define LCD_DRIVE_10MA (0)
#endif

//============================================================================
// EXTRA SETUP & ERROR CHECKING BELOW HERE -- nothing should need to be modified
// below here
//============================================================================

// make sure microsd card is used for some demos
#if ((SOUND_DEMO == 1) || (BMP_DEMO == 1) || (MARBLE_DEMO == 1) || (PROGRAM_FLASH_FROM_USD == 1))
# define BUILD_SD (1)
#else
# define BUILD_SD (0)
#endif

// make sure a display is selected
#if !defined(LCD_WIDTH)
#error                                                                         \
    "No display selected. Uncomment exactly one DISPLAY_xxx line in CFA_E_defines.h"
#endif

// throw an error if touch demo is requested for a non-touch display.
#if (EVE_TOUCH_TYPE == EVE_TOUCH_NONE) && (TOUCH_DEMO == 1)
#error Cannot enable touch demo for a non-touch display.
#endif

// throw an error if the controller does not match the touch type.
#if ((EVE_TOUCH_TYPE == EVE_TOUCH_RESISTIVE) &&                                 \
    ((EVE_DEVICE == FT801) || (EVE_DEVICE == FT811) ||                         \
     (EVE_DEVICE == FT813) || (EVE_DEVICE == FT815) || (EVE_DEVICE == FT817)))
#error Cannot specify EVE_TOUCH_RESISTIVE for an EVE_DEVICE that only supports capacitive touch.
#endif

#if ((EVE_TOUCH_TYPE == EVE_TOUCH_CAPACITIVE) &&                                \
    ((EVE_DEVICE == FT800) || (EVE_DEVICE == FT810) ||                         \
     (EVE_DEVICE == FT812) || (EVE_DEVICE == FT816) || (EVE_DEVICE == FT818)))
#error Cannot specify EVE_TOUCH_CAPACITIVE for an EVE_DEVICE that only supports resistive touch.
#endif

#endif // __CFA_E_DEFINES_H__
