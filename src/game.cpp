#include <iostream>
#include <vector>
#include <iostream>

#include "game.hpp"
#include "2dphysics.hpp"
#include "texture.hpp"
#include "player.hpp"
#include "sword.hpp"
#include "grapplinghook.hpp"
#include "rope.hpp"

void Game::handleInputs(Player& player1) {
	_inputManager->update(*this);
	
	// player 1
	player1.setLookAngle({ static_cast<float>(_inputManager->getMouseX()), static_cast<float>(_inputManager->getMouseY())});
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

	if (_inputManager->isKeyDown(SDL_SCANCODE_SPACE))
	{
		player1.jump();
	}

    if (_inputManager->isMouseButtonDown(SDL_BUTTON_LEFT))
    {
		player1.attack();
    }

}

void Game::run() {
    // Texture spaceDoritoTex(_window.getRenderer(), "res/spaceDorito.png");
	// Texture swordTex(_window.getRenderer(), "res/sword.png");

	
	Player wilson({-100, 55});
	// Player spilson({200, 55});

	wilson.setPosition({0, 0});
	// spilson.setPosition({500,500});

	Sword doriSword({100, -200}, wilson);
	// Sword spillySword({-100, -200}, spilson);

	// GrapplingHook hook(wilson);

	// spilson.equipItem(&spillySword);
	// wilson.equipItem(&hook);

	Rope rope({0, 200}, {1000, 200}, 15);
	
	


	Uint32 prevTime = SDL_GetTicks();
	float deltaTime = 0;


	while (this->_gameRunning)
	{
		Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f; // Convert to seconds
        prevTime = currentTime;
        
		handleInputs(wilson);

		// clear
		_window.clear();

		// update
		wilson.update(deltaTime);
		// spilson.update(deltaTime);
		rope.update(deltaTime);

		rope.setEndAnchor(wilson.getPosition());

		std::cout << rope << std::endl;
		
		// _collisionManager->checkAndResolve(wilson, spilson);
		_collisionManager->resolveBounds(wilson);
		// _collisionManager->resolveBounds(spilson);
		

		// render
		_window.render(wilson);
		_window.render(rope);
		
		// display
		_window.display();
	}

	
}
