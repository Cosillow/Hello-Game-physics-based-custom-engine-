#include <iostream>
#include <vector>
#include <string>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "game.hpp"
#include "2dphysics.hpp"
#include "player.hpp"
#include "sword.hpp"
#include "grapplinghook.hpp"
#include "rope.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"
#include "canvas.hpp"
#include "platform.hpp"

void Game::handleInputs(Player& player1) {
	this->_inputManager->update(*this);

	// player 1
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_A)) 
	{
		player1.moveLeft(true);
	}
	if (this->_inputManager->isKeyUp(SDL_SCANCODE_A))
	{
		player1.moveLeft(false);
	}
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_D)) 
	{
		player1.moveRight(true);
	}
	if (this->_inputManager->isKeyUp(SDL_SCANCODE_D))
	{
		player1.moveRight(false);
	}
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_SPACE))
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
	Platform testForm({800,700}, 3);
	Platform testForm2({500,600}, 4);
	
	// Canvas spriteTool;

	Uint32 prevTime = SDL_GetTicks();
	float deltaTime = 0;
	while (this->_gameRunning)
	{
		Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f; // Convert to seconds
        prevTime = currentTime;
        
		this->handleInputs(wilson);

		// clear
		this->_window.clear();
		
		// update
		wilson.update(deltaTime);

		// resolve collisions
		this->_collisionManager->resolveBounds(wilson);
		this->_collisionManager->resolveBounds(wilson, testForm);
		this->_collisionManager->resolveBounds(wilson, testForm2);

		// std::cout << wilson.getPosition() << wilson.getHitbox()->_inCollision << wilson.getVelocity() << wilson.getAcceleration() << std::endl;
		

		// Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
		

		ImGui::ShowDemoWindow();


		ImGui::Checkbox("Debug mode", &Constants::debugMode);
		ImGui::SliderFloat("gravity", &Constants::GRAVITY, 0.0f, 10000.0f, "g = %.3f");
		ImGui::SliderFloat("player speed", &Constants::PLAYER_SPEED, 0.0f, 10000.0f, "s = %.3f");
		ImGui::SliderFloat("max player speed", &Constants::PLAYER_MAX_SPEED, 0.0f, 50.0f, "m = %.3f");
		ImGui::SliderFloat("jump force", &Constants::PLAYER_JUMP, 0.0f, 50.0f, "f = %.3f");
		// ImGui::SliderFloat("friction", &Constants::PLAYER_FRICTION, 0.0f, 10000.0f, "fr = %.3f");
		ImGui::SliderFloat("collision buffer", &Constants::COLLISION_BUFFER, 0.0001f, 0.00001f, "b = %.9f");
		if (ImGui::Button("toggle fullscreen")) {
			const bool fullscreen = !this->_window.getFullscreen();
			this->_window.setFullscreen(fullscreen);
			SDL_SetWindowFullscreen(&this->_window.getWindow(), fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
		}

		// render
		
		this->_window.render(wilson);
		this->_window.render(testForm);
		this->_window.render(testForm2);

		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
		
		// display
		this->_window.display();
	}
}
