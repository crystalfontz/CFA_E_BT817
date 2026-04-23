#ifndef __CFA_E_DISPLAY_CFAF1024600B0070_H__
#define __CFA_E_DISPLAY_CFAF1024600B0070_H__

//============================================================================
// Crystalfontz America, Inc. example firmware for:
// https://www.crystalfontz.com/products/eve-accelerated-tft-displays.php
//===========================================================================
// See LICENSE.md for software licensing information.
//===========================================================================

//============================================================================
// Timing for Crystalfontz 7.0" 1024x600 EVE displays:
//   CFAF1024600B0070SCA1  capacitive touch
//============================================================================

// Define RGB output pins order, determined by PCB layout
#define LCD_SWIZZLE (0x3)

// Pixel clock divisor (based on 72MHz internal clock)
//   1 = 60MHz  (target 44.9MHz to 63MHz)
#define LCD_PCLK (1)

//----------------------------------------------------------------------------
// Frame_Rate = 60Hz / 16.7mS
//----------------------------------------------------------------------------
// Horizontal timing (minimum values from EK7900_v1.1.pdf page 26)
// Target 60Hz frame rate, using the largest possible line time in order to
// maximize the time that the EVE has to process each line.
#define HPX         (1024) // Horizontal Pixel Width
#define HSW         (1) // Horizontal Sync Width (1~140)
#define HBP         (160) // Horizontal Back Porch
#define HFP         (16) // Horizontal Front Porch (16~160~216)
#define HPP         (396) // Horizontal Pixel Padding (calculate using Calculation_of_Timing.xlsx)
#define LCD_WIDTH   (HPX) // Active width of LCD display
#define LCD_HSYNC0  (HFP) // Start of horizontal sync pulse
#define LCD_HSYNC1  (HFP + HSW) // End of horizontal sync pulse
#define LCD_HOFFSET (HFP + HSW + HBP) // Start of active line
#define LCD_HCYCLE  (HPX + HFP + HSW + HBP + HPP) // Total number of clocks per line

//----------------------------------------------------------------------------
// Vertical timing (minimum values from EK7900_v1.1.pdf page 27)
#define VLH (600) // Vertical Line Height
#define VS  (1) // Vertical Sync (in lines)  (1~20)
#define VBP (32) // Vertical Back Porch (must be 23, includes VS)
#define VFP (1) // Vertical Front Porch (7~22~147)
#define VLP (1) // Vertical Line Padding (tot=511: 510~525~650)

//touch
#define EVE_TOUCH_TYPE (EVE_TOUCH_CAPACITIVE)
#define EVE_TOUCH_CAP_DEVICE (EVE_CAP_DEV_FT5316)
#define EVE_TOUCH_POINTS (5)

#endif // __CFA_E_DISPLAY_CFAF1024600B0070_H__
