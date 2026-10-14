#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include <random>

#include "global.h"
#include "app.h"
#include "text_container.h"

const char* app_name		= "dynamic-text-renderer";
const char* app_version		= "v0.n";
const char* app_identifier	= "com.popapan.dynamic-text-renderer";
const char* window_title	= "Dynamic Text Renderer";

SDL_InitFlags init_flags				= SDL_INIT_VIDEO | SDL_INIT_AUDIO;
SDL_RendererLogicalPresentation mode	= SDL_LOGICAL_PRESENTATION_LETTERBOX;

std::vector<SDL_Texture*> glyph_textures;
TextContainer text_container;
App app;

// <Interface> Methods

void get_font_textures(
	const char* file_name,
	std::vector<SDL_Texture*>* textures,
	SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont(file_name, 32);

	// For each printable character, create a texture	
	// that can be rendered to the window.
	for (int i = 32; i < 127; i++)
	{
		SDL_Surface* glyph_surface = TTF_RenderGlyph_Blended(
			font,
			char(i),
			SDL_Color{ 255, 255, 255, 255 }
		);
		SDL_Texture* glyph_texture = SDL_CreateTextureFromSurface(
			renderer,
			glyph_surface
		);
		(*textures).push_back(glyph_texture);
	}
	TTF_CloseFont(font);
}

// Application Life-cycle Methods

SDL_AppResult SDL_AppInit(
		void** app_state,
		int arg_c,
		char* arg_v[])
{
	srand(time(0));
	// Set the app's metadata before actually initialising the window & SDL subsystems.
	// Operating systems will default to fallback properties otherwise.
	SDL_SetAppMetadata(
			app_name,
			app_version,
			app_identifier
	);

	// <Initialise subsystems.>
	// 
	bool sdl_success = SDL_Init(init_flags);
	bool window_renderer_success = SDL_CreateWindowAndRenderer(
			window_title,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY,
			&window, &renderer
	);
	bool ttf_success = TTF_Init();

	std::string error_message;

	if (!sdl_success)
		error_message = "Couldn't initialise SDL: %s";
	else if (!window_renderer_success)
		error_message = "Couldn't create window/renderer: %s";
	else if (!ttf_success)
		error_message = "Couldn't initialise TTF: %s";

	if (!error_message.empty()) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Log(error_message.c_str(), SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_SetRenderLogicalPresentation(
			renderer,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			mode
	);

	get_font_textures("aovel-sans-rounded.ttf", &glyph_textures, renderer);
	app.on_start();

	TTF_Font* font = TTF_OpenFont("aovel-sans-rounded.ttf", 32);

	text_container = TextContainer(
		100, 345,
		0,
		font,
		"Evil, ominous red text of doom, death and destruction.",
		&glyph_textures
	);

	return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void* app_state)
{
	SDL_RenderClear(renderer);
	app.on_update();
	text_container.render_text(renderer);
	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void* app_state, SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_EVENT_QUIT:
			return SDL_APP_SUCCESS;
		default:
			return SDL_APP_CONTINUE;
	}
}


void SDL_AppQuit(void* app_state, SDL_AppResult result)
{
	app.on_quit();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
