//
// Created by admin on 20.12.2023.
//
#include "Magic.h"
#include "Animation.h"
#include "Defines.h"

//animating Marek
void MarekAnim(GameEntity &player, Data &data, Check &value){
	if (data.AnimFrames % data.frameChange == 0) {
		player.currentFrame += 1;
		player.size.x = player.size.w * player.currentFrame;
	}
	if (data.AnimFrames % (data.frameChange * (data.maxFrames - 1)) == 0 or player.currentFrame > 7) {
		player.currentFrame = 0;
	}
	data.AnimFrames++;
	if (value.falling) {
		player.currentFrame = 7;
	} else if (value.standing) player.currentFrame = 8;
}
