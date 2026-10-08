#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>

#include "global.h"

SDL_Window* window		= NULL;
SDL_Renderer* renderer	= NULL;
TTF_Font* font			= NULL;

SDL_Color clear_color	{ 0, 0, 0, 255 };
const char* font_file	= "PressStart2P.ttf";
int point_size			= 12;