#ifndef __DEMOS_H__
#define __DEMOS_H__

//============================================================================
// Crystalfontz America, Inc. example firmware for:
// https://www.crystalfontz.com/products/eve-accelerated-tft-displays.php
//===========================================================================
// See LICENSE.md for software licensing information.
//===========================================================================

#if (0 != PROGRAM_FLASH_FROM_USD)
uint16_t Initialize_Flash_From_uSD(uint16_t FWol, uint32_t RAM_G_Unused_Start, uint32_t *Flash_Sector);
#endif // (0 != PROGRAM_FLASH_FROM_USD)

#if (0 != TOUCH_DEMO)
uint16_t Add_Touch_Dot_To_Display_List(uint16_t FWol, uint16_t touch_x, uint16_t touch_y);
#endif //(0 != TOUCH_DEMO)

#if (0 != BMP_DEMO)
uint16_t Initialize_Bitmap_Demo(uint16_t FWol, uint8_t next_bitmap_handle_available);
uint16_t Add_Bitmap_To_Display_List(uint16_t FWol);
#endif // (0 != BMP_DEMO)

#if (0 != MARBLE_DEMO) // Requires uSD
uint16_t Initialize_Marble_Demo(uint16_t FWol, uint32_t *RAM_G_Unused_Start, uint8_t next_bitmap_handle_available);
#if (0 != TOUCH_DEMO)
void Force_Marble_Position(uint32_t x, uint16_t y);
#endif //(0 != TOUCH_DEMO)
uint16_t Add_Marble_To_Display_List(uint16_t FWol);
void Move_Marble(void);
#endif // (0 != MARBLE_DEMO)

#if (0 != BOUNCE_DEMO)
void Initialize_Bounce_Demo(void);
uint16_t Add_Bounce_To_Display_List(uint16_t FWol);
void Bounce_Ball(void);
#endif // (0 != BOUNCE_DEMO)

#if (0 != LOGO_DEMO)
uint16_t Initialize_Logo_Demo(uint16_t FWol, uint32_t *RAM_G_Unused_Start, uint8_t next_bitmap_handle_available);
uint16_t Add_Logo_To_Display_List(uint16_t FWol);
#endif // (0 != LOGO_DEMO)

#if (0 != SOUND_DEMO)
uint16_t Initialize_Sound_Demo(uint16_t FWol, uint32_t *RAM_G_Unused_Start);
void Start_Sound_Demo_Playing(void);
#endif // (0 != SOUND_DEMO)

#if (0 != VIDEO_DEMO)
uint16_t Initialize_Video_Demo(uint16_t FWol, uint32_t *RAM_G_Unused_Start, uint8_t next_bitmap_handle_available);

#if (0 != TOUCH_DEMO)
uint16_t Add_Video_To_Display_List(uint16_t FWol, uint8_t points_touched_mask, int16_t *x_points, int16_t *y_points);
#else // (0 != TOUCH_DEMO)
uint16_t Add_Video_To_Display_List(uint16_t FWol);
#endif // (0 != TOUCH_DEMO)
uint16_t Update_Video_Frame(uint16_t FWol);
#endif // (0 != VIDEO_DEMO)

//============================================================================
#endif // __DEMOS_H__
