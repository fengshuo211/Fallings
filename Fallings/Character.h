#include <SDL.h>
#include "GameTexture.h"
#include "Vector.h"
#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
public:
	Character(int inputX, int inputY, SDL_Renderer *renderer, int screen_w, int screen_h);
	~Character();

	void move(float currentTimeTicks);
	void handleEvent(float currentTimeTicks);
	Vector getCurrentPosition();
	int const getPlayerWidth();
	int const getPlayerHeight();

private:

	void renderRight();
	void renderStop();
	void renderLeft();

	void setMoveLeft();
	void setMoveRight();
	void stop();

	CharacterTexture *mainCharacterTexture = NULL;
	SDL_Renderer *renderer = NULL;
	const Uint8* keystates = NULL;

	float previousTimeTicks = 0.0;
	const int h = 60;
	const int w = 60;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	// Vector Math Improvements
	Vector playerPosition; // 2D vector to indicate the position of the player
	Vector playerDirection;
	int playerSpeed = 200; // 200 pixels per second
};
#endif 
