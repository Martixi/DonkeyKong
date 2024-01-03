#include "Magic.h"
#include "Defines.h"
#include "MainFunctions.h"

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

	if (!CheckLibrary(*&sdl)) return 1;
	PrepareGame(*&sdl, *&objects, *&player, *&colors);

	while (!quit) {
		Gravity(player, objects, *&gravity, *&value);
		SetPlayerPosition(*&player, *&value, objects, data, delta, gravity);
		FallingWalkingStanding(*&gravity, *&value, *&player, objects, *&data);
		TimeUpdate(*&data, *&delta);
		LevelView(*&sdl, text, *&data, colors, player, objects);
		Input(*&data, *&quit, *&player, *&value);
}
	return 0;
}