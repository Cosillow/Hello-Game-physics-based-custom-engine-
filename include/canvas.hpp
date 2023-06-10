#include "2dphysics.hpp"
#include "resourcemanager.hpp"

class Canvas : public UpdateableI {
private:
    SDL_Texture* _photo;
    SDL_Rect _box;
    std::pair<Vector2, Vector2> _selection;
    bool _isSelecting;
    float _zoomPercent;

public:
    Canvas() : _photo(nullptr), _box({0,0,0,0}), _selection(std::make_pair(Vector2(0,0), Vector2(0,0))), _isSelecting(false), _zoomPercent(100) {}
    ~Canvas() { this->cleanup(); }

    bool setPhoto(const std::string& path) {
        this->cleanup();
        this->_photo = ResourceManager::openTexture(path);
        if (!this->_photo) { this->_photo = nullptr; return false; }
        SDL_QueryTexture(this->_photo, nullptr, nullptr, &this->_box.w, &this->_box.h);

        // Calculate the zoom factor to fit the photo width to the screen width minus padding
        int padding = 20;  // Adjust the padding value as desired
        float zoomFactor = (Constants::WINDOW_WIDTH - padding) / static_cast<float>(this->_box.w);

        // Set the box size and position
        _box.w = static_cast<int>(this->_box.w * zoomFactor);
        _box.h = static_cast<int>(this->_box.h * zoomFactor);
        _box.x = 0;
        _box.y = 0;
        return true;
    }

    void panX(float panX) {
        this->_box.x += panX;
    }

    void panY(float panY) {
        this->_box.y += panY;
    }

    void zoom(float increment) {
        // adjustment factor based on the current zoom percentage
        float adjustment = _zoomPercent / 100.0f;
        _zoomPercent += increment * adjustment;
    }

    void drawBox(Vector2 screenPosition) {
        Vector2 canvasPosition = getSpriteOffset(screenPosition);
        if (this->_isSelecting) {
            // still drawing
            this->_selection.second = screenPosition;
        } else {
            // just started drawing
            this->_isSelecting = true;
            this->_selection.first = screenPosition;
            this->_selection.second = screenPosition;
        }
    }

    void completeBox(Vector2 position) {
        if (!this->_isSelecting) return;
        this->_isSelecting = false;
        // TODO: splicing logic
    }

    void update(float deltaTime) override { }

    // getters
    bool isSelecting() const { return this->_isSelecting; }

    int getZoom() const { return this->_zoomPercent; }

    SDL_Texture* getPhoto() const {
        return this->_photo;
    }

    const SDL_Rect& getBox() const {
        return this->_box;
    }

    const SDL_Rect getSelection() const {
        int offsetX = _box.x;
        int offsetY = _box.y;

        const float zoomFactor = this->_zoomPercent / 100;

        SDL_Rect selectionRect;
        selectionRect.x = static_cast<int>((std::min(this->_selection.first.x, this->_selection.second.x) - offsetX));
        selectionRect.y = static_cast<int>((std::min(this->_selection.first.y, this->_selection.second.y) - offsetY));
        selectionRect.w = static_cast<int>(std::abs(this->_selection.second.x - this->_selection.first.x) * zoomFactor);
        selectionRect.h = static_cast<int>(std::abs(this->_selection.second.y - this->_selection.first.y) * zoomFactor);
        return selectionRect;
    }

private:
    void cleanup() { if (this->_photo) SDL_DestroyTexture(this->_photo); }
    Vector2 getSpriteOffset(Vector2 screenPosition) const {
        // Calculate the offset based on the zoom percentage
        const float zoomFactor = this->_zoomPercent / 100;
        int offsetX = static_cast<int>(std::abs(this->_box.x - screenPosition.x) * zoomFactor);
        int offsetY = static_cast<int>(std::abs(this->_box.y - screenPosition.y) * zoomFactor);

        return Vector2(offsetX, offsetY);
    }
};
