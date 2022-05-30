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
	const char* title = "Tetris";
	if (tetris->init(title))
	{
		while (tetris->isrunning())
		{	
			tetris->setCurrentTime(SDL_GetTicks());
			tetris->handleEvents();
			bool isGameOver = tetris->gameplay();
			if (isGameOver) {
				const char* title = "Game Over";
				char message[200];
				sprintf_s(message, "Game is Over, you score is %d!!!", tetris->getScore());
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, NULL);
				break;
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