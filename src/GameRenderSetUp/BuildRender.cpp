//
// Created by admin on 03.01.2024.
//

#include "BuildRender.h"
#include "../Drawing/Drawing.h"

void
PrepareGame(Sdl &sdl, GameObjects &objects, GameEntity &player, Colors &colors, GameEntity &enemy, GameEntity *barrels,
            GameEntity &portal) {
	SDL_RenderSetLogicalSize(sdl.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(sdl.window, "Marek the demon slayer");
	loadAllTextures(sdl.screen, sdl.charset, sdl.Background, sdl.Level, sdl.Enemy);
	BasicSetUp(objects.platforms, objects.ladders);
	GenerateEntity(&player, sdl.renderer, "static/Marek.bmp", MAREK_WIDTH, MAREK_WIDTH, MAREK_X, MAREK_Y);
	GenerateEntity(&enemy, sdl.renderer, "static/Bogdan.bmp", 64, 64, SCREEN_WIDTH / 2 - 37, 104);
	for (int i = 0; i < BARRELS_AMOUNT; ++i) {
		GenerateEntity(&barrels[i], sdl.renderer, "static/Barrels.bmp", BARRELS_WIDTH, BARRELS_HEIGHT, BARRELS_X, BARRELS_Y);
	}
	GenerateEntity(&portal, sdl.renderer, "static/PortalForBarrels.bmp", PORTAL_WIDTH, PORTAL_HEIGHT, PORTAL_X, PORTAL_Y);

	sdl.texture = SDL_CreateTexture(sdl.renderer, SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	colors = {SDL_MapRGB(sdl.screen->format, 0x00, 0x00, 0x00), SDL_MapRGB(sdl.screen->format, 0x79, 0xEE, 0xE3),
	          SDL_MapRGB(sdl.screen->format, 0xFF, 0x00, 0x00)};
}

//creating an entity for ex: player, barrel, enemy etc...

void GenerateEntity(GameEntity *player, SDL_Renderer *renderer, const char *bmp, int width, int height, int startingX,
                    int startingY) {
	player->image = TransformImage(bmp, renderer);
	player->currentFrame = 0;
	player->width = width;
	player->height = height;
	player->position.x = startingX;
	player->position.y = startingY;
	player->size = {0, 0, width, height};
}


//Rendering a player

void RenderPlayer(SDL_Renderer *renderer, GameEntity *player) {
	SDL_Rect destination = {
			int(player->position.x),
			int(player->position.y),
			player->size.w,
			player->size.h
	};
	if (player->speed.x < 0)
		SDL_RenderCopyEx(renderer, player->image, &player->size, &destination, 0, nullptr, SDL_FLIP_HORIZONTAL);
	else SDL_RenderCopy(renderer, player->image, &player->size, &destination);
}

void RenderEnemy(SDL_Renderer *renderer, GameEntity *enemy) {
	SDL_Rect destination = {
			int(enemy->position.x),
			int(enemy->position.y),
			enemy->size.w,
			enemy->size.h
	};
	SDL_RenderCopy(renderer, enemy->image, &enemy->size, &destination);
}

void RenderBarrel(SDL_Renderer *renderer, GameEntity *barrel){
	SDL_Rect destination = {
			int(barrel->position.x),
			int(barrel->position.y),
			barrel->size.w,
			barrel->size.h
	};
	SDL_RenderCopy(renderer, barrel->image, &barrel->size, &destination);

}

//creating a texture
SDL_Texture *TransformImage(const char *bmp, SDL_Renderer *renderer) {
	SDL_Surface *temporary = SDL_LoadBMP(bmp);
	SDL_SetColorKey(temporary, true, 0x000000);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, temporary);
	SDL_FreeSurface(temporary);
	return texture;
}

//setting up platforms and ladders
void Platform_Set_Up(SDL_Rect *platforms) {
	int platform = 0;
	platforms[platform++] = {PLATFORM1_X, PLATFORM1_Y, PLATFORM1_WIDTH, PLATFORM_HEIGHT};
	platforms[platform++] = {PLATFORM2_X, PLATFORM2_Y, PLATFORM2_WIDTH, PLATFORM_HEIGHT};
	platforms[platform++] = {PLATFORM3_X, PLATFORM3_Y, PLATFORM3_WIDTH, PLATFORM_HEIGHT};
	platforms[platform++] = {PLATFORM4_X, PLATFORM4_Y, PLATFORM4_WIDTH, PLATFORM_HEIGHT};
	platforms[platform++] = {PLATFORM5_X, PLATFORM5_Y, PLATFORM5_WIDTH, PLATFORM_HEIGHT};
	platforms[platform] = {PLATFORM6_X, PLATFORM6_Y, PLATFORM6_WIDTH, PLATFORM_HEIGHT};
}

void Ladder_Set_Up(SDL_Rect *ladders) {
	int ladder = 0;
	ladders[ladder++] = {295, PLATFORM2_Y, LADDERS_WIDTH, LADDERS_HEIGHT};
	ladders[ladder++] = {420, PLATFORM2_Y, LADDERS_WIDTH, LADDERS_HEIGHT};
	ladders[ladder++] = {73, PLATFORM3_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 2};
	ladders[ladder++] = {524, PLATFORM3_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 2};
	ladders[ladder++] = {271, PLATFORM4_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 2};
	ladders[ladder++] = {340, PLATFORM4_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 2};
	ladders[ladder++] = {134, PLATFORM5_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 3};
	ladders[ladder++] = {482, PLATFORM5_Y, LADDERS_WIDTH, LADDERS_HEIGHT - 3};
	ladders[ladder] = {391, PLATFORM6_Y, LADDERS_WIDTH, LADDERS_HEIGHT + 1};

}

void BasicSetUp(SDL_Rect *platforms, SDL_Rect *ladders) {
	Platform_Set_Up(platforms);
	Ladder_Set_Up(ladders);
}

void
BasicRender(SDL_Texture *texture, SDL_Surface *screen, SDL_Renderer *renderer, GameEntity *player, GameEntity *enemy,
            GameEntity *barrels, GameEntity *portal) {
	SDL_UpdateTexture(texture, nullptr, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	RenderPlayer(renderer, player);
	RenderEnemy(renderer, enemy);
	RenderEnemy(renderer, portal);
	for (int i = 0; i < BARRELS_AMOUNT; ++i) {
		if (barrels[i].position.x != BARRELS_X) {
			RenderBarrel(renderer, &barrels[i]);
		}
	}
	SDL_RenderPresent(renderer);

}

// checking if Marek is touching the floor

void
LevelView(Sdl &sdl, char *text, Data &data, Colors colors, GameEntity player, GameObjects &objects, GameEntity Enemy,
          GameEntity *barrels, GameEntity Portal) {
	SDL_FillRect(sdl.screen, nullptr, colors.black);
	DrawSurface(sdl.screen, sdl.Level, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	DrawRectangle(sdl.screen, 4, 4, SCREEN_WIDTH - 8, 36, colors.cyan, colors.black);
	snprintf(text, 128, "Get the artefact, time that has passed = %.1lf s  %.0lf frames / s", data.worldTime, data.fps);
	DrawString(sdl.screen, sdl.screen->w / 2 - strlen(text) * 8 / 2, 10, text, sdl.charset);
	snprintf(text, 128, "Esc - quit, n - refresh game, all basic requirements met: 1-4 basic + A + C");
	DrawString(sdl.screen, sdl.screen->w / 2 - strlen(text) * 8 / 2, 26, text, sdl.charset);
	//DrawPlatforms(*&sdl, *&objects, *&colors); // drawing platform and ladder structs
	BasicRender(sdl.texture, sdl.screen, sdl.renderer, &player, &Enemy, barrels, &Portal);
}

bool CheckLibrary(Sdl &sdl) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return false;
	}
	int initError = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &sdl.window, &sdl.renderer);
	if (initError != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void TimeUpdate(Data &data, double &delta) {
	data.endTick = SDL_GetTicks();
	delta = (data.endTick - data.startTick) * 0.001;
	data.startTick = data.endTick;
	data.worldTime += delta;
	data.fpsTimer += delta;

	if (data.fpsTimer > FPS_REFRESH_TIME) {
		data.fps = data.frames * FPS_ADJUSTED_TIME;
		data.frames = 0;
		data.fpsTimer -= FPS_REFRESH_TIME;
	}
}
