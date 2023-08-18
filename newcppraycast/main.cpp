#include <SDL.h>
#include "graphics.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "textures.h"
#include "wall.h"
#include "sprite.h"
#include "physics.h"


class Application
{
public:
	bool isGameRunning = false;
	int ticksLastFrame = 0;

	//objects
	graphics graphic;
	Map map;
	Player player;
	Rays ray;
	Texture texture;
	Wall wall;
	Sprites sprite;
	thePhysics phs;

public:
	Application() = default;

	void setup()
	{
		player.initplayer();
		texture.loadTextures();
		sprite.init();
		//phs.constants();

	}

	void processInput()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT: {
			isGameRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				isGameRunning = false;
			if (event.key.keysym.sym == SDLK_w)
				player.walkDirection = +1;
			if (event.key.keysym.sym == SDLK_s)
				player.walkDirection = -1;
			if (event.key.keysym.sym == SDLK_d)
				player.turnDirection = +1;
			if (event.key.keysym.sym == SDLK_a)
				player.turnDirection = -1;
			if (event.key.keysym.sym == SDLK_PAGEUP)
		 		sprite.fSpriteUplift -= 2.0f; 
		 	if (event.key.keysym.sym == SDLK_PAGEDOWN)
		 		sprite.fSpriteUplift += 2.0f;
		 
		 	
		 }break;

		 case SDL_KEYUP: {
		 	if (event.key.keysym.sym == SDLK_w)
		 		player.walkDirection = 0;
		 	if (event.key.keysym.sym == SDLK_s)
		 		player.walkDirection = 0;
		 	if (event.key.keysym.sym == SDLK_d)
		 		player.turnDirection = 0;
		 	if (event.key.keysym.sym == SDLK_a)
		 		player.turnDirection = 0;
		 	//if (event.key.keysym.sym == SDLK_PAGEUP)
		 		//isfalling = true; iscaught = false;
		 
		 	
		 }break;


		}
	}

	void update()
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TIME_LENGTH));


		float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

		ticksLastFrame = SDL_GetTicks();
		//sprite.update(deltaTime, phs);
		player.movePlayer(deltaTime);
		ray.castAllRays(player, map);

	}

	void render()
	{
		graphic.clearColorBuffer(0xff000000);
		wall.renderWallProjection(graphic, ray, player, texture);
		sprite.renderSpriteProjection(graphic, player, ray, texture);
		map.renderMapGrid(graphic);
		ray.renderMapRays(graphic,player);
		sprite.renderMapSprites(graphic);
		player.renderMapPlayer(graphic);

		graphic.renderColorBuffer();
	}

	void releaseResources()
	{
		graphic.destroyWindow();
		texture.freeTextures();
	}

};


int main(int argc, char* args[])
{
	Application app;
	
	app.isGameRunning = app.graphic.initializeWindow();

	app.setup();

	while (app.isGameRunning)
	{
		app.processInput();
		app.update();
		app.render();
	}

	app.releaseResources();

	return 0;
}