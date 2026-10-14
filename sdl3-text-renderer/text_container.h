#pragma once
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <string>
#include <vector>
#include <iostream>
#include <random>

class TextContainer
{
public:

	int x_pos;
	int y_pos;
	int width;

	std::string text;
	std::vector<SDL_FRect> glyph_rects;
	std::vector<SDL_Texture*>* glyph_textures;


	TextContainer(
			int new_x_pos,
			int new_y_pos,
			int new_width,
			TTF_Font* font,
			std::string new_text,
			std::vector<SDL_Texture*>* new_textures)
	{
		x_pos = new_x_pos;
		y_pos = new_y_pos;
		width = new_width;
		text = new_text;
		glyph_textures = new_textures;

		int font_height = TTF_GetFontHeight(font);
		int rect_x_pos = x_pos;
		int rect_y_pos = y_pos + font_height;

		char prev_ch = NULL;

		for (int i = 0; i < text.size(); i++) {
			
			char ch = text[i];
			int min_x, max_x, min_y, max_y, advance = 0;
			TTF_GetGlyphMetrics(font, ch, &min_x, &max_x, &min_y, &max_y, &advance);

			int kerning = 0;
			if (prev_ch)
				TTF_GetGlyphKerning(font, ch, prev_ch, &kerning);

			float w, h;
			SDL_GetTextureSize((*glyph_textures)[ch - 32], &w, &h);

			SDL_FRect rect {
					rect_x_pos + min_x + kerning,
					y_pos + font_height,
					w,
					h
			};

			glyph_rects.push_back(rect);
			rect_x_pos += advance;
			prev_ch = ch;
		}
	}


	TextContainer(void)
	{
		x_pos = y_pos	= 0;
		width			= 0;
		text			= "";
		glyph_rects		= {};
		glyph_textures	= {};
	}


	void render_text(SDL_Renderer* renderer)
	{
		for (int i = 0; i < text.size(); i++)
		{
			char ch = text[i];

			SDL_FRect rect = glyph_rects[i];
			rect.x += rand() % 4;
			rect.y += rand() % 4;

			SDL_SetTextureColorMod((*glyph_textures)[ch - 32], 255, 0, 0);

			SDL_RenderTexture(
					renderer,
					(*glyph_textures)[ch - 32],
					NULL,
					&rect
			);
			SDL_SetTextureColorMod((*glyph_textures)[ch - 32], 255, 255, 255);
		}
	}
};