#ifndef PLAYER_H
#define PLAYER_H
#include "graphics.h"
#include "map.h"
#include "defs.h"

class Player
{
public:
	Player() = default;
	void initplayer();
	void movePlayer(float deltatime);
	void renderMapPlayer(graphics& gfx);
	void normalizeAngle(float* angle);

public:
	float x;
	float y;
	float width;
	float height;
	int   turnDirection; // -1 for left, +1 for right
	int   walkDirection; // -1 for back, +1 for front
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
	int   islookingupdown;
	float lookUpDown;
	float playerLookAngle;

	Map map;

};

#endif // !PLAYER_H



