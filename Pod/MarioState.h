#pragma once

enum MarioState {
	DROPPING, JUMPING, STANDING, WALKING, DIE, DIE_JUMPING, DIE_DROPPING,
};

enum MarioSubState {
	NONE, PUSHING,
};