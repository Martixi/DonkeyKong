//
// Created by admin on 20.12.2023.
//

#ifndef DONKEYKONG_DRAWING_H
#define DONKEYKONG_DRAWING_H

#include "../Magic/Magic.h"
#include "../Defines.h"

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
bool loadAllTextures(SDL_Surface *&screen, SDL_Surface *&charset, SDL_Surface *&Background, SDL_Surface *&Level,SDL_Surface *&Enemy);
void DrawPlatforms(Sdl &sdl, GameObjects &objects, Colors &colors);
void MarekAnim(GameEntity &player, Data &data, Check &value, double gravity);
void EnemyAnim(GameEntity &Enemy, Data &data, Check &value);
void BarrelAnim(GameEntity *barrel, Data &data);
void PortalAnim(GameEntity &portal, Data &data);
void Animations(GameEntity &player, Data &data, Check &value, GameEntity &enemy,
                GameEntity &portal, GameEntity *barrels, double &gravity);

#endif //DONKEYKONG_DRAWING_H
