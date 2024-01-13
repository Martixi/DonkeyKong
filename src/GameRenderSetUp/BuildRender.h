//
// Created by admin on 03.01.2024.
//

#ifndef DONKEYKONG_BUILDRENDER_H
#define DONKEYKONG_BUILDRENDER_H

#include "../Magic/Magic.h"
#include "../Defines.h"
#include "cstdio"

void
PrepareGame(Sdl &sdl, GameObjects &objects, GameEntity &player, Colors &colors, GameEntity &enemy, GameEntity *barrels,
            GameEntity &portal);

void GenerateEntity(GameEntity *player, SDL_Renderer *renderer, const char *bmp, int width, int height, int startingX,
                    int startingY);

void RenderPlayer(SDL_Renderer *renderer, GameEntity *player);

void RenderEnemy(SDL_Renderer *renderer, GameEntity *enemy);

SDL_Texture *TransformImage(const char *bmp, SDL_Renderer *renderer);

void Platform_Set_Up(SDL_Rect *platforms);

void Ladder_Set_Up(SDL_Rect *ladders);

void
BasicRender(SDL_Texture *texture, SDL_Surface *screen, SDL_Renderer *renderer, GameEntity *player, GameEntity *enemy,
            GameEntity *barrels, GameEntity *portal);

void BasicSetUp(SDL_Rect *platforms, SDL_Rect *ladders);

void
LevelView(Sdl &sdl, char *text, Data &data, Colors colors, GameEntity player, GameObjects &objects, GameEntity Enemy,
          GameEntity *barrels, GameEntity Portal);

bool CheckLibrary(Sdl &sdl);

void TimeUpdate(Data &data, double &delta);

#endif //DONKEYKONG_BUILDRENDER_H
