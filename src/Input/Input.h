//
// Created by admin on 20.12.2023.
//

#ifndef DONKEYKONG_INPUT_H
#define DONKEYKONG_INPUT_H
#include "../Defines.h"

void KeyN(GameEntity &player, GameEntity *barrels, Data &data);
void InputKey(Data &data, Check &value, GameEntity &player, GameEntity *barrels, GameObjects objects, bool &quit);
#endif //DONKEYKONG_INPUT_H
