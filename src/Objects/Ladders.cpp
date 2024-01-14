//
// Created by admin on 03.01.2024.
//

#include "Ladders.h"
#include "../Other/Other.h"
#include "../Defines.h"

//Checks if player is currently on the ladder
bool IsOnLadder(GameEntity player, SDL_Rect *ladders){
	int player_center_x = (int) player.position.x + player.width/2;
	float player_foots = (float) player.position.y + player.width;
	for (int i = 0; i < LADDERS; ladders++) {
		if ((player_center_x > ladders->x) and
		    (player_center_x < ladders->x + ladders->w) and
		    (player_foots >= (float) ladders->y) and
		    (player_foots <= (float) (ladders->y+ladders->h))){
			return true;
		}
		++i;
	}
	return false;
}
