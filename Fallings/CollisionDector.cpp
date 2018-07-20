#include <iostream>

#include "CollisionDector.h"

CollisonDector::CollisonDector(){}

CollisonDector::~CollisonDector(){}

/*
	Took from Lazy Fool's toturial 
	http://lazyfoo.net/SDL_tutorials/lesson17/index.php
*/
bool CollisonDector::check(SDL_Rect *rect1, SDL_Rect *rect2)
{
	if (rect1 == NULL || rect2 == NULL) {
		std::cout << "Failed to check the collision because input rectangle is NULL";
	}

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = rect1->x;
	rightA = rect1->x + rect1->w;
	topA = rect1->y;
	bottomA = rect1->y + rect1->h;

	//Calculate the sides of rect B
	leftB = rect2->x;
	rightB = rect2->x + rect2->w;
	topB = rect2->y;
	bottomB = rect2->y + rect2->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}
