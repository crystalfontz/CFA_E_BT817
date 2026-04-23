#ifndef __CFA_E_DISPLAY_CFA480480E0040_H__
#define __CFA_E_DISPLAY_CFA480480E0040_H__

//============================================================================
// Crystalfontz America, Inc. example firmware for:
// https://www.crystalfontz.com/products/eve-accelerated-tft-displays.php
//===========================================================================
// See LICENSE.md for software licensing information.
//===========================================================================

//============================================================================
// Timing for Crystalfontz 4.0" 480x480 EVE displays:
//   CFA480480E0040TN  non-touch
//============================================================================

// Define RGB output pins order, determined by PCB layout
#define LCD_SWIZZLE (0b0011)

// This family uses falling-edge PCLK; overrides the board default of (1).
// Data is put out coincident with falling edge of the clock.
// Rising edge of the clock is in the middle of the data.
#undef LCD_PCLKPOL
#define LCD_PCLKPOL (0)

// Pixel clock divisor (based on 72MHz internal clock)
//   3 = 24MHz  (target ~33MHz)
#define LCD_PCLK (3)

//----------------------------------------------------------------------------
// Frame_Rate = 60Hz / 16.7mS
//----------------------------------------------------------------------------
// Horizontal timing (minimum values from ST7701_v1_2.pdf controller datasheet)
// Target 60Hz frame rate, using the largest possible line time in order to
// maximize the time that the EVE has to process each line.
#define HPX         (480) // Horizontal Pixel Width
#define HSW         (1) // Horizontal Sync Width (1~255)
#define HBP         (15) // Horizontal Back Porch (1~255, includes HSW)
#define HFP         (15) // Horizontal Front Porch (must be 1)
#define HPP         (5) // Horizontal Pixel Padding (calculate using Calculation_of_Timing.xlsx)
#define LCD_WIDTH   (HPX) // Active width of LCD display
#define LCD_HSYNC0  (HFP) // Start of horizontal sync pulse
#define LCD_HSYNC1  (HFP + HSW) // End of horizontal sync pulse
#define LCD_HOFFSET (HFP + HSW + HBP) // Start of active line
#define LCD_HCYCLE  (HPX + HFP + HSW + HBP + HPP) // Total number of clocks per line

//----------------------------------------------------------------------------
// Vertical timing (minimum values from ST7701_v1_2.pdf page 75)
#define VLH (480) // Vertical Line Height
#define VS  (1) // Vertical Sync (in lines)  (1~254)
#define VBP (1) // Vertical Back Porch (1~254, includes VS)
#define VFP (2) // Vertical Front Porch (must be 2)
#define VLP (1) // Vertical Line Padding (tot=511: 510~525~650)

//touch
#define EVE_TOUCH_TYPE (EVE_TOUCH_NONE)
#define EVE_TOUCH_POINTS (0)

#endif // __CFA_E_DISPLAY_CFA480480E0040_H__
