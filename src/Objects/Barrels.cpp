//
// Created by admin on 13.01.2024.
//

#include "Barrels.h"
#include "../Defines.h"
#include "Ladders.h"
#include "Movement.h"
#include "../Input/Input.h"




void BarrelActivation(GameEntity *barrels, Data data){
	if (data.worldTime > 45) return;
	if ((int) data.worldTime == BARREL_FREQUENCY){
		barrels[0].speed.x = -BARREL_SPEED;
	}
	if ((int) data.worldTime == BARREL_FREQUENCY*2){
		barrels[1].speed.x = BARREL_SPEED;
	}
	if ((int) data.worldTime == BARREL_FREQUENCY*3){
		barrels[2].speed.x = -BARREL_SPEED;
	}
	if ((int) data.worldTime == BARREL_FREQUENCY*4){
		barrels[3].speed.x = BARREL_SPEED;
	}
	if ((int) data.worldTime == BARREL_FREQUENCY*5){
		barrels[4].speed.x = -BARREL_SPEED;
	}
	if ((int) data.worldTime == BARREL_FREQUENCY*6){
		barrels[5].speed.x = BARREL_SPEED;
	}
}

void BarrelReset(GameEntity *barrels){
	for (int i = 0; i < BARRELS_AMOUNT; ++i) {
		if (barrels[i].position.y > SCREEN_HEIGHT){
			barrels[i].position.x = BARRELS_X;
			barrels[i].position.y = BARRELS_Y;
			barrels[i].speed.y = 0;
		}
	}
}

void BarrelMovement(GameEntity *barrels, double barrelGravity, GameObjects objects, double delta){
	for (int i = 0; i < BARRELS_AMOUNT; ++i) {
		if (barrels[i].position.x == BARRELS_X) barrelGravity = 0;
		else if (IsOnLadder(barrels[i], objects.ladders)){
			barrelGravity = 80;
			barrels[i].speed.x = barrels[i].speed.x*(-1);
		}
		else if (OnFloor(barrels[i], objects.platforms)) barrelGravity = 0, barrels[i].speed.y = 0;
		else barrelGravity = 80;

		barrels[i].speed.y += barrelGravity*delta;
		if (barrels[i].speed.y == 0){
			barrels[i].position.x += barrels[i].speed.x*delta;
		}
		barrels[i].position.y += barrels[i].speed.y*delta;
	}
}
void BarrelCollision(GameEntity &player, GameEntity *barrels, Data &data){
	double playerLeft = player.position.x +5;
	double playerRight = player.position.x + player.width-10, playerFeet = player.position.y + player.height;
	for (int i = 0; i < BARRELS_AMOUNT; ++i) {
		double barrelRight = barrels[i].position.x + barrels[i].width;
		double barrelBottom = barrels[i].position.y + barrels[i].height;
		if (playerRight >= barrels[i].position.x and
		    playerLeft <= barrelRight and
		    playerFeet >= barrels[i].position.y and
		    player.position.y <= barrelBottom){
			KeyN(player, barrels, data);
			return;
		}
		if (playerRight >= barrels[i].position.x and
		    playerRight <= barrelRight and
		    playerFeet >= barrels[i].position.y and
		    playerFeet <= barrelBottom){
			KeyN(player, barrels, data);
			return;
		}
	}

}

void BarrelsHandler(GameEntity &player, GameEntity *barrels, Data &data, GameObjects objects, double gravity, double delta){
	BarrelActivation(barrels, data);
	BarrelCollision(player, barrels, data);
	BarrelMovement(barrels, gravity, objects, delta);
	BarrelReset(barrels);
}