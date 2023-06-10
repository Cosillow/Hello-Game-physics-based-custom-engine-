#include <iostream>
#include <vector>
#include <string>
#include <iostream>

#include "game.hpp"
#include "2dphysics.hpp"
#include "player.hpp"
#include "sword.hpp"
#include "grapplinghook.hpp"
#include "rope.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"
#include "canvas.hpp"

void Game::handleInputs(Player& player1) {
	_inputManager->update(*this);
	
	// player 1
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
    


	// // canvas
    // const float panSpeed = 1.0f;
    // const float zoomSpeed = 6.0f;

    // // Pan canvas with middle mouse button
    // if (_inputManager->isMouseButtonDown(SDL_BUTTON_MIDDLE)) {
    //     float mouseX = _inputManager->getMousePosition().x;
    //     float mouseY = _inputManager->getMousePosition().y;

    //     float prevMouseX = _inputManager->getPreviousMousePosition().x;
    //     float prevMouseY = _inputManager->getPreviousMousePosition().y;

    //     float deltaMouseX = mouseX - prevMouseX;
    //     float deltaMouseY = mouseY - prevMouseY;

	// 	canvas.panX(deltaMouseX * panSpeed);
	// 	canvas.panY(deltaMouseY * panSpeed);
    // }

    // // Zoom canvas with scroll wheel
    // int scrollDelta = _inputManager->getMouseScrollDelta();
    // if (scrollDelta) canvas.zoom(scrollDelta * zoomSpeed);

	// // selection box
	// if (_inputManager->isMouseButtonDown(SDL_BUTTON_LEFT)) { canvas.drawBox(this->_inputManager->getMousePosition()); }
	// if (canvas.isSelecting() && this->_inputManager->isMouseButtonUp(SDL_BUTTON_LEFT)) { canvas.completeBox(this->_inputManager->getMousePosition()); }

}

void Game::run() {

	Player wilson({400, 200});
	Sword doriSword({100, -200}, wilson);
	// Canvas spriteTool;
	// spriteTool.setPhoto("./res/chimpsheet.png");


	Uint32 prevTime = SDL_GetTicks();
	float deltaTime = 0;
	while (this->_gameRunning)
	{
		Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f; // Convert to seconds
        prevTime = currentTime;
        
		handleInputs(wilson);

		// clear
		this->_window.clear();

		// update
		wilson.update(deltaTime);		
		this->_collisionManager->resolveBounds(wilson);
		
		// std::cout << wilson << std::endl;
		// render
		this->_window.render(wilson);
		
		// display
		this->_window.display();
	}
}
