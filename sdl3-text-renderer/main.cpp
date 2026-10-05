#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void** app_state, int arg_c, char* arg_v[]) {
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* app_state) {
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* app_state, SDL_Event* event) {

	switch (event->type) {

	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;

	default:
		return SDL_APP_CONTINUE;
	}
}

void SDL_AppQuit(void* app_state, SDL_AppResult result) {
	return;
}