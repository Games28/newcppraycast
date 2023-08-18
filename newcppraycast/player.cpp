#include "player.h"

void Player::initplayer()
{
	x = WINDOW_WIDTH / 2;
	y = WINDOW_HEIGHT / 2;
	width = 2;
	height = 2;
	turnDirection = 0;
    walkDirection = 0; 
	rotationAngle = PI / 2;
	walkSpeed = 100;
	turnSpeed = 45 * (PI / 180);
	islookingupdown = 0;
	lookUpDown = 45 * (PI / 180);
	playerLookAngle = 0;
}

void Player::movePlayer(float deltatime)
{
	rotationAngle += turnDirection * turnSpeed * deltatime;
	normalizeAngle(&rotationAngle);

	float moveStep = walkDirection * walkSpeed * deltatime;

	float newPlayerX = x + cos(rotationAngle) * moveStep;
	float newPlayerY = y + sin(rotationAngle) * moveStep;

	//wall collision
	if (!map.mapHasWallAt(newPlayerX, newPlayerY)) {
		x = newPlayerX;
		y = newPlayerY;
	}
}

void Player::renderMapPlayer(graphics& gfx)
{
	gfx.drawRect(
		x * MINIMAP_SCALE_FACTOR,
		y * MINIMAP_SCALE_FACTOR,
		width * MINIMAP_SCALE_FACTOR,
		height * MINIMAP_SCALE_FACTOR,
		0xffffffff
	);
}

void Player::normalizeAngle(float* angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0) {
		*angle = TWO_PI + *angle;
	}
}
