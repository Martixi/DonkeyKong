//
// Created by admin on 20.12.2023.
//
#include "../Magic/Magic.h"
#include "Input.h"
#include "../Objects/Movement.h"

void KeyN(GameEntity &player, GameEntity *barrels, Data &data){
	player.position.x = MAREK_X;
	player.position.y = MAREK_Y;
	player.speed.x = 0;
	player.speed.y = 0;
	data.worldTime = 0;
	for (int i = 0; i < BARRELS_AMOUNT; ++i) {
		barrels[i].position.x = BARRELS_X;
		barrels[i].position.y = BARRELS_Y;
		barrels[i].speed.x = 0;
		barrels[i].speed.y = 0;
	}
}

void InputKey(Data &data, Check &value, GameEntity &player, GameEntity *barrels, GameObjects objects, bool &quit){
	while (SDL_PollEvent(&data.event)) {
		switch (data.event.type) {
			case SDL_KEYDOWN:
				if (data.event.key.keysym.sym == SDLK_ESCAPE) quit = true; // Esc = Quit
				else if (data.event.key.keysym.sym == SDLK_n) {
					KeyN(player, barrels, data);
				} else if (data.event.key.keysym.sym == SDLK_RIGHT and value.canWalk and !value.isClimbing)
					player.speed.x = MAREK_SPEED;
				else if (data.event.key.keysym.sym == SDLK_LEFT and value.canWalk and !value.isClimbing)
					player.speed.x = -MAREK_SPEED;
				else if (data.event.key.keysym.sym == SDLK_UP and value.onLadder and value.canClimb) {
					player.speed.y = -LADDER_SPEED;
					value.isClimbing = true;
					value.ArrowUp = true;
				} else if (data.event.key.keysym.sym == SDLK_DOWN and value.onLadder and value.canClimb) {
					player.speed.y = LADDER_SPEED;
					value.isClimbing = true;
					value.ArrowDown = true;
				} else if (data.event.key.keysym.sym == SDLK_SPACE and !value.jump and !value.onLadder) {
					value.jump = true;
					player.speed.y = -MAREK_JUMP;
				}
				break;
			case SDL_KEYUP:
				if (data.event.key.keysym.sym == SDLK_DOWN) {
					if (value.onLadder) {
						player.speed.y = 0;
					}
					value.ArrowDown = false;
				} else if (data.event.key.keysym.sym == SDLK_UP) {
					if (value.onLadder) {
						player.speed.y = 0;
					}
					value.ArrowUp = false;
					if (!value.onLadder and OnFloor(player, objects.platforms)) data.moveValue = 0;
				} else if (data.event.key.keysym.sym == SDLK_RIGHT or data.event.key.keysym.sym == SDLK_LEFT) {
					player.speed.x = 0;
				}
				break;
			case SDL_QUIT:
				quit = true;
				break;
		}
	}

	data.frames++;
}
