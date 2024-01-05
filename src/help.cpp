//#include "cmath"
//#include "cstdio"
//#include "cstring"
//#include "Magic/Magic.h"
//#include "Defines.h"
//#include "Drawing/Drawing.h"
//
//
////struct Position {
////	double x;
////	double y;
////};
////
////struct Speed {
////	double x = 0;
////	double y = 0;
////};
////
////struct GameEntity {
////	SDL_Texture *image;
////	SDL_Rect size;
////	Position position;
////	int currentFrame;
////	int width;
////	int height;
////	Speed speed;
////};
////
////
////SDL_Texture *TransformImage(const char *bmp, SDL_Renderer *renderer) {
////	SDL_Surface *temporary = SDL_LoadBMP(bmp);
////	SDL_SetColorKey(temporary, true, 0x000000);
////	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, temporary);
////	SDL_FreeSurface(temporary);
////	return texture;
////}
////
////
////void GenerateEntity(GameEntity *player, SDL_Renderer *renderer, const char *bmp, int width, int height, int startingX,
////					int startingY) {
////	player->image = TransformImage(bmp, renderer);
////	player->currentFrame = 0;
////	player->width = width;
////	player->height = height;
////	player->position.x = startingX;
////	player->position.y = startingY;
////	player->size = {0, 0, width, height};
////}
////
////
////void RenderPlayer(SDL_Renderer *renderer, GameEntity *player) {
////	SDL_Rect destination = {
////		int(player->position.x),
////		int(player->position.y),
////		player->size.w,
////		player->size.h
////	};
////	if (player->speed.x < 0)
////		SDL_RenderCopyEx(renderer, player->image, &player->size, &destination, 0, nullptr, SDL_FLIP_HORIZONTAL);
////	else SDL_RenderCopy(renderer, player->image, &player->size, &destination);
////}
////
////
////void BasicRender(SDL_Texture *texture, SDL_Surface *screen, SDL_Renderer *renderer, GameEntity *player) {
////	SDL_UpdateTexture(texture, nullptr, screen->pixels, screen->pitch);
////	SDL_RenderClear(renderer);
////	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
////	RenderPlayer(renderer, player);
////	SDL_RenderPresent(renderer);
////}
////
////
////void Platform_Set_Up(SDL_Rect *platforms) {
////	int platform = 0;
////	platforms[platform++] = {PLATFORM1_X, PLATFORM1_Y, PLATFORM1_WIDTH, PLATFORM_HEIGHT};
////	platforms[platform++] = {PLATFORM2_X, PLATFORM2_Y, PLATFORM2_WIDTH, PLATFORM_HEIGHT};
////	platforms[platform++] = {PLATFORM3_X, PLATFORM3_Y, PLATFORM3_WIDTH, PLATFORM_HEIGHT};
////	platforms[platform++] = {PLATFORM4_X, PLATFORM4_Y, PLATFORM4_WIDTH, PLATFORM_HEIGHT};
////	platforms[platform++] = {PLATFORM5_X, PLATFORM5_Y, PLATFORM5_WIDTH, PLATFORM_HEIGHT};
////	platforms[platform] = {PLATFORM6_X, PLATFORM6_Y, PLATFORM6_WIDTH, PLATFORM_HEIGHT};
////}
////
////
////void Ladder_Set_Up(SDL_Rect *ladders) {
////	int ladder = 0;
////	ladders[ladder++] = {295, PLATFORM2_Y, LADDERS_WIDTH, LADDERS_HEIGHT};
////	ladders[ladder++] = {420, PLATFORM2_Y, LADDERS_WIDTH, LADDERS_HEIGHT};
////	ladders[ladder++] = {73, PLATFORM3_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 2};
////	ladders[ladder++] = {524, PLATFORM3_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 2};
////	ladders[ladder++] = {271, PLATFORM4_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 2};
////	ladders[ladder++] = {340, PLATFORM4_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 2};
////	ladders[ladder++] = {134, PLATFORM5_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 3};
////	ladders[ladder++] = {482, PLATFORM5_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 3};
////	ladders[ladder] = {391, PLATFORM6_Y, LADDERS_WIDTH, LADDERS_HEIGHT + 1};
////
////}
////
////
////bool IsOnLadder(GameEntity player, SDL_Rect *ladders) {
////	int player_center_x = (int) player.position.x + MAREK_WIDTH / 2;
////	int player_foots = (int) player.position.y + MAREK_WIDTH;
////	for (int i = 0; i < LADDERS; ladders++) {
////		if ((player_center_x > ladders->x) and
////			(player_center_x < ladders->x + ladders->w) and
////			(player_foots >= ladders->y) and
////			(player_foots <= ladders->y + ladders->h)) {
////			return true;
////		}
////		++i;
////	}
////	return false;
////}
////
////
////int LadderOff(GameEntity player, SDL_Rect *platforms) {
////	int y = (int) player.position.y + MAREK_WIDTH;
////	for (int i = 0; i < PLATFORMS; ++platforms) {
////		++i;
////		if (y == platforms->y + 1) return -1;
////		if (y == platforms->y - 1) return 1;
////	}
////	return 0;
//////}
//////
////
////bool OnFloor(GameEntity player, SDL_Rect *platforms) {
////	int x = (int) player.position.x + MAREK_WIDTH / 2;
////	int y = (int) player.position.y + MAREK_WIDTH;
////	for (int i = 0; i < PLATFORMS; ++platforms) {
////		i++;
////		if ((y >= platforms->y and y < platforms->y + platforms->h) and
////			(x >= platforms->x and x <= platforms->x + platforms->w))
////			return true;
////	}
////	return false;
////}
//////
////int Gravity(GameEntity player, SDL_Rect *platforms, SDL_Rect *ladders) {
////	if (OnFloor(player, platforms) or IsOnLadder(player, ladders)) return 0;
////	else return 150;
////}
//
//int main(int argc, char **args) {
//
//	SDL_Window *window = nullptr;
//	SDL_Renderer *renderer = nullptr;
//	SDL_Rect platforms[PLATFORMS], ladders[LADDERS];
//	SDL_Surface *screen;
//	SDL_Surface *charset;
//	SDL_Texture *texture;
//	SDL_Surface *Background;
//	SDL_Surface *Level;
//	GameEntity player;
//	//SDL_Surface barriers[]=
//
//	char text[128];
//
//	Platform_Set_Up(platforms);
//	Ladder_Set_Up(ladders);
//	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//		printf("SDL_Init error: %s\n", SDL_GetError());
//		return 1;
//	}
//
//	int initError = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
//	if (initError != 0) {
//		SDL_Quit();
//		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
//		return 1;
//	}
//
//	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//	SDL_SetWindowTitle(window, "Hello there. General Kenobi!");
//
//	loadAllTextures(screen, charset, Background, Level);
//
//	// Generating Marek
//	GenerateEntity(&player, renderer, "static/Marek.bmp", MAREK_WIDTH, MAREK_WIDTH, MAREK_X, MAREK_Y);
//	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
//								SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	Uint32 black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
//	Uint32 green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
//	Uint32 cyan = SDL_MapRGB(screen->format, 0x79, 0xEE, 0xE3);
//	Uint32 red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
//
//	Uint32 startTick = SDL_GetTicks(), endTick;
//	double delta;
//
//	Uint32 frames = 0; // count of frames in between each check
//	double fpsTimer = 0; // +- how much time has passed between showing last frame count
//	double fps = 0; // recalculated value of Frames Per Second
//
//	double worldTime = 0; // how much time has passed since the start of the game
//
//	double distance = 0; // reserve a variable for storing the distance that was covered
//	double MarekSpeed = 1; // speed multiplier for the future
//	double gravity = 0;
//	double jumpValue = 0;
//	double moveValue = 0;
//
//	SDL_Event event;
//	bool quit = false;
//	bool onLadder = false;
//	bool wasOnLadder = false;
//	bool isClimbing = false;
//	bool falling = false;
//	bool walking = false;
//	bool standing = true;
//	bool canWalk = true;
//	bool canClimb = false;
//	bool jump = false;
//
//	bool collidingFloor = false;
//
//
//	int AnimFrames = 0;
//	int maxFrames = 8;
//	int frameChange = 50;
//	while (!quit) {
//		// Measure time separate function? maybe?
//		endTick = SDL_GetTicks();
//		delta = (endTick - startTick) * 0.001;
//		startTick = endTick;
//		worldTime += delta;
//		fpsTimer += delta;
//		if (fpsTimer > FPS_REFRESH_TIME) {
//			fps = frames * FPS_ADJUSTED_TIME;
//			frames = 0;
//			fpsTimer -= FPS_REFRESH_TIME;
//		}
//
//		/*---------HERE-------*/
//
//		// handle input
//
//		// update positions
//		player.speed.y += gravity * delta;
//
//		player.position.y += player.speed.y * delta;
//		if (player.position.x < 0)
//			player.position.x = 0;
//
//		player.position.x += player.speed.x * delta;
//		if (player.position.x > SCREEN_WIDTH - MAREK_WIDTH)
//			player.position.x = SCREEN_WIDTH - MAREK_WIDTH;
//
//		// perform checks
//		collidingFloor = OnFloor(player, platforms);
//		onLadder = IsOnLadder(player, ladders);
//
//		if (!onLadder) {
//			if (collidingFloor) {
//				// handle collision
//				gravity = 0;
//				// resolve collision FuckGoBack! don't move like that
//				player.position.y -= player.speed.y * delta;
//				player.speed.y = 0;
//
//				// rememeber to set jump
//				jump = false;
//			} else {
//				gravity = 180;
//			}
//		} else {
//			// now we are on ladder
//			gravity = 0; // make sure there is no gravity
//			if (collidingFloor) {
//				player.position.y -= 30*delta;
//			}
////			player.position.y += LadderOff(player, ladders);
//		}
//
//		// render
//
//		/*if (player.speed.y == 0 or !OnFloor(player, platforms)) canWalk = true;
//		else canWalk = false;
//		if (player.speed.x == 0) canClimb = true;
//		else canClimb = false;
//
//		if (OnFloor(player, platforms) or IsOnLadder(player, ladders)) {
//			gravity = 0;
//			jump = false;
//		} else {
//			gravity = 150;
//			jump = true;
//		}
//
//		if (!isClimbing)player.position.x += player.speed.x * delta;
//		if (player.position.x < 0) player.position.x = 0;
//		if (player.position.x > SCREEN_WIDTH - MAREK_WIDTH) player.position.x = SCREEN_WIDTH - MAREK_WIDTH;
//
//		player.speed.y += gravity * delta;
//		if (OnFloor(player, platforms)) player.speed.y = 0;
//
//		player.position.y += player.speed.y * delta + moveValue * delta + jumpValue;
//		onLadder = IsOnLadder(player, ladders);
//		if (wasOnLadder and !onLadder) {
//			player.position.y = LadderOff(player, platforms);
//			isClimbing = false;
//		}
//		wasOnLadder = onLadder;
//
////		if (gravity) falling = true;
////		else falling = false;
////		if (player.speed.x != 0) {
////			walking = true;
////			standing = false;
////		}
////		else {
////			walking = false;
////			standing = true;
////		}*/
//
//		/*---------HERE-------*/
//
//		// Animation stuff for player separate function
//		if (AnimFrames % frameChange == 0) {
//			player.currentFrame += 1;
//			player.size.x = player.size.w * player.currentFrame;
//		}
//		if (AnimFrames % (frameChange * (maxFrames - 1)) == 0 or player.currentFrame > 7) {
//			player.currentFrame = 0;
//		}
//		AnimFrames++;
//		if (falling) {
//			player.currentFrame = 7;
//		} else if (standing) player.currentFrame = 8;
//
//		SDL_FillRect(screen, nullptr, black);
//		DrawSurface(screen, Level, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
//		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, cyan, black);
//
//		snprintf(text, 128, "Pieklo jest na ziemi, czas cierpienia = %.1lf s  %.0lf klatek / s", worldTime, fps);
//
//		// see that string above? Yes, show this one. Centered on the screen
//		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
//		snprintf(text, 128, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
//
//		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
//
//		BasicRender(texture, screen, renderer, &player);
//
//		while (SDL_PollEvent(&event)) {
//
//			switch (event.type) {
//				case SDL_KEYDOWN:
//					if (event.key.keysym.sym == SDLK_ESCAPE) quit = true; // Esc = Quit
//					else if (event.key.keysym.sym == SDLK_n) {
//						player.position.x = MAREK_X;
//						player.position.y = MAREK_Y;
//						player.speed.x = 0;
//						player.speed.y = 0;
//						worldTime = 0;
//					} else if (event.key.keysym.sym == SDLK_RIGHT and canWalk) player.speed.x = MAREK_SPEED;
//					else if (event.key.keysym.sym == SDLK_LEFT and canWalk) player.speed.x = -MAREK_SPEED;
//					else if (event.key.keysym.sym == SDLK_UP and onLadder) {
////						moveValue = -LADDER_SPEED;
//						player.speed.y = -LADDER_SPEED;
//						isClimbing = true;
//					} else if (event.key.keysym.sym == SDLK_DOWN and onLadder) {
////						moveValue = LADDER_SPEED;
//						player.speed.y = LADDER_SPEED;
//						isClimbing = true;
//					} else if (event.key.keysym.sym == SDLK_SPACE and !jump and !onLadder) {
//						jump = true;
//						player.speed.y = -180;
//					}
//					break;
//				case SDL_KEYUP:
//					if (event.key.keysym.sym == SDLK_UP or event.key.keysym.sym == SDLK_DOWN) {
//						if (onLadder) {
//							player.speed.y = 0;
//						}
////						if (!onLadder and OnFloor(player, platforms)) moveValue = 0;
//					} else if (event.key.keysym.sym == SDLK_RIGHT or event.key.keysym.sym == SDLK_LEFT) {
//						player.speed.x = 0;
//					}
//					break;
//				case SDL_QUIT:
//					quit = true;
//					break;
//			}
//		}
//
//		frames++;
//	}
//
//	return 0;
//}
