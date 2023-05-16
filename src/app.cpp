#include <iostream>
#include <vector>

#include "app.hpp"
#include "entity.hpp"
#include "texture.hpp"

void App::run() const {
    Texture grassTexture(_window.getRenderer(), "res/spaceDorito.png");







    std::vector<Entity> entitiees = {Entity(Vector2f(0, 0), grassTexture.get()),
                         			 Entity(Vector2f(30, 0), grassTexture.get()),
                           			 Entity(Vector2f(30, 30), grassTexture.get()),
                          			 Entity(Vector2f(30, 60), grassTexture.get())};
    {
	    Entity wilson(Vector2f(100, 50), grassTexture.get());

	    entitiees.push_back(wilson);
	    
	}


	bool TESTHideImages = false;

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
        _inputManager->update();

		if (_inputManager->isKeyDown(SDL_SCANCODE_SPACE)) 
        {
			TESTHideImages = true;
        }

		if (_inputManager->isKeyUp(SDL_SCANCODE_SPACE))
        {
            TESTHideImages = false;
        }


		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		_window.clear();
		
		if (!TESTHideImages) {
			for (Entity& e : entitiees)
		{ 
			_window.render(e);
		}
		}
		

		_window.display();

	}

	
}
