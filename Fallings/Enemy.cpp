#include <algorithm>
#include <random>

#include "Enemy.h"
#include "GameTexture.h"
#include "CollisionDector.h"

Enemy::Enemy(int pos, SDL_Renderer *renderer):enemyTexture(renderer)
{
	position = pos;
	mainRenderer = renderer;
	enemyRect.x = position;
	enemyRect.y = currentY;
	enemyRect.w = 25;
	enemyRect.h = 25;
}

Enemy::~Enemy(){}

bool Enemy::render(int addPixel, SDL_Rect *characterPosition, int *points)
{
	currentY += addPixel;

	enemyRect.x = position;
	enemyRect.y = currentY;
	enemyRect.w = 25;
	enemyRect.h = 25;

	bool hitWithCharacter = checkCollection(characterPosition);
	
	if (hitWithCharacter) {
		*points = *points + 1;
	}
	
	if (currentY <= 360 && !hitWithCharacter) {
		enemyTexture.renderEnemy(&enemyRect);
		return true;
	}

	return false;
}

bool Enemy::checkCollection(SDL_Rect *characterPosition)
{
	return collisionDector.check(&enemyRect, characterPosition);
}

int const Enemy::getPosition()
{
	return position;
}

void Enemy::isHit()
{
}

EneryController::EneryController(int width, int height, SDL_Renderer *renderer, int *currentPoints)
{
	screenHeight = height;
	screenWidth = width;
	mainRenderer = renderer;
	points = currentPoints;
}

EneryController::~EneryController(){}

/**
	Generate a new enemy, just need to calculate the correct x position
*/
void EneryController::addEnemy()
{
	std::vector<int> availablePositions = getValidPositions();
	int vectorSize = availablePositions.size();

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, vectorSize); // define the range

	int newEnemyPosition = distr(eng);

	Enemy newEnemy(newEnemyPosition, mainRenderer);
	enemyCollection.push_back(newEnemy);
}

void EneryController::update(float currentTimeTicks, SDL_Rect *characterPosition)
{
	int addPixel = static_cast<int> (VAL * (currentTimeTicks - previousTimeTicks) / 10);
	std::vector <Enemy >::iterator iter;

	// Move each enemy accordingly
	for (iter = enemyCollection.begin(); iter != enemyCollection.end(); ) {
		bool success = (*iter).render(addPixel, characterPosition, points);
		if (!success) {
			iter = enemyCollection.erase(iter);
		}
		else
			++iter;
	}

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 100); // define the range

	int newEnemyPosition = distr(eng);
	// Check to see if we need add more enemy
	if (newEnemyPosition < 5) {
		addEnemy();
	}
	previousTimeTicks = currentTimeTicks;
}

std::vector<int> EneryController::getValidPositions()
{
	std::vector<int> positions;

	for (int i = 1; i < screenWidth - 1; i++) {
		positions.push_back(i);
	}

	for (auto enemy : enemyCollection)
	{
		int inValidPosition = enemy.getPosition();
		positions.erase(std::remove(positions.begin(), positions.end(), inValidPosition), positions.end());
	}
	return positions;
}
