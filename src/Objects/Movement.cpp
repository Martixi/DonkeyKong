//
// Created by admin on 20.12.2023.
//
#include "Movement.h"
#include "Ladders.h"
#include "../Drawing/Drawing.h"


bool OnFloor(GameEntity player, SDL_Rect *platforms){
	int x = (int) player.position.x + MAREK_WIDTH/2;
	int y = (int) player.position.y + MAREK_WIDTH;
	for (int i = 0; i < PLATFORMS; ++platforms) {
		i++;
		if ((y >= platforms->y
		and y < platforms->y + platforms->h)
		and (x >= platforms->x
		and x<= platforms->x + platforms->w)) return true;
	}
	return false;
}
void PlayerPositionX(GameEntity &player, Check &value, double delta){
	if (player.position.x < 0)
		player.position.x = 0;

	player.position.x += player.speed.x * delta;
	if (player.position.x > SCREEN_WIDTH - MAREK_WIDTH)
		player.position.x = SCREEN_WIDTH - MAREK_WIDTH;
}
void PlayerPositionY(GameEntity &player, Check &value, GameObjects objects, Data data, double delta, int gravity){
	player.speed.y += gravity * delta;
	player.position.y += player.speed.y * delta;
}
void SetPlayerPosition(GameEntity &player, Check &value, GameObjects objects, Data data, double delta, int gravity){
	PlayerPositionX(*&player, *&value, delta);
	PlayerPositionY(*&player, *&value, objects, data, delta, gravity);
}
void FallingWalkingStanding(double &gravity, Check &value, GameEntity &player, GameObjects objects, Data &data, double delta) {
	// perform checks
	value.onLadder = IsOnLadder(player, objects.ladders);

	if (!value.onLadder) {
		if (OnFloor(player, objects.platforms)) {
			// handle collision
			gravity = 0;
			// resolve collision FuckGoBack! don't move like that
			player.position.y -= player.speed.y * delta;
			player.speed.y = 0;

			// rememeber to set jump
			value.jump = false;
		} else {
			gravity = GRAVITY_VALUE;
		}
	} else {
		// now we are on ladder
		gravity = 0;
	}

	//Figuring out what player can do
	if (player.speed.y == 0 or !OnFloor(player, objects.platforms)) value.canWalk = true;
	else value.canWalk = false;
	if (player.speed.x == 0) value.canClimb = true;
	else value.canClimb = false;

	//Figuring out what player is doing
	if (gravity) value.falling = true;
	else value.falling = false;
	if (player.speed.x != 0){ value.walking = true; value.standing = false;}
	else {value.walking = false; value.standing = true;}

	//animating Marek
	MarekAnim(*&player, *&data, *&value, gravity);
}

void Gravity(GameEntity &player, GameObjects &objects, double &gravity, Check &value){
	if (OnFloor(player,objects.platforms)){
		gravity = 0;
		value.jump = false;

	}
	else if (IsOnLadder(player, objects.ladders)){
		if (value.canClimb or value.isClimbing){
			gravity = 0;
			value.jump = false;
		}
	}
	else {
		gravity = GRAVITY_VALUE;
		value.jump = true;
	}

}
