#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#define TOP_SCREEN_WIDTH  400
#define TOP_SCREEN_HEIGHT 240
#define BOTTOM_SCREEN_WIDTH  320
#define BOTTOM_SCREEN_HEIGHT 240

void drawpixel(int x, int y)
{
	u8* screen;
	screen = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	u32 v = (TOP_SCREEN_HEIGHT-y+x*TOP_SCREEN_HEIGHT)*3;
	screen[v] = 0xff;
	screen[v+1] = 0xff;
}

int main(int argc, char* argv[])
{
	gfxInitDefault();

	//PrintConsole objects for each screen
	PrintConsole topScreen, bottomScreen;

	//Initialize both PrintConsole objects
	//consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//your code here
		for(int i = 0; i < 100; i++) {
			drawpixel(i, i);
		}

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
