#include "Magic/Magic.h"
#include "Defines.h"
#include "GameRenderSetUp/BuildRender.h"
#include "Objects/Movement.h"
#include "Input/Input.h"
#include "Objects/Ladders.h"
#include "Drawing/Drawing.h"
#include "Objects/Barrels.h"
int main(int argc, char **args) {
	Sdl sdl;
	GameEntity player, enemy, barrels[BARRELS_AMOUNT], portal;
	GameObjects objects{};
	Check value;
	Data data;
	Colors colors{};
	char text[128];
	bool quit = false;
	double delta, gravity = 0, barrelGravity = 0;
	//preparing for game
	if (!CheckLibrary(sdl)) return 1;
	PrepareGame(sdl, objects, player, colors, enemy, barrels, portal);
	// Game loop
	while (!quit) {
		BarrelsHandler(player, barrels, data, objects, barrelGravity, delta);
		Gravity(player, objects, gravity, value);
		//position x and y
		SetPlayerPosition(player, value, objects, delta, gravity);
		// perform checks
		GravityCollisionChecks(value, player, objects, gravity, delta);
		//Figuring out what player can do
		CheckConditionsForMovement(player, objects, value);
		Animations(player, data, value, enemy, portal, barrels, gravity);
		//Game update
		TimeUpdate(data, *&delta);
		LevelView(sdl, text, data, colors, player, objects, enemy, barrels, portal);
		//player Input
		InputKey(data, value, player, barrels, objects, quit);
	}
	return 0;
}