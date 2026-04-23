#ifndef __CFA_E_DISPLAY_CFA800480E3050_H__
#define __CFA_E_DISPLAY_CFA800480E3050_H__

//============================================================================
// Crystalfontz America, Inc. example firmware for:
// https://www.crystalfontz.com/products/eve-accelerated-tft-displays.php
//===========================================================================
// See LICENSE.md for software licensing information.
//===========================================================================

//============================================================================
// Timing for Crystalfontz 5.0" 800x480 EVE displays:
//   CFA800480E3050SN  non-touch
//============================================================================

// Define RGB output pins order, determined by PCB layout
#define LCD_SWIZZLE (0x0)

// Pixel clock divisor (based on 72MHz internal clock)
//   2 = 36MHz  (target ~33MHz)
#define LCD_PCLK (2)

//----------------------------------------------------------------------------
// Frame_Rate = 60Hz / 16.7mS
//----------------------------------------------------------------------------
// Horizontal timing (Typical values from ST7262_v0_3.pdf page 52)
// Target 60Hz frame rate, using the largest possible line time in order to
// maximize the time that the EVE has to process each line.
#define HPX         (800) // Horizontal Pixel Width
#define HSW         (4) // Horizontal Sync Width (pulse width 2-8)
#define HBP         (8) // Horizontal Back Porch (4~8~48, includes HSW)
#define HFP         (8) // Horizontal Front Porch (4~8~48)
#define HPP         (377) // Horizontal Pixel Padding (calculate using Calculation_of_Timing.xlsx) EVE needs at least 1 here
#define LCD_WIDTH   (HPX) // Active width of LCD display
#define LCD_HSYNC0  (HFP) // Start of horizontal sync pulse
#define LCD_HSYNC1  (HFP + HSW) // End of horizontal sync pulse
#define LCD_HOFFSET (HFP + HSW + HBP) // Start of active line
#define LCD_HCYCLE  (HPX + HFP + HSW + HBP + HPP) // Total number of clocks per line

//----------------------------------------------------------------------------
// Vertical timing (Typical values from ST7262_v0_3.pdf page 52)
#define VLH (480) // Vertical Line Height
#define VS  (4) // Vertical Sync (in lines)  (1~20)
#define VBP (8) // Vertical Back Porch (must be 23, includes VS)
#define VFP (8) // Vertical Front Porch (7~22~147)
#define VLP (1) // Vertical Line Padding (tot=511: 510~525~650)

//touch
#define EVE_TOUCH_TYPE (EVE_TOUCH_NONE)
#define EVE_TOUCH_POINTS (0)

#endif // __CFA_E_DISPLAY_CFA800480E3050_H__
