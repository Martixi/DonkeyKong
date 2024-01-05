#include "Magic/Magic.h"
#include "Defines.h"
#include "GameRenderSetUp/BuildRender.h"
#include "Objects/Movement.h"
#include "Input/Input.h"
#include "Objects/Ladders.h"
#include "Drawing/Drawing.h"



int main(int argc, char **args) {
	Sdl sdl;
	GameEntity player;
	GameObjects objects{};
	Check value;
	Data data;
	Colors colors{};
	char text[128];
	bool quit = false;
	double delta, gravity = 0;

	if (!CheckLibrary(sdl)) return 1;
	PrepareGame(sdl, objects, player, colors);

	// Actual game ---->
	while (!quit) {
		if (!IsOnLadder(player, objects.ladders)) value.isClimbing = false;

		//--------------gravity---------------//
		if (OnFloor(player,objects.platforms)){
			gravity = 0;
			value.jump = false;

		}
		if (IsOnLadder(player, objects.ladders)){
			gravity = 0;
			value.jump = false;
			if (!value.ArrowDown and player.speed.y > 0)  player.speed.y = 0;
		}
		else {
			gravity = GRAVITY_VALUE;
			value.jump = true;
		}
		//--------------gravity---------------//

		//position x and y
		if (player.position.x < 0)
			player.position.x = 0;

		player.position.x += player.speed.x * delta;
		if (player.position.x > SCREEN_WIDTH - MAREK_WIDTH)
			player.position.x = SCREEN_WIDTH - MAREK_WIDTH;

		player.speed.y += gravity * delta;
		player.position.y += player.speed.y * delta;
		//CorrectPlayerPositionY(player, objects.platforms, value, gravity);

		//position x and y

		// perform checks
		value.collidingFloor = OnFloor(player, objects.platforms);
		value.onLadder = IsOnLadder(player, objects.ladders);

		if (!IsOnLadder(player, objects.ladders)) {
			if (OnFloor(player, objects.platforms)) {
				gravity = 0;
				player.position.y -= player.speed.y * delta;
				player.speed.y = 0;
				value.isClimbing = false;

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
		if (player.speed.x == 0 and IsOnLadder(player, objects.ladders)) value.canClimb = true;
		else value.canClimb = false;




		//animating Marek
		MarekAnim(*&player, *&data, *&value, gravity);

		TimeUpdate(*&data, *&delta);
		LevelView(sdl, text, data, colors, player, objects);

		while (SDL_PollEvent(&data.event)) {
			switch (data.event.type) {
				case SDL_KEYDOWN:
					if (data.event.key.keysym.sym == SDLK_ESCAPE) quit = true; // Esc = Quit
					else if (data.event.key.keysym.sym == SDLK_n) {
						player.position.x = MAREK_X;
						player.position.y = MAREK_Y;
						player.speed.x = 0;
						player.speed.y = 0;
						data.worldTime = 0;
					} else if (data.event.key.keysym.sym == SDLK_RIGHT and value.canWalk and !value.isClimbing) player.speed.x = MAREK_SPEED;
					else if (data.event.key.keysym.sym == SDLK_LEFT and value.canWalk and !value.isClimbing) player.speed.x = -MAREK_SPEED;
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
					if (data.event.key.keysym.sym == SDLK_DOWN){
						if (value.onLadder) {
							player.speed.y = 0;
						}
						value.ArrowDown = false;
					}else if (data.event.key.keysym.sym == SDLK_UP) {
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
	return 0;
}