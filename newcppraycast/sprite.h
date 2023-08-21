#ifndef SPRITE_H
#define SPRITE_H
#include "defs.h"
#include "graphics.h"
#include "textures.h"
#include "player.h"
#include "ray.h"
#include "physics.h"
#include "map.h"

struct Sprite
{
	float x;
	float y;
	int texture;
	int lift;
	

	//sprite movement
	int   turnDirection; // -1 for left, +1 for right
	int   walkDirection; // -1 for back, +1 for front
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
	//float* spritelift = nullptr;
	float Slift;
	float scale;
	bool isfalling = false;
	float spritescale;
	float distance;
	float angle;
	bool visible;
	bool insight = false;
	bool islifting = false;
	
};

class Sprites
{
public:
	Sprites() = default;
	void init();
	void update(float deltatime,thePhysics& phs);
	void renderSpriteProjection(graphics& gfx, Player& player,Rays& ray, Texture& texture, thePhysics& phs);
	void renderMapSprites(graphics& gfx);
	float distanceBetweenPoints(float x1, float y1, float x2, float y2);

	void moveSprite(float deltatime);
	void normalizeAngle(float* angle);


public:
	Sprite sprites[NUM_SPRITES];
	float fSpriteUplift = 0.0f;
	Map map;
	bool islifting = false;
	bool istargeted = false;
	
};
#endif // !SPRITE_H


