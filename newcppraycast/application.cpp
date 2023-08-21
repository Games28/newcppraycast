#include "application.h"




	void Application::setup()
	{
		player.initplayer();
		texture.loadTextures();
		sprite.init();
		phs.physicsconstants();

	}

	void Application::processInput()
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
			if (event.key.keysym.sym == SDLK_q)
				player.strafeDirection = +1; player.isstrafingleft = true;
			if (event.key.keysym.sym == SDLK_e)
				player.strafeDirection = -1; player.isstrafingright = true;
			if (event.key.keysym.sym == SDLK_PAGEUP)
				sprite.islifting = true;//sprite.fSpriteUplift -= 5.0f; 
			if (event.key.keysym.sym == SDLK_PAGEDOWN)
				sprite.fSpriteUplift += 5.0f;

			//sprite movment
			for (int i = 0; i < NUM_SPRITES; i++)
			{
				if (event.key.keysym.sym == SDLK_UP)
					sprite.sprites[i].walkDirection = +1;
				if (event.key.keysym.sym == SDLK_DOWN)
					sprite.sprites[i].walkDirection = -1;
				if (event.key.keysym.sym == SDLK_RIGHT)
					sprite.sprites[i].turnDirection = +1;
				if (event.key.keysym.sym == SDLK_LEFT)
					sprite.sprites[i].turnDirection = -1;
			}
			
			if (event.key.keysym.sym == SDLK_SPACE)
				sprite.istargeted = true;

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
			if (event.key.keysym.sym == SDLK_q)
				player.strafeDirection = 0; 
			if (event.key.keysym.sym == SDLK_e)
				player.strafeDirection = 0; 
			if (event.key.keysym.sym == SDLK_PAGEUP)
			{
				sprite.islifting = false;
				for (int i = 0; i < NUM_SPRITES; i++)
				{
					Sprite* s = &sprite.sprites[i];
					s->isfalling = true;
				}
			}

			//spritemovement
			for (int i = 0; i < NUM_SPRITES; i++)
			{
				if (event.key.keysym.sym == SDLK_UP)
					sprite.sprites[i].walkDirection = 0;
				if (event.key.keysym.sym == SDLK_DOWN)
					sprite.sprites[i].walkDirection = 0;
				if (event.key.keysym.sym == SDLK_RIGHT)
					sprite.sprites[i].turnDirection = 0;
				if (event.key.keysym.sym == SDLK_LEFT)
					sprite.sprites[i].turnDirection = 0;
			}

			if (event.key.keysym.sym == SDLK_SPACE)
				sprite.istargeted = false;
		}break;


		}
	}

	void Application::update()
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TIME_LENGTH));


		float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

		ticksLastFrame = SDL_GetTicks();

		sprite.moveSprite(deltaTime);
		sprite.update(deltaTime, phs);
		
		player.movePlayer(deltaTime);
		player.strafePlayer(deltaTime);
		ray.castAllRays(player, map);

	}

	void Application::render()
	{
		graphic.clearColorBuffer(0xff000000);
		wall.renderWallProjection(graphic, ray, player, texture);
		sprite.renderSpriteProjection(graphic, player, ray, texture,phs);
		map.renderMapGrid(graphic);
		ray.renderMapRays(graphic, player);
		sprite.renderMapSprites(graphic);
		player.renderMapPlayer(graphic);
		//fp.Draw(graphic, texture, 0);
		fp.update(graphic, player, sprite, texture);
		graphic.renderColorBuffer();
	}

	void Application::releaseResources()
	{
		graphic.destroyWindow();
		texture.freeTextures();
	}


