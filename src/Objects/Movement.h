//
// Created by admin on 20.12.2023.
//

#ifndef DONKEYKONG_MOVEMENT_H
#define DONKEYKONG_MOVEMENT_H

#include "../Magic/Magic.h"
#include "../Defines.h"

bool OnFloor(GameEntity player, SDL_Rect *platforms);
void PlayerPositionX(GameEntity &player, Check &value, double delta);
void PlayerPositionY(GameEntity &player, Check &value, GameObjects objects, Data data, double delta, int gravity);
void SetPlayerPosition(GameEntity &player, Check &value, GameObjects objects, double delta, double gravity);
void FallingWalkingStanding(double &gravity, Check &value, GameEntity &player, GameObjects objects, Data &data, double delta);
void Gravity(GameEntity &player, GameObjects &objects, double &gravity, Check &value);
void InTheFloor(GameEntity &player, SDL_Rect *platforms, Check values);
bool HeadCollision(GameEntity player, SDL_Rect *platforms, Check values);
void CheckConditionsForMovement(GameEntity &player, GameObjects objects, Check &value);
void GravityCollisionChecks(Check &value, GameEntity &player, GameObjects &objects, double &gravity, double delta);

#endif //DONKEYKONG_MOVEMENT_H
