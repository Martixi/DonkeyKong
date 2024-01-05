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
void SetPlayerPosition(GameEntity &player, Check &value, GameObjects objects, Data data, double delta, int gravity);
void FallingWalkingStanding(double &gravity, Check &value, GameEntity &player, GameObjects objects, Data &data, double delta);
void Gravity(GameEntity &player, GameObjects &objects, double &gravity, Check &value);


#endif //DONKEYKONG_MOVEMENT_H
