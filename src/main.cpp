#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderwindow.hpp"
#include "app.hpp"



int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	{
		// Create a new scope for `RenderWindow` and `App` deconstructors to be called
		// Ensures order --> ~Textures(), ~RenderWindow(), SDL_Quit()

		RenderWindow window("GAME v1.0", 1280, 720);

		App app(window);

		app.run();
	}

	SDL_Quit();

	return 0;
}
