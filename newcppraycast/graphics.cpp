#include "graphics.h"

bool graphics::initializeWindow(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {         //error checking
		fprintf(stderr, "error initializing sdl.\n");
		return false;
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	int fullScreenWidth = 1200;
	int fullScreenHeight = 800;
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		fullScreenWidth,
		fullScreenHeight,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {                                       //error checking
		fprintf(stderr, "error creating sdl window. \n");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {                                    //error checking
		fprintf(stderr, "error creating renderer. \n");
		return false;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	//allocate the total amount of bytes in memory to hold colorbuffer
	colorBuffer = (color_t*)malloc(sizeof(color_t) * (color_t)WINDOW_WIDTH * (color_t)WINDOW_HEIGHT);

	//create a sdl texture to display the color buffer
	colorBufferTexture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING,
		WINDOW_WIDTH,
		WINDOW_HEIGHT
	);

	return true;
}

void graphics::destroyWindow(void)
{
	free(colorBuffer);
	SDL_DestroyTexture(colorBufferTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void graphics::clearColorBuffer(color_t color)
{
	for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {
		colorBuffer[i] = color;

	}
}

void graphics::renderColorBuffer(void)
{
	SDL_UpdateTexture(
		colorBufferTexture,
		NULL,
		colorBuffer,
		(int)((color_t)WINDOW_WIDTH * sizeof(color_t))
	);
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);

	SDL_RenderPresent(renderer);
}

void graphics::drawPixel(int x, int y, color_t color)
{
	colorBuffer[(WINDOW_WIDTH * y) + x] = color;
}

void graphics::drawRect(int x, int y, int width, int height, color_t color)
{
	for (int i = x; i <= (x + width); i++)
	{
		for (int j = y; j <= (y + height); j++)
		{
			drawPixel(i, j, color);
		}
	}
}

void graphics::drawLine(int x0, int y0, int x1, int y1, color_t color)
{
	int deltaX = (x1 - x0);
	int deltaY = (y1 - y0);

	int longestSideLength = (abs(deltaX) >= abs(deltaY) ? abs(deltaX) : abs(deltaY));

	float xIncrement = deltaX / (float)longestSideLength;
	float yIncrement = deltaY / (float)longestSideLength;

	float currentX = x0;
	float currentY = y0;

	for (int i = 0; i < longestSideLength; i++)
	{
		drawPixel(round(currentX), round(currentY), color);
		currentX += xIncrement;
		currentY += yIncrement;
	}
}
