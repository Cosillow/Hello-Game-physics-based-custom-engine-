#include <iostream>
#include <vector>
#include <iostream>

#include "app.hpp"
#include "entity.hpp"
#include "texture.hpp"
#include "player.hpp"
#include "sword.hpp"

void App::handleInputs(Player& player1, Player& player2) const {
	_inputManager->update();
	if (_inputManager->isKeyDown(SDL_SCANCODE_W)) 
	{
		player1.moveUp(true);
	}

	if (_inputManager->isKeyUp(SDL_SCANCODE_W))
	{
		player1.moveUp(false);
	}

	if (_inputManager->isKeyDown(SDL_SCANCODE_S)) 
	{
		player1.moveDown(true);
	}

	if (_inputManager->isKeyUp(SDL_SCANCODE_S))
	{
		player1.moveDown(false);
	}

	if (_inputManager->isKeyDown(SDL_SCANCODE_A)) 
	{
		player1.moveLeft(true);
	}

	if (_inputManager->isKeyUp(SDL_SCANCODE_A))
	{
		player1.moveLeft(false);
	}

	if (_inputManager->isKeyDown(SDL_SCANCODE_D)) 
	{
		player1.moveRight(true);
	}

	if (_inputManager->isKeyUp(SDL_SCANCODE_D))
	{
		player1.moveRight(false);
	}

	// player 2
	if (_inputManager->isKeyDown(SDL_SCANCODE_UP)) 
	{
		player2.moveUp(true);
	}

	if (_inputManager->isKeyUp(SDL_SCANCODE_UP))
	{
		player2.moveUp(false);
	}
	
	if (_inputManager->isKeyDown(SDL_SCANCODE_DOWN)) 
	{
		player2.moveDown(true);
	}

	if (_inputManager->isKeyUp(SDL_SCANCODE_DOWN))
	{
		player2.moveDown(false);
	}

	if (_inputManager->isKeyDown(SDL_SCANCODE_LEFT)) 
	{
		player2.moveLeft(true);
	}

	if (_inputManager->isKeyUp(SDL_SCANCODE_LEFT))
	{
		player2.moveLeft(false);
	}

	if (_inputManager->isKeyDown(SDL_SCANCODE_RIGHT)) 
	{
		player2.moveRight(true);
	}

	if (_inputManager->isKeyUp(SDL_SCANCODE_RIGHT))
	{
		player2.moveRight(false);
	}
}

void App::run() const {
    Texture spaceDoritoTex(_window.getRenderer(), "res/spaceDorito.png");
	Texture swordTex(_window.getRenderer(), "res/sword.png");

	
	Player wilson({100, 55}, spaceDoritoTex, 1);
	Player spilson({200, 55}, spaceDoritoTex, 2); 

	Sword doriSword({-100, 200}, swordTex, wilson);
	Sword spillySword({100, 200}, swordTex, spilson);

	spilson.equipWeapon(&spillySword);
	wilson.equipWeapon(&doriSword);




	bool gameRunning = true;
	Uint32 prevTime = SDL_GetTicks();
	float deltaTime = 0;
	SDL_Event event;

	while (gameRunning)
	{
		Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f; // Convert to seconds
        prevTime = currentTime;
        
		handleInputs(wilson, spilson);

		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		// clear
		_window.clear();

		// update
		wilson.update(deltaTime);
		spilson.update(deltaTime);

		bool collision = false;
		// check collisions
		if (_collisionManager->checkCollision(spillySword, wilson)) {
			std::cout << "wilson has been touched by spillySword" << std::endl;
			collision = true;
		}
		if (_collisionManager->checkCollision(doriSword, spilson)) {
			std::cout << "spilson has been touched by doriSword" << std::endl;
			collision = true;
		}
		if (!collision) std::cout << "no collision" << std::endl;

		// render
		_window.render(wilson);
		_window.render(spilson);
		_window.render(spillySword);
		_window.render(doriSword);
		
		// display
		_window.display();
	}

	
}
