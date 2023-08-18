#ifndef RAY_H
#define RAY_H
#include "defs.h"
#include "player.h"
#include "map.h"
#include "graphics.h"
#include <limits>


struct ray_t
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	bool wasHitVertical;
	bool firstwall;
	int texture;

};

class Rays
{
public:
	Rays() = default;
	void castRay(float rayAngle, int stripId, Player& player, Map& map);
	void castAllRays(Player& player, Map& map);
	void renderMapRays(graphics& gfx, Player& player);
	void normalizeAngle(float* angle);
	float distanceBetweenPoints(float x1, float y1, float x2, float y2);

public:
	ray_t rays[NUM_RAYS];
};

#endif // !



