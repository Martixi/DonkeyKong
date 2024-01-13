//
// Created by admin on 13.01.2024.
//

#ifndef DONKEYKONG_BARRELS_H
#define DONKEYKONG_BARRELS_H
#include "../Defines.h"

void BarrelActivation(GameEntity *barrels, Data data);
void BarrelReset(GameEntity *barrels);
void BarrelMovement(GameEntity *barrels, double barrelGravity, GameObjects objects, double delta);
void BarrelCollision(GameEntity &player, GameEntity *barrels, Data &data);
void BarrelsHandler(GameEntity &player, GameEntity *barrels, Data &data, GameObjects objects, double gravity, double delta);

#endif //DONKEYKONG_BARRELS_H
