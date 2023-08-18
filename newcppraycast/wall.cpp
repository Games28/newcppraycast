#include "wall.h"

void Wall::changeColorIntensity(color_t* color, float factor)
{
	color_t a = (*color & 0xFF000000);
	color_t r = (*color & 0x00FF0000) * factor;
	color_t g = (*color & 0x0000FF00) * factor;
	color_t b = (*color & 0x000000FF) * factor;

	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

void Wall::renderWallProjection(graphics& gfx, Rays& ray, Player& player, Texture& texture)
{
	bool topwallhit = false;
	for (int x = 0; x < NUM_RAYS; x++) {
		float prepDistance = ray.rays[x].distance * cos(ray.rays[x].rayAngle - player.rotationAngle);

		float WallHeight = (TILE_SIZE / prepDistance * Dist_PROJ_PLANE);

		int wallStripHeight = (int)WallHeight;

		int wallTopY, wallBottomY;

		wallTopY = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);

		wallBottomY = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
		//multilevel attempt

		wallTopY = wallTopY < 0 ? 0 : wallTopY;
		wallBottomY = wallBottomY > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomY;
		int nHalfWindowHeight = WINDOW_HEIGHT / 2;
		float fPlayerH = TILE_SIZE / 2.0f;
		float fFoV = 60.0f;
		float fAngleStep = fFoV / (float)NUM_RAYS;
		float fViewAngle = (float)(x - (NUM_RAYS / 2)) * fAngleStep;
		float fCurAngle = (player.rotationAngle * 180.0f / PI) + fViewAngle;
		float fPlayerX = player.x;
		float fPlayerY = player.y;
		float fCosCurAngle = cos(fCurAngle * PI / 180.0f);
		float fSinCurAngle = sin(fCurAngle * PI / 180.0f);
		float fCosViewAngle = cos(fViewAngle * PI / 180.0f);

		int textureOffSetX;
		if (ray.rays[x].wasHitVertical) {
			textureOffSetX = (int)ray.rays[x].wallHitY % TILE_SIZE;

		}
		else {

			textureOffSetX = (int)ray.rays[x].wallHitX % TILE_SIZE;
		}

		//get correct texture id for map content
		int texNum = ray.rays[x].texture - 1;

		int texture_width = upng_get_width(texture.textures[texNum]);
		int texture_height = upng_get_height(texture.textures[texNum]);

		int hitindex = 0;
		float rawdistance;
		float correctdistance;
		int colheight;

		for (int y = 0; y < WINDOW_HEIGHT; y++)
		{
			if (y < wallTopY)
			{
				float fFloorProjDistance = ((fPlayerH / (float)(nHalfWindowHeight - y)) * Dist_PROJ_PLANE) / fCosViewAngle;
				float fFloorProjX = fPlayerX + fFloorProjDistance * fCosCurAngle;
				float fFloorProjY = fPlayerY + fFloorProjDistance * fSinCurAngle;
				int nSampleX = (int)(fFloorProjX) % TILE_SIZE;
				int nSampleY = (int)(fFloorProjY) % TILE_SIZE;
				color_t* wallTextureBuffer = (color_t*)upng_get_buffer(texture.textures[4]);
				color_t texelColor = wallTextureBuffer[(texture_width * nSampleY) + nSampleX];

				//drawPixel(x, y, texelColor);
				gfx.drawPixel(x, y, 0xff444444);


			}
			else if (y > wallBottomY)
			{

				float fFloorProjDistance = ((fPlayerH / (float)(y - nHalfWindowHeight)) * Dist_PROJ_PLANE) / fCosViewAngle;
				float fFloorProjX = fPlayerX + fFloorProjDistance * fCosCurAngle;
				float fFloorProjY = fPlayerY + fFloorProjDistance * fSinCurAngle;
				int nSampleX = (int)(fFloorProjX) % TILE_SIZE;
				int nSampleY = (int)(fFloorProjY) % TILE_SIZE;
				color_t* wallTextureBuffer = (color_t*)upng_get_buffer(texture.textures[5]);
				color_t texelColor = wallTextureBuffer[(nSampleY * texture_width) + nSampleX];

				gfx.drawPixel(x, y, texelColor);
				//drawPixel(x, y, 0xff777777);
			}
			else
			{
				int distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
				int textureOffSetY = distanceFromTop * ((float)texture_height / wallStripHeight);

				color_t* wallTextureBuffer = (color_t*)upng_get_buffer(texture.textures[texNum]);
				color_t texelColor = wallTextureBuffer[(texture_width * textureOffSetY) + textureOffSetX];
				gfx.drawPixel(x, y, texelColor);

				if (ray.rays[x].wasHitVertical)
				{
					changeColorIntensity(&texelColor, 0.7);
				}

				gfx.drawPixel(x, y, texelColor);
			}
		}
	}
}


