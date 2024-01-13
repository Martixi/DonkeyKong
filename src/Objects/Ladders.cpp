//
// Created by admin on 03.01.2024.
//

#include "Ladders.h"
#include "../Magic/Magic.h"
#include "../Defines.h"


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
int LadderOff(GameEntity player, SDL_Rect *platforms){
	int y = (int) player.position.y + MAREK_WIDTH;
	for (int i = 0; i < PLATFORMS; ++platforms) {
		++i;
		if (y == platforms->y+1 ) return (int) player.position.y -1;
		if (y == platforms->y-1 ) return (int) player.position.y +1;
	}
	return (int) player.position.y;
}
