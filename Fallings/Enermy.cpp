#include <algorithm>
#include <random>

#include "Enermy.h"
#include "GameTexture.h"
#include "CollisionDector.h"

Enermy::Enermy(int pos, SDL_Renderer *renderer):enermyTexture(renderer)
{
	position = pos;
	mainRenderer = renderer;
	enermyRect.x = position;
	enermyRect.y = currentY;
	enermyRect.w = 25;
	enermyRect.h = 25;
}

Enermy::~Enermy(){}

bool Enermy::render(int addPixel, SDL_Rect *characterPosition, int *points)
{
	currentY += addPixel;

	enermyRect.x = position;
	enermyRect.y = currentY;
	enermyRect.w = 25;
	enermyRect.h = 25;

	bool hitWithCharacter = checkCollection(characterPosition);
	
	if (hitWithCharacter) {
		*points = *points + 1;
	}
	
	if (currentY <= 360 && !hitWithCharacter) {
		enermyTexture.renderEnermy(&enermyRect);
		return true;
	}

	return false;
}

bool Enermy::checkCollection(SDL_Rect *characterPosition)
{
	return collisionDector.check(&enermyRect, characterPosition);
}

int const Enermy::getPosition()
{
	return position;
}

void Enermy::isHit()
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
	Generate a new enermy, just need to calculate the correct x position
*/
void EneryController::addEnermy()
{
	std::vector<int> availablePositions = getValidPositions();
	int vectorSize = availablePositions.size();

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, vectorSize); // define the range

	int newEnermyPosition = distr(eng);

	Enermy newEnermy(newEnermyPosition, mainRenderer);
	enermyCollection.push_back(newEnermy);
}

void EneryController::update(float currentTimeTicks, SDL_Rect *characterPosition)
{
	int addPixel = VAL * (currentTimeTicks - previousTimeTicks) / 10;
	std::vector <Enermy >::iterator iter;

	// Move each enermy accordingly
	for (iter = enermyCollection.begin(); iter != enermyCollection.end(); ) {
		bool success = (*iter).render(addPixel, characterPosition, points);
		if (!success) {
			iter = enermyCollection.erase(iter);
		}
		else
			++iter;
	}

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 100); // define the range

	int newEnermyPosition = distr(eng);
	// Check to see if we need add more enermy
	if (newEnermyPosition < 5) {
		addEnermy();
	}
	previousTimeTicks = currentTimeTicks;
}

std::vector<int> EneryController::getValidPositions()
{
	std::vector<int> positions;

	for (int i = 1; i < screenWidth - 1; i++) {
		positions.push_back(i);
	}

	for (auto enermy : enermyCollection)
	{
		int inValidPosition = enermy.getPosition();
		positions.erase(std::remove(positions.begin(), positions.end(), inValidPosition), positions.end());
	}
	return positions;
}
