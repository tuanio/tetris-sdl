#include "Tetris.h"
#include <iostream>

//SDL2.lib
//SDL2main.lib
//SDL2_image.lib
//SDL2_mixer.lib

int main(int argc, char* argv[])
{
	using namespace std;
	//srand(time(0));
	Tetris* tetris = new Tetris();
	bool gameOverFirstTime = true;
	if (tetris->init())
	{
		while (tetris->isrunning())
		{	
			tetris->setCurrentTime(SDL_GetTicks());
			tetris->handleEvents();
			bool isGameOver = tetris->gameplay();
			if (isGameOver) {
				if (gameOverFirstTime)
					tetris->initResultScreen();
				gameOverFirstTime = false;
			}
			else {
				gameOverFirstTime = true;
			}
			tetris->updateRender();
		}
	}
	else
	{
		cout << "Failed to initialize";
	}

	tetris->clean();

	return 0;
}