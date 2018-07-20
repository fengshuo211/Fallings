#include <SDL.h>
#include "GameTexture.h"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
public:
	Character(int inputX, int inputY, SDL_Renderer *renderer, int screen_w, int screen_h);
	~Character();

	void move(float currentTimeTicks);
	void handleEvent(float currentTimeTicks);
	SDL_Rect* getCurrentPosition();
private:
	void renderPosition();

	void renderRight();
	void renderStop();
	void renderLeft();

	void setMoveLeft();
	void setMoveRight();
	void stop();

	SDL_Rect *mainCharacter = NULL;

	CharacterTexture *mainCharacterTexture = NULL;
	SDL_Renderer *renderer = NULL;
	const Uint8* keystates = NULL;

	int x;
	int y;

	int xVal = 0;

	int moveRate = 1;
	int h = 60;
	int w = 60;

	float previousTimeTicks = 0.0;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
};
#endif 
