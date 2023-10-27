#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
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

int main(int argc, char* argv[])
{

	if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
		std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	{
		// Create a new scope for `RenderWindow` and `App` deconstructors to be called
		// Ensures order --> ~Textures(), ~RenderWindow(), SDL_Quit()

		for (int i = 1; i < argc; ++i) {
			std::string arg = argv[i];
			if (arg == "--debug") {
				Constants::debugMode = true;
			}
		}
		RenderWindow window("THE GAME", Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
		ResourceManager::initialize(&(window.getRenderer()), std::vector<std::string>{"./res/monkey.png", "./res/first-run-animation-Sheet.png"});

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

		// Set the location for imgui.ini
		ImGui::GetIO().IniFilename = "build/imgui.ini";

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();
		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForSDLRenderer(&window.getWindow(), &window.getRenderer());
		ImGui_ImplSDLRenderer2_Init(&window.getRenderer());

		

		Game game(window);

		game.run();
	}

	
	std::cout << "quit" << std::endl;

	ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
	IMG_Quit();
	SDL_Quit();

	return 0;
}
