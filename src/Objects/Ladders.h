//
// Created by admin on 03.01.2024.
//

#ifndef DONKEYKONG_LADDERS_H
#define DONKEYKONG_LADDERS_H
#include "../Magic/Magic.h"
#include "../Defines.h"

bool IsOnLadder(GameEntity player, SDL_Rect *ladders);
int LadderOff(GameEntity player, SDL_Rect *platforms);


#endif //DONKEYKONG_LADDERS_H
