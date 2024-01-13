//
// Created by admin on 20.12.2023.
//

#ifndef DONKEYKONG_DEFINES_H
#define DONKEYKONG_DEFINES_H
#include "Magic/Magic.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//Portals
#define PORTAL_WIDTH 64
#define PORTAL_HEIGHT 16
#define PORTAL_X 225
#define PORTAL_Y 111

//Marek data
#define MAREK_X 18
#define MAREK_Y 400
#define MAREK_WIDTH 32
#define MAREK_SPEED 70
#define MAREK_JUMP 170
#define LADDER_SPEED 100
#define GRAVITY_VALUE 180

//Barrels
#define BARRELS_AMOUNT 6
#define BARRELS_WIDTH 16
#define BARRELS_HEIGHT 18
#define BARRELS_X 250
#define BARRELS_Y 114
#define BARREL_SPEED 70
#define BARREL_FREQUENCY 5

//Platforms
#define PLATFORMS 6
#define PLATFORM_HEIGHT 15
#define PLATFORM1_X 0
#define PLATFORM1_Y 465
#define PLATFORM1_WIDTH SCREEN_WIDTH
#define PLATFORM2_X 45
#define PLATFORM2_Y 389
#define PLATFORM2_WIDTH (SCREEN_WIDTH-100)
#define PLATFORM3_X 52
#define PLATFORM3_Y 315
#define PLATFORM3_WIDTH (SCREEN_WIDTH-127)
#define PLATFORM4_X 85
#define PLATFORM4_Y 241
#define PLATFORM4_WIDTH (SCREEN_WIDTH-180)
#define PLATFORM5_X 106
#define PLATFORM5_Y 168
#define PLATFORM5_WIDTH (SCREEN_WIDTH-224)
#define PLATFORM6_X 165
#define PLATFORM6_Y 91
#define PLATFORM6_WIDTH (SCREEN_WIDTH-343)

//Ladders
#define LADDERS 9
#define LADDERS_WIDTH 20
#define LADDERS_HEIGHT 76

//fps data
#define FPS_REFRESH_TIME 0.5
#define FPS_ADJUSTED_TIME (1 / FPS_REFRESH_TIME)

//structs
struct Position{
	double x;
	double y;
};
struct Speed{
	double x = 0;
	double y = 0;
};
struct GameEntity{
	SDL_Texture *image;
	SDL_Rect size;
	Position position;
	int currentFrame;
	int width;
	int height;
	Speed speed;
};
struct Check{
	bool onLadder = false;
	bool isClimbing = false;
	bool falling = false;
	bool  walking = false;
	bool standing = true;
	bool canWalk = true;
	bool canClimb = false;
	bool jump = false;
	bool collidingFloor = false;
	bool ArrowDown = false;
	bool ArrowUp = false;

};
struct Sdl{
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	SDL_Surface *screen, *charset, *Background, *Level, *Enemy;
	SDL_Texture *texture;
};
struct GameObjects{
	SDL_Rect platforms[PLATFORMS], ladders[LADDERS];
};
struct Data{
	double fpsTimer = 0, fps = 0, worldTime = 0;
	double jumpValue = 0, moveValue = 0;
	int AnimFrames = 0, maxFrames = 8, frameChange = 50;
	int AnimFramesEnemy = 0, maxFramesEnemy = 2, frameChangeEnemy = 80;
	int AnimFramesBarrels = 0, maxFramesBarrel = 4, frameChangeBarrels = 35;
	int AnimFramesPortal = 0, maxFramesPortal = 7, frameChangePortal = 50;
	Uint32 startTick = SDL_GetTicks(), endTick, frames = 0;
	SDL_Event event;
};
struct Colors{
	Uint32 black;
	Uint32 cyan;
	Uint32 red;
};

#endif //DONKEYKONG_DEFINES_H
