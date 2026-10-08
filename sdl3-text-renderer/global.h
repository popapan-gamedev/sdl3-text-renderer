#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>

extern SDL_Color clear_color;
extern const char* font_file;
extern int point_size;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

#define WINDOW_WIDTH		1280
#define WINDOW_HEIGHT		720
#define UPDATE_INTERNVAL	16