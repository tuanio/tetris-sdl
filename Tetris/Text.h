#pragma once
#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class Text {
public:
	Text();
	~Text();
	
	enum TextColor {
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};

	bool LoadFromFile(string path);
	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();
	
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);

	void RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = 0, double angle = 0.0, SDL_Point* center = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int GetWidth() const { return width; };
	int GetHeight() const { return height; };

	void SetText(string& text) { str_val = text; };
	string GetText() const { return str_val; };
private:
	string str_val;
	SDL_Color text_color;
	SDL_Texture* texture;
	int width;
	int height;
};

#endif