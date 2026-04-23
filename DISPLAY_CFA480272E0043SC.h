#ifndef __DISPLAY_CFA480272E0043SC_H__
#define __DISPLAY_CFA480272E0043SC_H__

//============================================================================
// Crystalfontz America, Inc. example firmware for:
// https://www.crystalfontz.com/products/eve-accelerated-tft-displays.php
//===========================================================================
// See LICENSE.md for software licensing information.
//===========================================================================

//============================================================================
// Timing for Crystalfontz 4.3" 480x272 EVE displays:
//   CFA480272E0043SC  capacitive touch
//============================================================================

// Define RGB output pins order, determined by PCB layout
#define LCD_SWIZZLE (0x0)

// Pixel clock divisor (based on 72MHz internal clock)
//   8 = 9MHz
#define LCD_PCLK (8)

//----------------------------------------------------------------------------
// Frame_Rate = 60Hz / 16.7mS
//----------------------------------------------------------------------------
// Horizontal timing (minimum values from ST7282_v1_5 page 61)
// Target 60Hz frame rate, using the largest possible line time in order to
// maximize the time that the EVE has to process each line.
#define HPX         (480) // Horizontal Pixel Width
#define HSW         (4) // Horizontal Sync Width
#define HBP         (43) // Horizontal Back Porch
#define HFP         (8) // Horizontal Front Porch
#define HPP         (1) // Horizontal Pixel Padding, EVE needs at least 1 here
#define LCD_WIDTH   (HPX) // Active width of LCD display
#define LCD_HSYNC0  (HFP) // Start of horizontal sync pulse
#define LCD_HSYNC1  (HFP + HSW) // End of horizontal sync pulse
#define LCD_HOFFSET (HFP + HSW + HBP) // Start of active line
#define LCD_HCYCLE  (HPX + HFP + HSW + HBP + HPP) // Total number of clocks per line

//----------------------------------------------------------------------------
// Vertical timing
#define VLH (272) // Vertical Line Height
#define VS  (4) // Vertical Sync (in lines)
#define VBP (12) // Vertical Back Porch
#define VFP (8) // Vertical Front Porch
#define VLP (1) // Vertical Line Padding, EVE needs at least 1 here

//touch
#define EVE_TOUCH_TYPE (EVE_TOUCH_CAPACITIVE)
#define EVE_TOUCH_CAP_DEVICE (EVE_CAP_DEV_FT5316)
#define EVE_TOUCH_POINTS (5)

#endif // __DISPLAY_CFA480272E0043SC_H__
