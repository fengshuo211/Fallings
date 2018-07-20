#pragma once
#include <SDL.h>
#include <vector>
#include "GameTexture.h"
#include "Character.h"
#include "CollisionDector.h"

class Enermy
{
public:
	Enermy(int pos, SDL_Renderer *renderer);
	~Enermy();
	bool render(int addPixel, SDL_Rect *characterPosition, int *points);
	bool checkCollection(SDL_Rect *characterPosition);
	int const getPosition();
	void isHit();
private:
	SDL_Renderer *mainRenderer;
	EnermyTexture enermyTexture;
	CollisonDector collisionDector;
	SDL_Rect enermyRect;

	int position;
	int currentY = 0;
};

class EneryController
{
public:
	EneryController(int width, int height, SDL_Renderer *mainRenderer, int *currentPoints);
	~EneryController();
	void addEnermy();
	void update(float currentTimeTick, SDL_Rect *characterPosition);
	std::vector <Enermy > enermyCollection;

private:
	// void addEnermy();
	std::vector<int> getValidPositions();
	int screenWidth;
	int screenHeight;

	int *points;
	SDL_Renderer *mainRenderer;
	float previousTimeTicks = 0.0;

	int VAL = 1;
};