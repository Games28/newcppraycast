#ifndef SPRITE_H
#define SPRITE_H
#include "defs.h"
#include "graphics.h"
#include "textures.h"
#include "player.h"
#include "ray.h"
#include "physics.h"

struct Sprite
{
	float x;
	float y;
	int texture;
	int lift;
	float scale;
	float movement;
	float spritescale;
	float distance;
	float angle;
	bool visible;
};

class Sprites
{
public:
	Sprites() = default;
	void init();
	void update(float deltatime,thePhysics& phs);
	void renderSpriteProjection(graphics& gfx, Player& player,Rays& ray, Texture& texture);
	void renderMapSprites(graphics& gfx);
	float distanceBetweenPoints(float x1, float y1, float x2, float y2);

public:
	Sprite sprites[NUM_SPRITES];
	float fSpriteUplift = 0.0f;
};
#endif // !SPRITE_H


