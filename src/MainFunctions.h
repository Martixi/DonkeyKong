//
// Created by admin on 03.01.2024.
//

#ifndef DONKEYKONG_MAINFUNCTIONS_H
#define DONKEYKONG_MAINFUNCTIONS_H
#include "Magic.h"
#include "Defines.h"
#include "cstdio"

void PrepareGame(Sdl &sdl, GameObjects &objects, GameEntity &player, Colors &colors);
void GenerateEntity(GameEntity *player,SDL_Renderer *renderer, const char *bmp, int width, int height, int startingX, int startingY);
void RenderPlayer(SDL_Renderer *renderer, GameEntity *player);
SDL_Texture *TransformImage(const char *bmp, SDL_Renderer *renderer);
void Platform_Set_Up(SDL_Rect *platforms);
void Ladder_Set_Up(SDL_Rect *ladders);
void BasicRender(SDL_Texture *texture, SDL_Surface *screen, SDL_Renderer *renderer,GameEntity *player);
void BasicSetUp(SDL_Rect *platforms, SDL_Rect *ladders);
bool OnFloor(GameEntity player, SDL_Rect *platforms);
void LevelView(Sdl &sdl, char *text, Data &data, Colors colors, GameEntity player, GameObjects &objects);
bool CheckLibrary(Sdl &sdl);
void PlayerPositionX(GameEntity &player, Check &value, double delta);
void PlayerPositionY(GameEntity &player, Check &value, GameObjects objects, Data data, double delta, int gravity);
void SetPlayerPosition(GameEntity &player, Check &value, GameObjects objects, Data data, double delta, int gravity);
void FallingWalkingStanding(double &gravity, Check &value, GameEntity &player, GameObjects objects, Data &data);
void TimeUpdate(Data &data, double &delta);
void Gravity(GameEntity player, GameObjects objects, double &gravity, Check &value);
void Input(Data &data, bool &quit, GameEntity &player, Check &value);

#endif //DONKEYKONG_MAINFUNCTIONS_H
