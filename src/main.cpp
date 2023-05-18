#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderwindow.hpp"
#include "app.hpp"

// NON-preventable leaks
// ==11220== LEAK SUMMARY:
// ==11220==    definitely lost: 17 bytes in 1 blocks
// ==11220==    indirectly lost: 0 bytes in 0 blocks
// ==11220==      possibly lost: 304 bytes in 2 blocks
// ==11220==    still reachable: 241,365 bytes in 2,955 blocks
// ==11220==         suppressed: 0 bytes in 0 blocks

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

	
	std::cout << "quit" << std::endl;
	IMG_Quit();
	SDL_Quit();

	return 0;
}
