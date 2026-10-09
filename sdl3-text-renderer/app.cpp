#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <iostream>

#include "app.h"
#include "global.h"

TTF_Font* sdl_font;


void get_textures_from_glyphs(
		TTF_Font* font,
		std::vector<SDL_Texture*>* glyph_textures,
		SDL_Color foreground_color,
		SDL_Color background_color)
{
	for (int i = 32; i < 127; i++)
	{
		SDL_Surface* surface = TTF_RenderGlyph_LCD(
				font,
				char(i),
				foreground_color,
				background_color
		);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		glyph_textures->push_back(texture);
	}
}

// # Public API methods

void App::on_start()
{
	sdl_font = TTF_OpenFont("aovel-sans-rounded.ttf", 72);

	std::vector<SDL_Texture*> glyph_textures;
	get_textures_from_glyphs(font, &glyph_textures, SDL_Color{ 255, 255, 255, 255 }, SDL_Color{ 0, 0, 0, 255 });
	std::cout << glyph_textures.size() << std::endl;
	return;
}


void App::on_update()
{
	return;
}


void App::on_quit()
{
	TTF_CloseFont(sdl_font);
}
