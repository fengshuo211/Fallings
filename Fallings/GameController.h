#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameTexture.h"

class GameController {
public:
	GameController();
	void initGame();
	void startGame();
	void closeGame();
	void renderGame();

	~GameController();
private:
	// Functions 
	void checkNotNull(void * inputVariable, char *name);

	void renderBackground();
	void renderGameEnd();
	// Variables
	SDL_Window *mainGameWindow;
	SDL_Renderer *mainGameWindowRenderer;

	imageTexture *gameBackgroundTexture = NULL;
	imageTexture *gameFloorTexture = NULL;
	// Game Window 
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	// The current score
	int points = 0;

	SDL_Rect floorRect { 0, 380, SCREEN_WIDTH, SCREEN_HEIGHT - 380 };
};