#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "GameTexture.h"

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
class GameController {
public:
	GameController();
	void initGame();
	void startGame();
	void closeGame();
	void renderGame();

	~GameController();
private:
	void checkNotNull(void * inputVariable, char *name);

	void renderBackground();
	void renderGameEnd();

	SDL_Window *mainGameWindow = NULL;
	SDL_Renderer *mainGameWindowRenderer = NULL;
	Mix_Music *music = NULL;
	imageTexture *gameBackgroundTexture = NULL;
	imageTexture *gameFloorTexture = NULL;
	// Game Window 
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	// The current score
	int points = 0;

	SDL_Rect floorRect { 0, 380, SCREEN_WIDTH, SCREEN_HEIGHT - 380 };
};
#endif
