#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "Character.h"
#include "GameTexture.h"

Character::Character(int inputX, int inputY, SDL_Renderer * inputRenderer, int screen_w, int screen_h)
{
	if (inputRenderer == NULL) {
		std::cout << "input renderer can't be NULL";
	}

	x = inputX;
	y = inputY;
	renderer = inputRenderer;
	mainCharacter = new SDL_Rect();

	mainCharacter->x = x;
	mainCharacter->y = y;
	mainCharacter->h = h;
	mainCharacter->w = w;
	SCREEN_WIDTH = screen_w;
	SCREEN_HEIGHT = screen_h;

	mainCharacterTexture = new CharacterTexture(renderer);
}

Character::~Character()
{
	delete mainCharacter;
	mainCharacter = NULL;

	delete mainCharacterTexture;
	mainCharacterTexture = NULL;
}

void Character::move(float currentTimeTicks)
{
	int newX = static_cast<int> (mainCharacter->x + xVal * (currentTimeTicks - previousTimeTicks) / 5);
	if (newX >= -25 && newX + mainCharacter->w <= SCREEN_WIDTH)
		mainCharacter->x += static_cast<int> (xVal * (currentTimeTicks - previousTimeTicks) / 5);
	previousTimeTicks = currentTimeTicks;
}

void Character::handleEvent(float currentTimeTicks)
{
	keystates = SDL_GetKeyboardState(NULL);
	if (keystates[SDL_SCANCODE_LEFT])
		setMoveLeft();
	else if (keystates[SDL_SCANCODE_RIGHT])
		setMoveRight();
	else
		stop();

	move(currentTimeTicks);
	if (xVal == 0) {
		renderStop();
	}
	else if (xVal > 0){
		renderRight();
	}
	else {
		renderLeft();
	}
}

SDL_Rect* Character::getCurrentPosition()
{
	return mainCharacter;
}

void Character::renderPosition()
{
	SDL_SetRenderDrawColor(renderer, 51, 204, 51, 0);
	SDL_RenderFillRect(renderer, mainCharacter);
}

void Character::renderRight() 
{
	mainCharacterTexture->renderMoveRight(mainCharacter);
}

void Character::renderStop()
{
	mainCharacterTexture->renderStop(mainCharacter);
}
void Character::renderLeft()
{
	mainCharacterTexture->renderMoveLeft(mainCharacter);
}
void Character::setMoveLeft()
{
	xVal = -moveRate;
}

void Character::setMoveRight()
{
	xVal = moveRate;
}

void Character::stop()
{
	xVal = 0;
}

