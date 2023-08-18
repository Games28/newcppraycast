#ifndef TEXTURES_H
#define TEXTURES_H
#include <stdint.h>
#include "defs.h"
#include "upng.h"

class Texture
{
public:
	Texture() = default;

	upng_t* textures[NUM_TEXTURES];

	void loadTextures();
	void freeTextures();

public:
	const char* textureFileNames[NUM_TEXTURES] = {
	"./images/redbrick.png",
	"./images/purplestone.png",
	"./images/mossystone.png",
	"./images/graystone.png",
	"./images/bluestone.png",
	"./images/colorstone.png",
	"./images/wood.png",
	"./images/eagle.png",
	"./images/pikuma.png",
	"./images/barrel_big.png",
	"./images/light.png",  //10
	"./images/table.png",  //11
	"./images/guard.png", //12
	"./images/armor.png" //13


	};
};



#endif

