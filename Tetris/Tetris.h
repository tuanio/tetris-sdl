#pragma once
#ifndef TETRIS_H_
#define TETRIS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Text.h"

class Tetris
{
public:
	Tetris()
	{
	}
	~Tetris()
	{
	}

	void setCurrentTime(Uint32 t)
	{
		currentTime = t;
	}

	bool isrunning()
	{
		return running;
	}

	int getScore() {
		return score;
	}

	bool getIsPlay() {
		return isPlay;
	}

	bool isvalid();

	bool init();
	void initHome();
	void initHelp();
	void initResultScreen();
	void initGamePlay();
	void nextTetrimino();
	int handleEvents();
	void setRectPos(SDL_Rect& rect, int x = 0, int y = 0, int w = BlockW, int h = BlockH);
	void moveRectPos(SDL_Rect& rect, int x, int y);
	bool gameplay();
	void updateRender();
	void clean();
	void initMusic(const char* filepath);
	void playMusic();

private:
	bool isPlay = true;
	int score = 0;
	int unit_score = 100;
	enum { ScreenW = 300, ScreenH = 480 };
	enum { BlockW = 18, BlockH = 18 };
	enum { Lines = 20, Cols = 10 };
	enum { HomeScreen, GameScreen, HelpScreen, ResultScreen };
	int currentScreen = HomeScreen;
	SDL_Window* window = NULL;
	SDL_Renderer* render = NULL;
	SDL_Texture* background = NULL, *blocks = NULL;
	SDL_Rect srcR = { 0, 0, BlockW, BlockH }, destR = { 0, 0, BlockW, BlockH };

	Mix_Chunk* chunk = NULL;
	Mix_Music* music = NULL;

	bool running = false;
	int field[Lines][Cols] = { 0 };
	static const int figures[7][4];
	struct Point
	{
		int x, y;
	} items[4], backup[4];
	int color = 1;
	int dx = 0;
	bool rotate = false;
	unsigned int delay = 300;
	Uint32 startTime = 0, currentTime = 0;
	Text text;
	TTF_Font* font = NULL;
	int xp = 0, yp = 0;
};


#endif // !TETRIS_H_
