//
// Created by admin on 20.12.2023.
//

#ifndef DONKEYKONG_DRAWING_H
#define DONKEYKONG_DRAWING_H
#include "Magic.h"
#include "Defines.h"

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
bool loadAllTextures(SDL_Surface *&screen, SDL_Surface *&charset, SDL_Surface *&Background, SDL_Surface *&Level);
void DrawPlatforms( Sdl &sdl, GameObjects &objects, Colors &colors );


#endif //DONKEYKONG_DRAWING_H
