//
// Created by admin on 20.12.2023.
//
#include "Movement.h"
#include "Ladders.h"
#include "../Drawing/Drawing.h"

//Checks Game objects collision with floor
bool OnFloor(GameEntity player, SDL_Rect *platforms){
	int x = (int) player.position.x + player.width/2;
	int y = (int) player.position.y + player.width;
	for (int i = 0; i < PLATFORMS; ++platforms) {
		i++;
		if ((y >= platforms->y
		and y < platforms->y + platforms->h)
		and (x >= platforms->x
		and x<= platforms->x + platforms->w)) return true;
	}
	return false;
}

//Sets position of player on board
void SetPlayerPosition(GameEntity &player, Check &value, GameObjects objects, double delta, double gravity){
	if (player.position.x < 0)
		player.position.x = 0;

	player.position.x += player.speed.x * delta;
	if (player.position.x > SCREEN_WIDTH - MAREK_WIDTH)
		player.position.x = SCREEN_WIDTH - MAREK_WIDTH;

	InTheFloor(player, objects.platforms, value);

	player.speed.y += gravity * delta;
	player.position.y += player.speed.y * delta;
}

//Handles the gravity value of the player
void Gravity(GameEntity &player, GameObjects &objects, double &gravity, Check &value) {
	if (!IsOnLadder(player, objects.ladders)) value.isClimbing = false;

	if (OnFloor(player, objects.platforms)) {
		gravity = 0;
		value.jump = false;

	}
	if (IsOnLadder(player, objects.ladders)) {
		gravity = 0;
		value.jump = false;
		if (!value.ArrowDown and player.speed.y > 0) player.speed.y = 0;
	} else {
		gravity = GRAVITY_VALUE;
	}
}

//Correction of player if stuck in floor
void InTheFloor(GameEntity &player, SDL_Rect *platforms, Check values) {
	double feet = (player.position.y + player.height) - 1;
	if (!values.isClimbing) {
		for (int i = 0; i < PLATFORMS; ++i) {
			if (feet >= platforms->y and feet <= platforms->y + platforms->h
			    and (int) player.position.x + player.width / 2 >= platforms->x
			    and (int) player.position.x + player.width / 2 <= platforms->x + platforms->w) {
				player.position.y = platforms->y - player.height;
			}
			++platforms;
		}
	}
}

//Collision of player with sealing
bool HeadCollision(GameEntity player, SDL_Rect *platforms, Check values) {
	double head = player.position.y;
	if (!values.isClimbing) {
		for (int i = 0; i < PLATFORMS; ++i) {
			if (head > platforms->y + platforms->h - 10 and head <= platforms->y + platforms->h
			    and (int) player.position.x + player.width / 2 >= platforms->x
			    and (int) player.position.x + player.width / 2 <= platforms->x + platforms->w) {
				return true;
			}
			++platforms;
		}
	}
	return false;
}

void CheckConditionsForMovement(GameEntity &player, GameObjects objects, Check &value){
	if (player.speed.y == 0 or !OnFloor(player, objects.platforms)) value.canWalk = true;
	else value.canWalk = false;
	if (player.speed.x == 0 and IsOnLadder(player, objects.ladders)) value.canClimb = true;
	else value.canClimb = false;

}

//Special adjustments for different scenarios connected to gravity
void GravityCollisionChecks(Check &value, GameEntity &player, GameObjects &objects, double &gravity, double delta){
	value.collidingFloor = OnFloor(player, objects.platforms);
	value.onLadder = IsOnLadder(player, objects.ladders);
	//hitting the platform with players head
	if (!IsOnLadder(player, objects.ladders)) {
		if (HeadCollision(player, objects.platforms, value)) {
			gravity = GRAVITY_VALUE;
			player.position.y -= player.speed.y * delta - gravity * delta;
			player.position.x -= player.speed.x * delta;
			player.speed.y = 0;

			value.isClimbing = false;
		}
		//player has fallen on to floor
		else if (OnFloor(player, objects.platforms)) {
			gravity = 0;
			player.position.y -= player.speed.y * delta;
			player.speed.y = 0;
			value.isClimbing = false;
			value.jump = false;
		}
		//player is falling
		else {
			gravity = GRAVITY_VALUE;
		}
	} else {
		//player's on ladder
		gravity = 0;
	}
}