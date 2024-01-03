//
// Created by admin on 20.12.2023.
//

#include "Drawing.h"
#include "Magic.h"
#include "Defines.h"


void DrawString(SDL_Surface *screen, int x, int y, const char *text,
                SDL_Surface *charset) {
	int offX, offY;
	int character;

	// SDL_Rect - structure keeping information about origin (x, y) (top left corner) and its (w, h) (width and height)
	SDL_Rect src, dest;

	// basic assignment to a struct
	src.w = 8;
	src.h = 8;
	dest.w = 8;
	dest.h = 8;

	// while we are not at the end of the string '/0' do this...
	while (*text) {
		character = *text & 255; // convert 'char' to number with a "mask"
		// now knowing the characters are position in rows of 16 elements
		// from numerical value we calculate its offset from top and left
		offY = (character / 16) * 8;
		offX = (character % 16) * 8;

		src.x = offX;
		src.y = offY;
		dest.x = x;
		dest.y = y;

		// Draw the letter
		SDL_BlitSurface(charset, &src, screen, &dest);
		/* This function takes in 4 argument, or more precisely two groups of arguments
		 * each group consists of 2 args.
		 *
		 * group looks like this: (surface with some drawings, information [x, y, w, h] what part interest us)
		 * now the full function arguments can be read: (copy from, copy to)
		 */

		// Move x by width of the letter and increase the letter
		x += 8;
		text++;
	}
}

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) { // remember (x, y) cords of the center
	// SDL_Rect - structure keeping information about origin (x, y) (top left corner) and its (w, h) (width and height)
	SDL_Rect dest;
	SDL_Rect src[] = {};
	// Determine the top left corner
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	// copy width and height
	dest.w = sprite->w;
	dest.h = sprite->h;
	// draw entire sprite on screen at given position
	SDL_BlitSurface(sprite, nullptr, screen, &dest);
}

void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) { // Warning! Wibbly wobbly, timey wimey stuff
	// how about we move on and just take for granted that this works? Okay? Great!

	int bpp = surface->format->BytesPerPixel; // one pixel consists of N Bytes, wee need to know of how many
	// surface->pixels is type of `void *` void pointers, whenever we do something directly with it,
	// we need to reinterpret it to use operate on Bytes
	Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;
	/*
	 * Seriously why you are reading this, go touch some gras.
	 * Uint8 *p = (Uint8 *) - this is the type we are operating on, a "SiMpLiFiCaTiOn" for pointer arithmetics
	 * surface->pixels - pointer to array of pixels, yes 1D array #libraryOptimization
	 * ... now will come pointer arithmetics for determining the correct spot to alter values to change the color of pixel
	 * + y * surface->pitch - `pitch` holds info about how long in Bytes one row is, that is how we get correct row
	 * + x * bpp - Byte size of one Pixel times which pixel from left it is
	 * now we should have a pointer to the beginning of a pixel value.
	 */
	// first reinterpret the pointer to be the size of out format
	*(Uint32 *) p = color; // alter the value
	// congrats, you changed one pixel
	// almost no students were harmed in writing this explanation
}

void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	// yes! you guessed correctly.
	for (int i = 0; i < l; i++) { // this iterates over the line and draws every pixel, separately
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	}
}

void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	// Drawing borderlines separately, so we can have outlines in a different color
	DrawLine(screen, x, y, k, 0, 1, outlineColor);             // left
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);     // right
	DrawLine(screen, x, y, l, 1, 0, outlineColor);             // top
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);     // bottom

	for (int i = y + 1; i < y + k - 1; i++) // iterate over y value and fill the remaining space
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
}

bool loadAllTextures(SDL_Surface *&screen, SDL_Surface *&charset, SDL_Surface *&Background, SDL_Surface *&Level) {

	screen = SDL_CreateRGBSurface(
			0,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			32,
			0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000
	);

	charset = SDL_LoadBMP("static/cs8x8.bmp");
	SDL_SetColorKey(charset, true, 0x000000);
	Background = SDL_LoadBMP("static/Forest2.bmp");
	Level = SDL_LoadBMP("static/zamek.bmp");
	SDL_SetColorKey(Level, true, 0x000000);
	return true;
}