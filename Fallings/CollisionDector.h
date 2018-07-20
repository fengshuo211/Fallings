#include <SDL.h>
#ifndef COLLISIONDECTOR_H
#define COLLISIONDECTOR_H

class CollisonDector
{
public:
	CollisonDector();
	~CollisonDector();
	bool check(SDL_Rect *rect1, SDL_Rect *rect2);
};
#endif
