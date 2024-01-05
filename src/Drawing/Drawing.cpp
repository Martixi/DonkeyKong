//
// Created by admin on 20.12.2023.
//

#include "Drawing.h"
#include "../Magic/Magic.h"
#include "../Defines.h"

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


void DrawString(SDL_Surface *screen, int x, int y, const char *text,
                SDL_Surface *charset) {
	int offX, offY;
	int character;
	SDL_Rect src, dest;
	src.w = 8;
	src.h = 8;
	dest.w = 8;
	dest.h = 8;
	while (*text) {
		character = *text & 255;
		offY = (character / 16) * 8;
		offX = (character % 16) * 8;

		src.x = offX;
		src.y = offY;
		dest.x = x;
		dest.y = y;
		SDL_BlitSurface(charset, &src, screen, &dest);
		x += 8;
		text++;
	}
}

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	SDL_Rect src[] = {};
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, nullptr, screen, &dest);
}

void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *) p = color;
}

void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	}
}

void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (int i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
}

void DrawPlatforms( Sdl &sdl, GameObjects &objects, Colors &colors ){
	SDL_Rect *platforms = objects.platforms;
	SDL_Rect *ladders = objects.ladders;

	for (int i = 0; i < PLATFORMS; ++i) {
		DrawRectangle(sdl.screen, platforms[i].x, platforms[i].y, platforms[i].w, platforms[i].h, colors.cyan, colors.cyan);
	}
	for (int j = 0; j < LADDERS; ++j) {
		DrawRectangle(sdl.screen, ladders[j].x, ladders[j].y, ladders[j].w, ladders[j].h, colors.red, colors.red);
	}
}

void MarekAnim(GameEntity &player, Data &data, Check &value, double gravity){
	//Animation falling
	if (gravity) value.falling = true;
	else value.falling = false;

	//Animation Walking and standing
	if (player.speed.x != 0){ value.walking = true; value.standing = false;}
	else {value.walking = false; value.standing = true;}


	if (data.AnimFrames % data.frameChange == 0) {
		player.currentFrame += 1;
		player.size.x = player.size.w * player.currentFrame;
	}
	if (data.AnimFrames % (data.frameChange * (data.maxFrames - 1)) == 0 or player.currentFrame > 7) {
		player.currentFrame = 0;
	}
	data.AnimFrames++;
	if (value.falling) {
		player.currentFrame = 7;
	} else if (value.standing) player.currentFrame = 8;
}

