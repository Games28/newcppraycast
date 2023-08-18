#include "sprite.h"

void Sprites::init()
{
	sprites[0] = { 300, 400, 9, 0, 1.0f, 1.0f, 1.0f };
}

void Sprites::update(float deltatime, thePhysics& phs)
{
	phs.setup(fSpriteUplift);
	phs.integrate(deltatime);
	phs.objectleft(deltatime);

}

void Sprites::renderSpriteProjection(graphics& gfx, Player & player, Rays& ray, Texture& texture)
{
	Sprite visibleSprites[NUM_SPRITES];
	int numVisibleSprites = 0;


	for (int i = 0; i < NUM_SPRITES; i++) {
		float angleSpritePlayer = player.rotationAngle - atan2(sprites[i].y - player.y, sprites[i].x - player.x);

		if (angleSpritePlayer > PI)
			angleSpritePlayer -= TWO_PI;
		if (angleSpritePlayer < -PI)
			angleSpritePlayer += TWO_PI;

		angleSpritePlayer = fabs(angleSpritePlayer);

		const float EPSILON = 0.2f;
		if (angleSpritePlayer < (FOV_ANGLE / 2) + EPSILON) {
			sprites[i].visible = true;
			sprites[i].angle = angleSpritePlayer;
			sprites[i].distance = distanceBetweenPoints(sprites[i].x, sprites[i].y, player.x, player.y);
			visibleSprites[numVisibleSprites] = sprites[i];
			numVisibleSprites++;
		}
		else {
			sprites[i].visible = false;
		}
	}

	for (int i = 0; i < numVisibleSprites - 1; i++)
	{
		for (int j = i + 1; j < numVisibleSprites; j++)
		{
			if (visibleSprites[i].distance < visibleSprites[j].distance)
			{
				Sprite temp = visibleSprites[i];
				visibleSprites[i] = visibleSprites[j];
				visibleSprites[j] = temp;
			}
		}
	}

	for (int i = 0; i < numVisibleSprites; i++)
	{
		Sprite sprite = visibleSprites[i];
		//sprite.movement;

		float prepDistance = sprite.distance * cos(sprite.angle);

		float spriteHeight = ((TILE_SIZE) / prepDistance) * Dist_PROJ_PLANE;

		float spriteWidth = spriteHeight;

		//this is will the bottom to bounce from
		float floor = (WINDOW_HEIGHT / 2) + (spriteHeight / 2);




		//this is will the determine the height to drop from 
		float spriteTopY = (WINDOW_HEIGHT / 2) - (spriteHeight / 2) + fSpriteUplift;
		float spriteBottomY = (WINDOW_HEIGHT / 2) + (spriteHeight / 2) + fSpriteUplift;



		spriteTopY = (spriteTopY < 0) ? 0 : spriteTopY;
		spriteBottomY = (spriteBottomY > WINDOW_HEIGHT) ? WINDOW_HEIGHT : spriteBottomY;




		float spriteAngle = atan2(sprite.y - player.y, sprite.x - player.x) - player.rotationAngle;
		float spriteScreenPosX = tan(spriteAngle) * Dist_PROJ_PLANE;

		float spriteLeftX = (WINDOW_WIDTH / 2) + spriteScreenPosX - spriteWidth / 2;
		float spriteRightX = spriteLeftX + spriteWidth;



		int textureWidth = upng_get_width(texture.textures[sprite.texture]);
		int textureHeight = upng_get_height(texture.textures[sprite.texture]);




		for (int x = spriteLeftX; x < spriteRightX; x++)
		{

			float texelWidth = (textureWidth / spriteWidth);
			int textureOffSetX = ((x - spriteLeftX) * texelWidth);
			for (int y = spriteTopY; y < spriteBottomY; y++)
			{
				int distanceFromTop = y - fSpriteUplift + (spriteHeight / 2) - (WINDOW_HEIGHT / 2);
				int textureOffSetY = distanceFromTop * (textureHeight / spriteHeight);

				if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
				{

					color_t* spriteTextureBuffer = (color_t*)upng_get_buffer(texture.textures[sprite.texture]);
					color_t texelColor = spriteTextureBuffer[(textureWidth * textureOffSetY) + textureOffSetX];

					if (sprite.distance < ray.rays[x].distance && texelColor != 0xffff00ff)
						gfx.drawPixel(x, y, texelColor);
				}

			}
		}

	}
}

void Sprites::renderMapSprites(graphics& gfx)
{
	for (int i = 0; i < NUM_SPRITES; i++)
	{
		for (int i = 0; i < NUM_SPRITES; i++) {
			gfx.drawRect(
				sprites[i].x * MINIMAP_SCALE_FACTOR,
				sprites[i].y * MINIMAP_SCALE_FACTOR,
				2,
				2,
				(sprites[i].visible) ? 0xFF00FFFF : 0xFF444444
			);
		}
	}
}

float Sprites::distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
