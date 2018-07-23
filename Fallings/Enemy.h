#include <SDL.h>
#include <vector>
#include "GameTexture.h"
#include "Character.h"
#include "CollisionDector.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
public:
	Enemy(int pos, SDL_Renderer *renderer);
	~Enemy();
	bool render(int addPixel, SDL_Rect *characterPosition, int *points);
	bool checkCollection(SDL_Rect *characterPosition);
	int const getPosition();
	void isHit();
private:
	SDL_Renderer *mainRenderer = NULL;
	EnemyTexture enemyTexture;
	CollisonDector collisionDector;
	SDL_Rect enemyRect;

	int position;
	int currentY = 0;
};

class EneryController
{
public:
	EneryController(int width, int height, SDL_Renderer *mainRenderer, int *currentPoints);
	~EneryController();
	void addEnemy();
	void update(float currentTimeTick, SDL_Rect *characterPosition);
	std::vector <Enemy> enemyCollection;

private:
	std::vector<int> getValidPositions();
	int screenWidth;
	int screenHeight;

	int *points = NULL;
	SDL_Renderer *mainRenderer = NULL;
	float previousTimeTicks = 0.0;

	int VAL = 1;
};
#endif