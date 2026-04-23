// ===========================================================================
// Crystalfontz Seeeduino / Arduino Simple Demonstration Program
// for BridgeTek EVE graphic accelerators.
//
// Example firmware for:
// https://www.crystalfontz.com/products/eve-accelerated-tft-displays.php
//
// Project settings can be found in CFA_E_defines.h 
//
// Code written for Seeeduino set to 3.3v (important!)
// Seeeduino is an Arduino Uno clone that can run at 3.3v.
// ===========================================================================
// See LICENSE.md for software licensing information.
// ===========================================================================

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <stdarg.h>
// our setup
#include "CFA_E_defines.h"
// the very simple EVE library files
#include "EVE_base.h"
#include "EVE_draw.h"
// our demonstrations of various EVE functions
#include "demos.h"

// ===========================================================================
void setup()
{
	// arduino setup (this is rus first)
#if (DEBUG_LEVEL != DEBUG_NONE)
	// Initialize UART for debugging messages
	Serial.begin(115200);
#endif
	DBG_STAT("Begin\n");

	// Initialize GPIO port states
	SET_EVE_CS_NOT; // set CS# high to start - SPI inactive
	SET_EVE_PD_NOT; // set PD# high to start
	SET_SD_CS_NOT;

	// Initialize port directions
	pinMode(EVE_INT, INPUT_PULLUP); // EVE interrupt output (not used in this example)
	pinMode(EVE_PD_NOT, OUTPUT); // EVE Power Down (reset) input
	pinMode(EVE_CS_NOT, OUTPUT); // EVE SPI bus CS# input
	pinMode(SD_CS, OUTPUT); // USD card CS
	pinMode(DEBUG_LED, OUTPUT); // Optional pin used for LED or oscilloscope debugging.

	// Initialize SPI
	SPI.begin();
	SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0)); // Bump the clock to 8MHz. Appears to be the maximum.
	DBG_GEEK("SPI initialzed to: 8MHz\n");

#if (BUILD_SD == 1)
	// The hardware functions fine at 8MHz which also appears to be the max that the ATmega328P can do.
	if (!SD.begin(8000000, SD_CS))
	{
		DBG_STAT("uSD card failed to initialize, or not present\n");
		// reset the SPI clock to fast. SD card library does not clean up well.
		// bump the clock to 8MHz. Appears to be the maximum.
		SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
	}
	else
		// ok
		DBG_STAT("uSD card initialized.\n");
#endif

	// see if we can find the FTDI/BridgeTek EVE processor
	if (EVE_Initialize() != 0)
	{
		DBG_STAT("Failed to initialize %s8%02X. Stopping.\n", EVE_DEVICE < 0x14 ? "FT" : "BT", EVE_DEVICE);
		while (1)
		{
		} // halt here
	}

	// finished setup
	DBG_STAT("%s8%02X initialized.\n", EVE_DEVICE < 0x14 ? "FT" : "BT", EVE_DEVICE);
}

// ===========================================================================

void loop()
{
	// main arduino program loop
	DBG_GEEK("Loop initialization.\n");

	// get the current write pointer from the EVE
	uint16_t FWo = EVE_REG_Read_16(EVE_REG_CMD_WRITE);
	DBG_GEEK("Initial Offset Read: 0x%04X = %u\n", FWo, FWo);

	// keep track of the RAM_G memory allocation
	uint32_t RAM_G_Unused_Start = 0;
	(void)(RAM_G_Unused_Start); //remove the warning if this isnt used anywhere
	DBG_GEEK("Initial RAM_G: 0x%08lX = %lu\n", RAM_G_Unused_Start, RAM_G_Unused_Start);

	// We need to keep track of the bitmap handles and where they are used.
	// By default, bitmap handles 16 to 31 are used for built-in font and 15 is used as scratch bitmap
	// handle by co-processor engine commands CMD_GRADIENT, CMD_BUTTON and CMD_KEYS.
	// For whatever reason, I am going to allocate handles from 14 to 0.
	uint8_t next_bitmap_handle_available = 14;
	(void)(next_bitmap_handle_available); //remove the warning if this isnt used anywhere
	DBG_GEEK("EVE_Initialize_Flash() . . . ");
	FWo = EVE_Initialize_Flash(FWo);
	DBG_GEEK("done.\n");

	uint8_t flash_status = EVE_REG_Read_8(EVE_REG_FLASH_STATUS);
	DBG_GEEK_Decode_Flash_Status(flash_status);

#if (PROGRAM_FLASH_FROM_USD == 1)
	// Keep track of the current write pointer into flash.
	uint32_t Flash_Sector = 0;
	// Load the BLOB & write our image data to the flash from the uSD card. This only needs to
	// be executed once. It uses RAM_G as scratch temporary memory, but does not allocate any RAM_G.
	FWo = Initialize_Flash_From_uSD(FWo, RAM_G_Unused_Start, &Flash_Sector);
#endif

#if (BOUNCE_DEMO == 1)
	DBG_STAT("Initialize_Bounce_Demo() . . .");
	Initialize_Bounce_Demo();
	DBG_STAT(" done.\n");
#endif

#if (LOGO_DEMO == 1)
	DBG_STAT("Initialize_Logo_Demo() . . .");
	FWo = Initialize_Logo_Demo(FWo, &RAM_G_Unused_Start, next_bitmap_handle_available);
	next_bitmap_handle_available--; // keep track that we used a bitmap handle
	DBG_STAT("  done.\n");
	DBG_GEEK("RAM_G after logo: 0x%08lX = %lu\n", RAM_G_Unused_Start, RAM_G_Unused_Start);
#endif

#if (BMP_DEMO == 1)
	DBG_STAT("Initialize_Bitmap_Demo() . . .");
	FWo = Initialize_Bitmap_Demo(FWo, next_bitmap_handle_available);
	next_bitmap_handle_available--; // keep track that we used a bitmap handle
	DBG_STAT("  done.\n");
	DBG_GEEK("RAM_G after bitmap: 0x%08lX = %lu\n", RAM_G_Unused_Start, RAM_G_Unused_Start);
#endif

#if (SOUND_DEMO == 1)
	DBG_STAT("Initialize_Sound_Demo() . . .");
	FWo = Initialize_Sound_Demo(FWo, &RAM_G_Unused_Start);
	DBG_STAT("  done.\n");
	DBG_GEEK( "RAM_G after sound: 0x%08lX = %lu\n", RAM_G_Unused_Start, RAM_G_Unused_Start);
#endif

#if (MARBLE_DEMO == 1)
	DBG_STAT("Initialize_Marble_Demo() . . .");
	FWo = Initialize_Marble_Demo(FWo, &RAM_G_Unused_Start, next_bitmap_handle_available);
	next_bitmap_handle_available--; // keep track that we used a bitmap handle
  DBG_STAT("  done.\n");
	DBG_GEEK("RAM_G after marble: 0x%08lX = %lu\n", RAM_G_Unused_Start, RAM_G_Unused_Start);
#endif

#if (TOUCH_DEMO == 1)
	// Bitmask of valid points in the array
	uint8_t points_touched_mask;
	int16_t x_points[5]; // 5 needed for cap touch, resistive only uses 1 point
	int16_t y_points[5];
#endif

#if (VIDEO_DEMO == 1)
	FWo = Initialize_Video_Demo(FWo, &RAM_G_Unused_Start, next_bitmap_handle_available);
	next_bitmap_handle_available--; // Keep track that we used a bitmap handle
	DBG_GEEK("RAM_G after video: 0x%08lX = %lu\n", RAM_G_Unused_Start, RAM_G_Unused_Start);
#endif

	DBG_STAT("Initialization complete, entering main loop.\n");
	while (1)
	{
		// frame synchronizing
		// Wait for graphics processor to complete executing the current command list. This happens when EVE_REG_CMD_READ
		// matches EVE_REG_CMD_WRITE, indicating that all commands have been executed.  We have a local copy of
		// EVE_REG_CMD_WRITE in FWo. This appears to only occur on frame completion, which is nice since
		// it allows us to step the animation along at a reasonable rate. If possible, we have tweaked the
		// timing on the Crystalfontz displays to all have ~60Hz frame rate.
		FWo = Wait_for_EVE_Execution_Complete(FWo);

#if (TOUCH_DEMO == 1)
		points_touched_mask = Read_Touch(x_points, y_points); // read the touch screen.
#endif

#if (SOUND_DEMO == 1)
		// See if we should play a sound. The sound will synchronize with the the start of the logo rotation.
		// If the previous sound is still playing it will wait until the next time we call it.
		Start_Sound_Demo_Playing();
#endif

		// start the display list
		FWo = EVE_Cmd_Dat_0(FWo, (EVE_ENC_CMD_DLSTART)); // start the display list
		FWo = EVE_Cmd_Dat_0(FWo, EVE_ENC_CLEAR_COLOR_RGB(0, 0, 0)); // set the default clear color to black
		FWo = EVE_Cmd_Dat_0(FWo, EVE_ENC_CLEAR(1 ,1 ,1)); // clear the screen - this and the previous prevent artifacts betweenlists

		// add graphic items to the display list
		FWo = EVE_Filled_Rectangle(FWo, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);  // fill background with white
#if (BMP_DEMO == 1)
		FWo = Add_Bitmap_To_Display_List(FWo);
#endif

#if (TOUCH_DEMO == 1)
		// see if we are touched at all
		if (points_touched_mask != 0)
		{
			// loop through the possible touch points
			uint8_t mask = 0x01;
			for (uint8_t i = 0; i < 5; i++)
			{
				if (0 != (points_touched_mask & mask))
				{
					// color table
					static uint32_t colors[5] =
					{ EVE_ENC_COLOR_RGB(0x00, 0x00, 0xFF), EVE_ENC_COLOR_RGB(0x00, 0xFF, 0x00), EVE_ENC_COLOR_RGB(0xFF,
						0x00, 0x00), EVE_ENC_COLOR_RGB(0xFF, 0x00, 0xFF), EVE_ENC_COLOR_RGB(0xFF, 0xFF, 0x00) };

					// this code loops through all the points touched
					FWo = EVE_Cmd_Dat_0(FWo, colors[i]); // make it solid
					FWo = EVE_Cmd_Dat_0(FWo, EVE_ENC_COLOR_A(0xFF));
					FWo = EVE_Point(FWo, x_points[i] * 16, y_points[i] * 16, 10 * 16); // draw the touch dot, a 60px point (filled circle)
					FWo = EVE_Cmd_Dat_0(FWo, EVE_ENC_COLOR_RGB(0xFF, 0x00, 0xFF)); // tag the touch point with magenta text to show off EVE_PrintF

					// move the the text out from under the user's finger
					int16_t xoffset = 160;
					int16_t yoffset = 80;
					if (x_points[i] >= (LCD_WIDTH / 2))
						xoffset = -160;
					if (y_points[i] >= (LCD_HEIGHT / 2))
						yoffset = -80;

					// put the text into the display list
					FWo = EVE_PrintF(FWo, x_points[i] + xoffset, y_points[i] + yoffset, 25, EVE_OPT_CENTER, "T[%d]@(%d,%d)", i + 1, x_points[i], y_points[i]);
				}
				mask <<= 1;
			}
		}
#endif

#if (MARBLE_DEMO == 1)
		// only show the bouncing marble if no there is no touch
#if (TOUCH_DEMO == 1)		
		if (points_touched_mask == 0)
#endif
			FWo = Add_Marble_To_Display_List(FWo);
#endif

#if (BOUNCE_DEMO == 1)
		// bouncy ball & rubber band
		FWo = Add_Bounce_To_Display_List(FWo);
#endif

#if (VIDEO_DEMO == 1) && (TOUCH_DEMO == 1)
		// add video with touch points
		FWo = Add_Video_To_Display_List(FWo, points_touched_mask, x_points, y_points);
#endif
#if (VIDEO_DEMO == 1) && (TOUCH_DEMO == 0)
		// add video
		FWo = Add_Video_To_Display_List(FWo);
#endif

#if (LOGO_DEMO == 1)
		// add logo to display list
		FWo = Add_Logo_To_Display_List(FWo);
#endif

#if (0 != VIDEO_DEMO)
		// Move the video to the next 30Hz frame
		FWo = Update_Video_Frame(FWo);
#endif // (0 != VIDEO_DEMO)

		// finish and show the display list
		FWo = EVE_Cmd_Dat_0(FWo, EVE_ENC_DISPLAY()); // instruct the graphics processor to show the list
		FWo = EVE_Cmd_Dat_0(FWo, EVE_ENC_CMD_SWAP); // make this list active
		EVE_REG_Write_16(EVE_REG_CMD_WRITE, (FWo)); // update the ring buffer pointer so the graphics processor starts executing

#if (BOUNCE_DEMO == 1)
		// move the ball and cycle color & transparency
		Bounce_Ball();
#endif

#if (MARBLE_DEMO == 1)
		// bouce the marble around
		Move_Marble();
#endif
	}

	// end of arduino main loop (we should never get here)
}

// ===========================================================================
