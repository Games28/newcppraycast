#ifndef  THEPHYSICS_H
#define THEPHYSICS_H

class thePhysics
{
public:
	thePhysics() = default;

	void integrate(float& deltatime);
	void constants();
	void objectleft(float& deltatime);
	void setup(float& lift);

public:
	bool isfalling;
	bool iscaught;
	float gravity;
	int pixels_per_meter;;
	float& pos;
	float vel;
	float accelerate;

};

#endif // ! PHYSICS_H


