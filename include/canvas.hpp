#include "2dphysics.hpp"
#include "resourcemanager.hpp"

class Canvas : public UpdateableI {
private:
    SDL_Texture* _photo;
    SDL_Rect _box;
    SDL_Rect _selection;
    float _zoomPercent;


public:
    Canvas() : _photo(nullptr), _box({0,0,0,0}), _selection({0,0,0,0}), _zoomPercent(100) {}
    ~Canvas() { this->cleanup(); }

    bool setPhoto(const std::string& path) {
        this->cleanup();
        this->_photo = ResourceManager::openTexture(path);
        if (!this->_photo) { this->_photo = nullptr; return false; }
        SDL_QueryTexture(this->_photo, nullptr, nullptr, &_box.w, &_box.h);
        return true;
    }

    void panX(float panX) {
        this->_box.x += panX;
    }

    void panY(float panY) {
        this->_box.y += panY;
    }

    void zoom(float increment) {
        this->_zoomPercent += increment;
    }

    void drawBox(const SDL_Rect& box) {
        this->_selection = box;
    }

    void update(float deltaTime) override { }

    // getters
    int getZoom() const { return this->_zoomPercent; }

    SDL_Texture* getPhoto() const {
        return this->_photo;
    }

    const SDL_Rect& getBox() const {
        return this->_box;
    }

    const SDL_Rect& getSelection() const {
        return _selection;
    }
private:
    void cleanup() { if (this->_photo) SDL_DestroyTexture(this->_photo); }
};