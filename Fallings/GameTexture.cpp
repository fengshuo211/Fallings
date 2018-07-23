#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>

#include "GameTexture.h"

void TextTexture::renderText(const char * text, SDL_Renderer * renderer, int x, int y, int w, int h)
{
	if (font == NULL || text == NULL || renderer == NULL) {
		std::cout << "Can't render the text because some mandatory variables are NULL";
	}

	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;

	SDL_Surface * fontSurface = TTF_RenderText_Blended(font, text, myColor);
	generatedTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	
	SDL_FreeSurface(fontSurface);
	SDL_RenderCopy(renderer, generatedTexture, NULL, &position);
}

void TextTexture::setFont(char *fontPath, int fontSize)
{
	font = TTF_OpenFont(fontPath, fontSize);
}

void TextTexture::setColor(int r, int g, int b)
{
	myColor.r = r;
	myColor.g = g;
	myColor.b = b;
}

void TextTexture::close()
{
	SDL_DestroyTexture(generatedTexture);
}

imageTexture::imageTexture(SDL_Renderer * renderer, char * filePath)
{
	mainRenderer = renderer;
	SDL_Surface *backgroundSurface = IMG_Load(filePath);
	if (backgroundSurface == NULL) {
		std::cout << "Failed to load background surface";
	}
	
	myTexture = SDL_CreateTextureFromSurface(mainRenderer, backgroundSurface);
	if (myTexture == NULL) {
		std::cout << "Failed to convert background surface to texture";
	}
}

void imageTexture::render()
{
	SDL_RenderCopy(mainRenderer, myTexture, NULL, NULL);
}

void imageTexture::renderWithRect(SDL_Rect * rect)
{
	SDL_RenderCopy(mainRenderer, myTexture, NULL, rect);
}

imageTexture::~imageTexture()
{
	SDL_DestroyTexture(myTexture);
	myTexture = NULL;
}

CharacterTexture::CharacterTexture(SDL_Renderer *renderer)
{
	mainRenderer = renderer;
	std::vector<char *> runningTexturePath;
	std::vector<char *> stoppingTexturePath;

	runningTexturePath.push_back("assets/raccoon/run/run0001.png");
	runningTexturePath.push_back("assets/raccoon/run/run0003.png");
	runningTexturePath.push_back("assets/raccoon/run/run0005.png");
	runningTexturePath.push_back("assets/raccoon/run/run0007.png");
	runningTexturePath.push_back("assets/raccoon/run/run0011.png");
	runningTexturePath.push_back("assets/raccoon/run/run0013.png");
	runningTexturePath.push_back("assets/raccoon/run/run0015.png");
	runningTexturePath.push_back("assets/raccoon/run/run0017.png");
	runningTexturePath.push_back("assets/raccoon/run/run0019.png");
	runningTexturePath.push_back("assets/raccoon/run/run0021.png");
	runningTexturePath.push_back("assets/raccoon/run/run0023.png");

	stoppingTexturePath.push_back("assets/raccoon/idle/0001.png");
	stoppingTexturePath.push_back("assets/raccoon/idle/0003.png");
	stoppingTexturePath.push_back("assets/raccoon/idle/0005.png");
	stoppingTexturePath.push_back("assets/raccoon/idle/0007.png");
	stoppingTexturePath.push_back("assets/raccoon/idle/0009.png");
	stoppingTexturePath.push_back("assets/raccoon/idle/0011.png");
	stoppingTexturePath.push_back("assets/raccoon/idle/0013.png");
	stoppingTexturePath.push_back("assets/raccoon/idle/0015.png");
	stoppingTexturePath.push_back("assets/raccoon/idle/0017.png");
	stoppingTexturePath.push_back("assets/raccoon/idle/0019.png");
	stoppingTexturePath.push_back("assets/raccoon/idle/0021.png");

	for (auto path : runningTexturePath) {
		SDL_Texture *myTexture = convertImageToTexture(path);
		runningTextures.push_back(myTexture);
	}

	for (auto path : stoppingTexturePath) {
		SDL_Texture *myTexture = convertImageToTexture(path);
		stoppingTextures.push_back(myTexture);
	}
}

CharacterTexture::~CharacterTexture()
{
	for (auto texture : stoppingTextures) {
		SDL_DestroyTexture(texture);
	}
	for (auto texture : runningTextures) {
		SDL_DestroyTexture(texture);
	}
}

SDL_Texture * CharacterTexture::convertImageToTexture(char *filePath)
{
	SDL_Surface *tempImageSurface = IMG_Load(filePath);
	if (tempImageSurface == NULL) {
		std::cout << "Failed to load Image \n";
	}
	
	imageHeight = tempImageSurface->h;
	imageWidth = tempImageSurface->w;
	SDL_Texture *ret = NULL;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	ret = SDL_CreateTextureFromSurface(mainRenderer, tempImageSurface);
	if (ret == NULL) {
		std::cout << "Failed to convert background surface to texture";
	}
	SDL_FreeSurface(tempImageSurface);
	return ret;	
}

void CharacterTexture::renderMoveLeft(int positionX, int positionY, int positionW, int positionH)
{
	SDL_Rect position;
	position.x = positionX;
	position.y = positionY;
	position.w = positionW;
	position.h = positionH;

	SDL_Texture *nextTexture = runningTextures[nextLeftTextureIndex];

	previousCharacterDirection = 0;

	Uint32 currentTicks = SDL_GetTicks();
	if (currentTicks - lastLeftRunningSwitchTime > (600 / runningTextures.size())) {
		nextLeftTextureIndex++;
		lastLeftRunningSwitchTime = currentTicks;
	}
	if (nextLeftTextureIndex >= runningTextures.size()) {
		nextLeftTextureIndex = 0;
	}
	nextRightTextureIndex = 0;
	nextStopTextureIndex = 0;
	SDL_RenderCopyEx(mainRenderer, nextTexture, NULL, &position, NULL, NULL, flip);
}

void CharacterTexture::renderMoveRight(int positionX, int positionY, int positionW, int positionH)
{
	SDL_Rect position;
	position.x = positionX;
	position.y = positionY;
	position.w = positionW;
	position.h = positionH;

	SDL_Texture *nextTexture = runningTextures[nextRightTextureIndex];

	previousCharacterDirection = 1;

	Uint32 currentTicks = SDL_GetTicks();
	if (currentTicks - lastRunningSwitchTime > (600 / runningTextures.size())) {
		nextRightTextureIndex++;
		lastRunningSwitchTime = currentTicks;
	}
	if (nextRightTextureIndex >= runningTextures.size()) {
		nextRightTextureIndex = 0;
	}
	nextLeftTextureIndex = 0;
	nextStopTextureIndex = 0;

	SDL_RenderCopy(mainRenderer, nextTexture, NULL, &position);
}

void CharacterTexture::renderStop(int positionX, int positionY, int positionW, int positionH)
{
	SDL_Rect position;
	position.x = positionX;
	position.y = positionY;
	position.w = positionW;
	position.h = positionH;

	SDL_Texture *nextTexture = stoppingTextures[nextStopTextureIndex];
	Uint32 currentTicks = SDL_GetTicks();
	if (currentTicks - lastStopRunningTime > (600 / stoppingTextures.size())) {
		nextStopTextureIndex++;
		lastStopRunningTime = currentTicks;
	}

	if (nextStopTextureIndex >= stoppingTextures.size()) {
		nextStopTextureIndex = 0;
	}
	nextRightTextureIndex = 0;
	nextLeftTextureIndex = 0;

	// Need to flip if previous direction is left
	if (previousCharacterDirection == 0) {
		SDL_RenderCopyEx(mainRenderer, nextTexture, NULL, &position, NULL, NULL, flip);
	}
	else {
		SDL_RenderCopy(mainRenderer, nextTexture, NULL, &position);
	}
}

EnemyTexture::EnemyTexture(SDL_Renderer * renderer)
{
	mainRenderer = renderer;
	enemyTexture = convertImageToTexture("assets/items/apple_red.png");
	if (enemyTexture == NULL) {
		printf("Failed to load enemy Texture\n");
	}
}

EnemyTexture::~EnemyTexture()
{
	mainRenderer = NULL;
	enemyTexture = NULL;
}

void EnemyTexture::renderEnemy(SDL_Rect * renderRect)
{
	SDL_RenderCopy(mainRenderer, enemyTexture, NULL, renderRect);
}

SDL_Texture * EnemyTexture::convertImageToTexture(char * filePath)
{
	SDL_Surface *tempImageSurface = IMG_Load(filePath);
	if (tempImageSurface == NULL) {
		std::cout << "Failed to load Image \n";
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	SDL_Texture *ret = SDL_CreateTextureFromSurface(mainRenderer, tempImageSurface);
	if (ret == NULL) {
		std::cout << "Failed to convert background surface to texture";
	}
	SDL_FreeSurface(tempImageSurface);
	return ret;
}