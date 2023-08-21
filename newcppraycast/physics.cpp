#include "physics.h"

void thePhysics::integrate(float& deltatime)
{
	vel += accelerate * deltatime;
	*pos += vel * deltatime;
}

void thePhysics::physicsconstants()
{
	gravity = 9.8f;
	pixels_per_meter = 50;
	accelerate = gravity * pixels_per_meter;
}

void thePhysics::physicsobjectlift(float& deltatime, bool& isfalling)
{
	if (isfalling)
	{
		integrate(deltatime);
		
	}
	
	if (*pos >= 0)
	{
		*pos = 0;

		vel *= -0.9f;
	}
}

void thePhysics::physicssetup(float& lift)
{
	pos = &lift;
}
