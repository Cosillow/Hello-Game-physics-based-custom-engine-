#include <memory>

#include "renderwindow.hpp"
#include "inputmanager.hpp"


class App
{
public:
    App(RenderWindow& window): _window(window), _inputManager(std::make_shared<InputManager>()) {};
    void run() const;
private:
    RenderWindow& _window;
    std::shared_ptr<InputManager> _inputManager;
};