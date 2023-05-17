#include <iostream>
#include <vector>

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

	
	Player wilson(Vector2f(100.0f, 55.0f), spaceDoritoTex, 1);
	Player spilson(Vector2f(200.0f, 55.0f), spaceDoritoTex, 2); 


	Sword spillySword(Vector2f(0.0f, 0.0f), spaceDoritoTex, spilson);
	spilson.equipWeapon(&spillySword);



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
		// spillySword.update(deltaTime);
		
		// render
		_window.render(wilson);
		_window.render(spilson);
		_window.render(spillySword);
		
		
		// display
		_window.display();
	}

	
}
