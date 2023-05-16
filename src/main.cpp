// // On linux compile with:
// // g++ -std=c++17 main.cpp -o prog -lSDL2

// // C++ Standard Libraries
// #include <iostream>

// // Third-party library
// #include <SDL2/SDL.h>

// int main(int argc, char* argv[]){

//     // Create a window data type
//     // This pointer will point to the 
//     // window that is allocated from SDL_CreateWindow
//     SDL_Window* window=nullptr;

//     // Initialize the video subsystem.
//     // If it returns less than 1, then an
//     // error code will be received.
//     if(SDL_Init(SDL_INIT_VIDEO) < 0){
//         std::cout << "SDL could not be initialized: " <<
//                   SDL_GetError();
//     }else{
//         std::cout << "SDL video system is ready to go\n";
//     }

//     // Request a window to be created for our platform
//     // The parameters are for the title, x and y position,
//     // and the width and height of the window.
//     window = SDL_CreateWindow("C++ SDL2 Window",
//             0,
//             2500,
//             640,
//             480,
//             SDL_WINDOW_SHOWN);

//     // We add a delay in order to see that our window
//     // has successfully popped up.
//     SDL_Delay(3000);

//     // We destroy our window. We are passing in the pointer
//     // that points to the memory allocated by the 
//     // 'SDL_CreateWindow' function. Remember, this is
//     // a 'C-style' API, we don't have destructors.
//     SDL_DestroyWindow(window);
    
//     // We safely uninitialize SDL2, that is, we are
//     // taking down the subsystems here before we exit
//     // our program.
//     SDL_Quit();
//     return 0;
// }





#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "renderwindow.hpp"
#include "entity.hpp"


int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);

	SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");

    // Entity entities[4] = {Entity(0, 0, grassTexture),
    //                       Entity(30, 0, grassTexture),
    //                       Entity(30, 30, grassTexture),
    //                       Entity(30, 60, grassTexture)};

    std::vector<Entity> entitiees = {Entity(Vector2f(0, 0), grassTexture),
                         			 Entity(Vector2f(30, 0), grassTexture),
                           			 Entity(Vector2f(30, 30), grassTexture),
                          			 Entity(Vector2f(30, 60), grassTexture)};
    {
	    Entity wilson(Vector2f(100, 50), grassTexture);

	    entitiees.push_back(wilson);
	    
	}



	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		window.clear();
		

		for (Entity& e : entitiees)
		{ 
			window.render(e);
		}


		window.display();

	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}
