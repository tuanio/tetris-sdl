#include <iostream>
#include "Tetris.h"
#include <string>

using namespace std;
/*
	0	1	2	3
	4	5	6	7
*/
const int Tetris::figures[7][4] =
{
	0,1,2,3,	// I
	0,4,5,6,	// J
	2,6,5,4,	// L
	1,2,5,6,	// O
	2,1,5,4,	// S
	1,4,5,6,	// T
	0,1,5,6,	// Z
};
bool Tetris::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		initMusic("music.flac");
		//playMusic();

		if (TTF_Init() == -1) {
			cout << "There's an error when init TTF" << endl;
		}
		font = TTF_OpenFont("fonts/consolas.ttf", 25);
		if (font == NULL) {
			cout << "There's an error when load font" << endl;
		}

		text.SetColor(Text::WHITE_TEXT);

		initHome();
}
	else
		return (running = false);

	running = true;
	return true;
}

void Tetris::initHome() {
	currentScreen = HomeScreen;

	string titleStr = "Home page";
	const char* title = titleStr.c_str();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	int imgFlags = IMG_INIT_JPG;
	int initted = IMG_Init(imgFlags);
	if ((initted & imgFlags) != imgFlags)
		std::cout << "Failed to init required png support\n" << "IMG_Init() Error : " << IMG_GetError() << std::endl;
	SDL_Surface* loadSurf = IMG_Load("img/hello.jpg");
	background = SDL_CreateTextureFromSurface(render, loadSurf);
	SDL_FreeSurface(loadSurf);
}

void Tetris::initHelp() {
	currentScreen = HelpScreen;

	string titleStr = "Help page";
	const char* title = titleStr.c_str();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	int imgFlags = IMG_INIT_JPG;
	int initted = IMG_Init(imgFlags);
	if ((initted & imgFlags) != imgFlags)
		std::cout << "Failed to init required png support\n" << "IMG_Init() Error : " << IMG_GetError() << std::endl;
	SDL_Surface* loadSurf = IMG_Load("img/help.jpg");
	background = SDL_CreateTextureFromSurface(render, loadSurf);
	SDL_FreeSurface(loadSurf);
}

void Tetris::initResultScreen() {
	currentScreen = ResultScreen;

	string titleStr = "Result page";
	const char* title = titleStr.c_str();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	int imgFlags = IMG_INIT_JPG;
	int initted = IMG_Init(imgFlags);
	if ((initted & imgFlags) != imgFlags)
		std::cout << "Failed to init required png support\n" << "IMG_Init() Error : " << IMG_GetError() << std::endl;
	SDL_Surface* loadSurf = IMG_Load("img/end.jpg");
	background = SDL_CreateTextureFromSurface(render, loadSurf);
	SDL_FreeSurface(loadSurf);

	string str_val = to_string(score);
	text.SetText(str_val);
	text.LoadFromRenderText(font, render);
	xp = 105;
	yp = 260;
}

void Tetris::initGamePlay() {
	currentScreen = GameScreen;

	string titleStr = "Game play";
	const char* title = titleStr.c_str();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	int imgFlags = IMG_INIT_PNG;
	int initted = IMG_Init(imgFlags);
	if ((initted & imgFlags) != imgFlags)
		std::cout << "Failed to init required png support\n" << "IMG_Init() Error : " << IMG_GetError() << std::endl;
	SDL_Surface* loadSurf = IMG_Load("img/background.png");
	background = SDL_CreateTextureFromSurface(render, loadSurf);
	SDL_FreeSurface(loadSurf);
	loadSurf = IMG_Load("img/blocks.png");
	blocks = SDL_CreateTextureFromSurface(render, loadSurf);
	SDL_FreeSurface(loadSurf);
	nextTetrimino();
}

void Tetris::initMusic(const char* filepath) {
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 640);

	music = Mix_LoadMUS(filepath);
	if (music != NULL)
		printf("Loaded the file\n");
	else
		printf("Mix_LoadMUS: %s\n", Mix_GetError());
}

void Tetris::playMusic() {
	if (isPlay && Mix_PlayMusic(music, -1) == -1)
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
}


void Tetris::nextTetrimino()
{
	color = 1 + rand() % 7;
	int n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		items[i].x = figures[n][i] % 4;
		items[i].y = int(figures[n][i] / 4);
	}
}

int Tetris::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				rotate = true;
				break;
			case SDLK_LEFT:
				dx = -1;
				break;
			case SDLK_RIGHT:
				dx = 1;
				break;
			case SDLK_m: // mute or not
				isPlay = !isPlay;
				if (!isPlay) Mix_PauseMusic(); // stop music
				else Mix_ResumeMusic();
				break;
			default:
				break;
			}
		case SDL_MOUSEBUTTONDOWN:
			int x = e.button.x;
			int y = e.button.y;
			switch (currentScreen) {
			case HomeScreen:
				if (x >= 103 && x <= 151 && y >= 234 && y <= 247) {
					SDL_DestroyWindow(window);
					initGamePlay();
					return 1;
				}
				else if (x >= 117 && x <= 181 && y >= 280 && y <= 290) {
					SDL_DestroyWindow(window);
					initHelp();
					return 2;
				}
				else if (x >= 101 && x <= 201 && y >= 318 && y <= 329) {
					running = false;
					return 3;
				}
				break;
			case HelpScreen:
				if (x >= 92 && x <= 203 && y >= 371 && y <= 428) {
					SDL_DestroyWindow(window);
					initHome();
				}
				break;
			case ResultScreen:
				if (x >= 90 && x <= 204 && y >= 306 && y <= 326) {
					// reset
					score = 0;
					dx = 0;
					color = 1;
					rotate = false;
					for (int i = 0; i < Lines; i++) {
						for (int j = 0; j < Cols; j++) {
							field[i][j] = 0;
						}
					}
					for (int i = 0; i < 4; i++) {
						items[i].x = 0;
						items[i].y = 0;
						backup[i].x = 0;
						backup[i].y = 0;
					}

					SDL_DestroyWindow(window);
					initGamePlay();

					return 1;
				}
				else if (x >= 111 && x <= 181 && y >= 361 && y <= 386) {
					running = false;
					return 3;
				}
				break;
			}
			break;
		}
		// xác định tọa độ
		/*if (e.button.button == SDL_BUTTON_LEFT) {
			int x = e.button.x;
			int y = e.button.y;
			cout << x << ' ' << y << endl;
		}*/
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_DOWN])
		delay = 50;
	return 0;
}

void Tetris::setRectPos(SDL_Rect& rect, int x, int y, int w, int h)
{
	rect = { x, y, w, h };
}

void Tetris::moveRectPos(SDL_Rect& rect, int x, int y)
{
	rect.x += x;
	rect.y += y;
}

bool Tetris::isvalid()
{
	for (int i = 0; i < 4; i++)
		if (items[i].x < 0 || items[i].x >= Cols || items[i].y >= Lines)
			return false;
		else if (field[items[i].y][items[i].x])
			return false;
	return true;
}


bool Tetris::gameplay()
{

	////////// backup
	for (int i = 0; i < 4; i++)
		backup[i] = items[i];
	////////// move
	if (dx)
	{
		for (int i = 0; i < 4; i++)
		{
			items[i].x += dx;
		}
		if (!isvalid())
			for (int i = 0; i < 4; i++)
				items[i] = backup[i];
	}

	///////// rotate
	if (rotate)
	{
		Point p = items[2];	// center of rotation
		for (int i = 0; i < 4; i++)
		{
			int x = items[i].y - p.y;
			int y = items[i].x - p.x;
			items[i].x = p.x - x;
			items[i].y = p.y + y;
		}
		if (!isvalid())
			for (int i = 0; i < 4; i++)
				items[i] = backup[i];
	}
	///////// tick
	if (currentTime - startTime > delay)
	{
		for (int i = 0; i < 4; i++)
			backup[i] = items[i];
		for (int i = 0; i < 4; i++)
			items[i].y++;
		if (!isvalid())
		{
			for (int i = 0; i < 4; i++)
				field[backup[i].y][backup[i].x] = color;
			nextTetrimino();
		}

		startTime = currentTime;
	}


	//////// check lines
	int k = Lines - 1;
	for (int i = k; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < Cols; j++)
		{
			if (field[i][j])
				count++;
			field[k][j] = field[i][j];
		}
		if (count < Cols) {
			k--;
		}
		else if (count == Cols) {
			cout << "Add score" << endl;
			score += unit_score;
		}
	}
	bool gameover = false;
	for (int j = 0; j < Cols; j++) {
		bool full = true;
		for (int i = 0; i < Lines; i++) {
			bool foo = false;
			for (int k = -2; k <= 2; k++) {
				int dy = j + k;
				if (dy >= 0 && dy < Cols)
					foo |= field[i][dy];
			}
			full &= foo;
			// với mỗi hàng, check 5 thằng liền kề nhau xem có gạch hay không
			// nếu mỗi hàng có từ 1 đến 5 gạch, và liên tục như vậy đến tất cả hàng
			// thì game kết thúc
		}
		gameover |= full;
	}

	if (gameover) {
		return true;
	}

	dx = 0;
	rotate = false;
	delay = 300;

	return false;
}

void Tetris::updateRender()
{
	SDL_RenderCopy(render, background, NULL, NULL);
	for (int i = 0; i < Lines; i++)
		for (int j = 0; j < Cols; j++)
			if (field[i][j])
			{
				setRectPos(srcR, field[i][j] * BlockW);
				setRectPos(destR, j * BlockW, i * BlockH);
				moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
				SDL_RenderCopy(render, blocks, &srcR, &destR);
			}
	for (int i = 0; i < 4; i++)
	{
		setRectPos(srcR, color * BlockW);
		setRectPos(destR, items[i].x * BlockW, items[i].y * BlockH);
		moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
		SDL_RenderCopy(render, blocks, &srcR, &destR);
	}
	text.RenderText(render, xp, yp);
	SDL_RenderPresent(render);

}

void Tetris::clean()
{
	SDL_DestroyTexture(blocks);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(render);
	IMG_Quit();
	SDL_Quit();
}