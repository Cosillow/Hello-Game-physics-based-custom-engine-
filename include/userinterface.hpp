#include "renderwindow.hpp"

class UserInterface {
    private:
        bool _fullscreen;
        bool _demoWindow;
    public:
        UserInterface(): _fullscreen(false), _demoWindow(false) {}
        void displayDebugMenu(RenderWindow& window, Player& Player);
        const void newFrame();
        const void renderFrame();
};