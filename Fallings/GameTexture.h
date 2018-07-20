#include <vector>
#include <SDL_ttf.h>

#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H
class TextTexture
{
public:
	void renderText(const char * text, SDL_Renderer *renderer, int x, int y, int w, int h);
	void setFont(char *fontPath, int fontSize);
	void setColor(int r, int g, int b);
	void close();
private:
	TTF_Font *font = NULL;
	SDL_Color myColor;
	SDL_Texture *generatedTexture = NULL;
};

class imageTexture
{
public:
	imageTexture(SDL_Renderer *renderer, char *filePath);
	void render();
	void renderWithRect(SDL_Rect * rect);
	~imageTexture();
private:

	SDL_Renderer *mainRenderer = NULL;
	
	SDL_Texture *myTexture = NULL;
};


class CharacterTexture 
{
public:
	CharacterTexture(SDL_Renderer *renderer);
	~CharacterTexture();
	SDL_Texture *convertImageToTexture(char *filePath);
	
	void renderMoveLeft(SDL_Rect *renderingRect);
	void renderMoveRight(SDL_Rect *renderingRect);
	void renderStop(SDL_Rect *renderingRect);
private:
	SDL_Renderer *mainRenderer;
	std::vector <SDL_Texture *> runningTextures;
	std::vector <SDL_Texture *> stoppingTextures;

	unsigned int nextLeftTextureIndex = 0;
	unsigned int nextRightTextureIndex = 0;
	unsigned int nextStopTextureIndex = 0;

	int lastRunningSwitchTime = 0;
	int lastStopRunningTime = 0;
	int lastLeftRunningSwitchTime = 0;

	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

	// 0 means left, 1 means right
	int previousCharacterDirection = 0;
	int imageWidth = 0;
	int imageHeight = 0;
};

class EnermyTexture {
public:
	EnermyTexture(SDL_Renderer *renderer);
	~EnermyTexture();
	void renderEnermy(SDL_Rect *renderRect);
private:
	SDL_Texture *convertImageToTexture(char *filePath);
	SDL_Renderer *mainRenderer = NULL;
	SDL_Texture *enermyTexture = NULL;
};
#endif
