#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderwindow.hpp"
#include "game.hpp"

// NON-preventable leaks
// ==24356== HEAP SUMMARY:
// ==24356==     in use at exit: 303,162 bytes in 3,654 blocks
// ==24356==   total heap usage: 57,276 allocs, 53,622 frees, 15,001,033 bytes allocated
// ==24356== 
// ==24356== LEAK SUMMARY:
// ==24356==    definitely lost: 896 bytes in 3 blocks
// ==24356==    indirectly lost: 11,240 bytes in 38 blocks
// ==24356==      possibly lost: 0 bytes in 0 blocks
// ==24356==    still reachable: 291,026 bytes in 3,613 blocks
// ==24356==         suppressed: 0 bytes in 0 blocks
// ==24356== Rerun with --leak-check=full to see details of leaked memory

int main(int argc, char* args[])
{

	if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
		std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	{
		// Create a new scope for `RenderWindow` and `App` deconstructors to be called
		// Ensures order --> ~Textures(), ~RenderWindow(), SDL_Quit()
		RenderWindow window("THE GAME", 1280, 720);

		Game game(window);

		game.run();
	}

	
	std::cout << "quit" << std::endl;
	IMG_Quit();
	SDL_Quit();

	return 0;
}
