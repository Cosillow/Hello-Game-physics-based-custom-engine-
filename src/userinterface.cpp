#include "userinterface.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "constants.hpp"
#include "renderwindow.hpp"
#include "player.hpp"

void UserInterface::displayDebugMenu(RenderWindow& window, Player& player)
{
    ImGui::Checkbox("Debug mode", &Constants::debugMode);
    ImGui::SliderFloat("gravity", &Constants::GRAVITY, 0.0f, 10000.0f, "g = %.3f");
    ImGui::SliderFloat("player speed", &Constants::PLAYER_SPEED, 0.0f, 10000.0f, "s = %.3f");
    ImGui::SliderFloat("max player speed", &Constants::PLAYER_MAX_SPEED, 0.0f, 50.0f, "m = %.3f");
    ImGui::SliderFloat("jump force", &Constants::PLAYER_JUMP, 0.0f, 50.0f, "f = %.3f");
    // ImGui::SliderFloat("friction", &Constants::FRICTION, 0.0f, 50.0f, "f = %.3f");
    ImGui::SliderFloat("collision buffer", &Constants::COLLISION_BUFFER, 0.0001f, 0.00001f, "b = %.9f");
    if (ImGui::Button("toggle fullscreen")) {
        this->_fullscreen = !this->_fullscreen;
        window.setFullscreen(this->_fullscreen);
    }
    if (ImGui::Button(this->_demoWindow ? "hide demo window" : "show demo window"))
    {
        this->_demoWindow = !this->_demoWindow;
    }
    ImGui::Text("Position: (%.2f, %.2f)", player.getPosition().x, player.getPosition().y);
    ImGui::Text("Acceleration: (%.2f, %.2f)", player.getAcceleration().x, player.getAcceleration().y);
    ImGui::Text("Velocity: (%.2f, %.2f)", player.getVelocity().x, player.getVelocity().y);
    ImGui::Text("hitbox bottom: (%.2f)", player.getHitbox()->getBottomY());

    if (this->_demoWindow)
    {
        ImGui::ShowDemoWindow();
    }
}

void UserInterface::newFrame() const
{
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void UserInterface::renderFrame() const
{
	ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}
	