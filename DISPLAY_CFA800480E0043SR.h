#ifndef __CFA_E_DISPLAY_CFA800480E0043_H__
#define __CFA_E_DISPLAY_CFA800480E0043_H__

//============================================================================
// Crystalfontz America, Inc. example firmware for:
// https://www.crystalfontz.com/products/eve-accelerated-tft-displays.php
//===========================================================================
// See LICENSE.md for software licensing information.
//===========================================================================

//============================================================================
// Timing for Crystalfontz 4.3" 800x480 EVE displays:
//   CFA800480E0043SR  resistive touch
//============================================================================

// Define RGB output pins order, determined by PCB layout
#define LCD_SWIZZLE (0x0)

// Pixel clock divisor (based on 72MHz internal clock)
//   3 = 24MHz
#define LCD_PCLK (3)

//----------------------------------------------------------------------------
// Frame_Rate = 60Hz / 16.7mS
//----------------------------------------------------------------------------
// Horizontal timing (minimum values from ST7262_v0.3 page 52)
// Target 60Hz frame rate, using the largest possible line time in order to
// maximize the time that the EVE has to process each line.
#define HPX         (800) // Horizontal Pixel Width
#define HSW         (4) // Horizontal Sync Width
#define HBP         (8) // Horizontal Back Porch
#define HFP         (8) // Horizontal Front Porch
#define HPP         (1) // Horizontal Pixel Padding, EVE needs at least 1 here
#define LCD_WIDTH   (HPX) // Active width of LCD display
#define LCD_HSYNC0  (HFP) // Start of horizontal sync pulse
#define LCD_HSYNC1  (HFP + HSW) // End of horizontal sync pulse
#define LCD_HOFFSET (HFP + HSW + HBP) // Start of active line
#define LCD_HCYCLE  (HPX + HFP + HSW + HBP + HPP) // Total number of clocks per line

//----------------------------------------------------------------------------
// Vertical timing
#define VLH (480) // Vertical Line Height
#define VS  (4) // Vertical Sync (in lines)
#define VBP (8) // Vertical Back Porch
#define VFP (8) // Vertical Front Porch
#define VLP (1) // Vertical Line Padding, EVE needs at least 1 here

//touch
#define EVE_TOUCH_TYPE (EVE_TOUCH_RESISTIVE)
#define EVE_TOUCH_POINTS (1)

#endif // __CFA_E_DISPLAY_CFA800480E0043_H__
