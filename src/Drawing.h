//
// Created by admin on 20.12.2023.
//

#ifndef DONKEYKONG_DRAWING_H
#define DONKEYKONG_DRAWING_H
#include "Magic.h"


// draw a text txt on surface screen, starting from the point (x, y)
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);


// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
// "sprite" meaning an asset/image or a part of it
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);


// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);


// draw vertical or horizontal line
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);


// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);


bool loadAllTextures(SDL_Surface *&screen, SDL_Surface *&charset, SDL_Surface *&Background, SDL_Surface *&Level);

#endif //DONKEYKONG_DRAWING_H
