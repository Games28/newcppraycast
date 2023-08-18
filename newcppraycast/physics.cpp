#include "physics.h"

void thePhysics::integrate(float& deltatime)
{
	vel += accelerate * deltatime;
	pos += vel * deltatime;
}

void thePhysics::constants()
{
	gravity = 9.8f;
	pixels_per_meter = 50;
	accelerate = gravity * pixels_per_meter;
}

void thePhysics::objectleft(float& deltatime)
{
	if (isfalling)
	{
		integrate(deltatime);
	}

	if (iscaught)
	{
		isfalling = false;
	}

	if (pos >= 1)
	{
		pos = 0;
		isfalling = false;
	}

}

void thePhysics::setup(float& lift)
{
	pos = lift;
}
