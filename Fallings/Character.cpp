#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "Character.h"
#include "GameTexture.h"
#include "Vector.h"

Character::Character(int inputX, int inputY, SDL_Renderer * inputRenderer, int screen_w, int screen_h): playerPosition(inputX, inputY)
{
	if (inputRenderer == NULL) {
		std::cout << "input renderer can't be NULL";
	}

	renderer = inputRenderer;

	SCREEN_WIDTH = screen_w;
	SCREEN_HEIGHT = screen_h;

	mainCharacterTexture = new CharacterTexture(renderer);
}

Character::~Character()
{
	delete mainCharacterTexture;
	mainCharacterTexture = NULL;
}

void Character::move(float currentTimeTicks)
{
	float timeDeltaInSeconds = (currentTimeTicks - previousTimeTicks) / 1000;

	Vector nextPosition(playerPosition.x, playerPosition.y);
	
	// Move the player Vector to the currect place based on the speed and direction
	// Calculate currenct Velocity
	Vector playerVelocity = VectorMath::multiplyScalar(playerDirection, playerSpeed);
	// Create a vector which respects the time delta
	Vector velocityRespectTimeDelta(static_cast<int> (playerVelocity.x * timeDeltaInSeconds), playerVelocity.y);
	
	nextPosition.add(velocityRespectTimeDelta);

	// Update the playerPosition if the nextPosition is within a valid range
	if (nextPosition.x >= -15 && nextPosition.x <= SCREEN_WIDTH - 50) {
		playerPosition.x = nextPosition.x;
	}
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

	if (playerDirection.x == 0) {
		renderStop();
	}
	else if (playerDirection.x > 0){
		renderRight();
	}
	else {
		renderLeft();
	}
}

Vector Character::getCurrentPosition(){ return playerPosition; }

int const Character::getPlayerWidth(){ return w; }

int const Character::getPlayerHeight(){ return h;}

void Character::renderRight() 
{
	mainCharacterTexture->renderMoveRight(playerPosition.x, playerPosition.y, w, h);
}

void Character::renderStop()
{
	mainCharacterTexture->renderStop(playerPosition.x, playerPosition.y, w, h);
}
void Character::renderLeft()
{
	mainCharacterTexture->renderMoveLeft(playerPosition.x, playerPosition.y, w, h);
}
void Character::setMoveLeft(){ playerDirection.setVector(-1, 0); }

void Character::setMoveRight(){ playerDirection.setVector(1, 0); }

void Character::stop(){ playerDirection.setVector(0, 0); }
