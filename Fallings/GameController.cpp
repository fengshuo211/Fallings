#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vld.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

#include "GameController.h"
#include "GameTexture.h"
#include "Character.h"
#include "Enermy.h"

GameController::GameController()
{
}

void GameController::initGame()
{
	// Init SDL Video
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "Failed to init SDL_INIT_VIDEO OR SDL_INIT_AUDIO";
	}
	
	if (TTF_Init() == -1) {
		std::cout << "Failed to init TTF";
	}
	
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "Warning: Linear texture filtering not enabled!";
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError();
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError();
	}

	mainGameWindow = SDL_CreateWindow("Potato Games - Fallings", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	checkNotNull(mainGameWindow, "mainGameWindow");

	mainGameWindowRenderer = SDL_CreateRenderer(mainGameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	checkNotNull(mainGameWindow, "mainGameWindowRenderer");

	gameBackgroundTexture = new imageTexture(mainGameWindowRenderer, "assets/png/BG/BG.png");
	gameFloorTexture = new imageTexture(mainGameWindowRenderer, "assets/png/Tiles/2.png");
}

void GameController::startGame()
{
	bool running = true;
	SDL_Event gameEvent;

	TextTexture timePassedText;
	timePassedText.setFont("fonts/lazy.ttf", 28);
	timePassedText.setColor(0, 0, 0);

	TextTexture frameCountText;
	frameCountText.setFont("fonts/lazy.ttf", 28);
	frameCountText.setColor(0, 0, 0);

	int frameGenerated = 0;

	std::stringstream timePassed;
	std::stringstream frameCountNumberText;

	Character mainCharacter(SCREEN_WIDTH / 2, SCREEN_HEIGHT - floorRect.h - 40, mainGameWindowRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	EneryController enermyController (SCREEN_WIDTH, SCREEN_HEIGHT, mainGameWindowRenderer, &points);

	enermyController.addEnermy();

	int timeLeftInSeconds = 0;
	float frameCountNumber = 0;
	
	while(running){
		while (SDL_PollEvent(&gameEvent)) {
			if (gameEvent.type == SDL_QUIT) {
				running = false;
			}
		}

		if (timeLeftInSeconds < 0) {
			renderGameEnd();
			renderGame();
			continue;
		}

		renderBackground();

		// Render the main character
		float currentTicks = (float) SDL_GetTicks();
		mainCharacter.handleEvent(currentTicks);
		
		enermyController.update(currentTicks, mainCharacter.getCurrentPosition());

		timeLeftInSeconds = static_cast<int> (currentTicks / 1000);
		timeLeftInSeconds = 60 - timeLeftInSeconds;

		frameCountNumber = frameGenerated / (SDL_GetTicks() / 1000.f);;
		if (frameCountNumber > 2000000)
		{
			frameCountNumber = 0;
		}

		timePassed.str("");
		timePassed << timeLeftInSeconds;

		frameCountNumberText.str("");
		frameCountNumberText << frameCountNumber;

		timePassedText.renderText(timePassed.str().c_str(), mainGameWindowRenderer, 200, 0, 20, 20);
		frameCountText.renderText(frameCountNumberText.str().c_str(), mainGameWindowRenderer, 90, 20, 50, 20);
		
		renderGame();
		frameGenerated++;

	}
	closeGame();
}

void GameController::closeGame()
{
	delete gameBackgroundTexture;
	delete gameFloorTexture;
	SDL_DestroyRenderer(mainGameWindowRenderer);
	SDL_DestroyWindow(mainGameWindow);
}

void GameController::renderGame()
{
	SDL_RenderPresent(mainGameWindowRenderer);

}

GameController::~GameController(){}

void GameController::checkNotNull(void * inputVariable, char *name)
{
	if (inputVariable == NULL) {
		printf("Error: %s is null, ", name);
	}
}

void GameController::renderBackground()
{
	gameBackgroundTexture->render();
	gameFloorTexture->renderWithRect(&floorRect);

	TextTexture indicateTimeText;
	indicateTimeText.setFont("fonts/lazy.ttf", 28);
	indicateTimeText.setColor(0, 0, 0);
	indicateTimeText.renderText("Time Left: ", mainGameWindowRenderer, 0, 0, 200, 20);

	TextTexture frameText;
	frameText.setFont("fonts/lazy.ttf", 28);
	frameText.setColor(0, 0, 0);
	frameText.renderText("Frame: ", mainGameWindowRenderer, 0, 20, 100, 20);

	TextTexture PointsText;
	PointsText.setFont("fonts/lazy.ttf", 28);
	PointsText.setColor(0, 0, 0);
	PointsText.renderText("Points: ", mainGameWindowRenderer, SCREEN_WIDTH - 120, 10, 80, 20);

	TextTexture ScoreText;
	std::stringstream val;
	val << points;
	ScoreText.setFont("fonts/lazy.ttf", 28);
	ScoreText.setColor(0, 0, 0);
	PointsText.renderText(val.str().c_str(), mainGameWindowRenderer, SCREEN_WIDTH - 50, 10, 20, 20);
}

void GameController::renderGameEnd()
{
	gameBackgroundTexture->render();

	TextTexture PointsText;
	PointsText.setFont("fonts/lazy.ttf", 28);
	PointsText.setColor(0, 0, 0);
	PointsText.renderText("Points: ", mainGameWindowRenderer, SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT-400, 200, 120);
	
	gameFloorTexture->renderWithRect(&floorRect);
}
