#ifndef WALL_H
#define WALL_H
#include "textures.h"
#include "defs.h"
#include "player.h"
#include "ray.h"
#include "graphics.h"

class Wall
{
public:
	void changeColorIntensity(color_t* color, float factor);
	void renderWallProjection(graphics& gfx, Rays& ray, Player& player, Texture& texture);
	void calculateBottomAndTop(float wallDistance, int wallHight, int& wallCeil, int& wallFloor);

};
#endif // !WALL_H


