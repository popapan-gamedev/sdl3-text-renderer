#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>
#include "global.h"
#include "app.h"

const char* app_name		= "dynamic-text-renderer";
const char* app_version		= "v0.n";
const char* app_identifier	= "com.popapan.dynamic-text-renderer";
const char* window_title	= "Dynamic Text Renderer";

SDL_InitFlags init_flags				= SDL_INIT_VIDEO | SDL_INIT_AUDIO;
SDL_RendererLogicalPresentation mode	= SDL_LOGICAL_PRESENTATION_LETTERBOX;

App app;


SDL_AppResult SDL_AppInit(
		void** app_state,
		int arg_c,
		char* arg_v[])
{
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
			SDL_WINDOW_RESIZABLE,
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

	app.on_start();

	return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void* app_state)
{
	SDL_RenderClear(renderer);
	app.on_update();
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
