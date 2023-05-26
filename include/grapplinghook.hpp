#pragma once

#include "item.hpp"
#include "player.hpp"
#include "rope.hpp"
#include "renderwindow.hpp"

class GrapplingHook : public Item {
public:
    enum class State
    {
        Idle,
        Extending,
        Retracting
    };
    GrapplingHook(Player& player): Item(player),
    _rope(new Rope(player.getPosition(), 20)),
    _currentState(State::Idle),
    _isGrabbingSurface(false) {}

    ~GrapplingHook() { if (_rope) delete _rope; }

    virtual void use(bool endUse=false);
    virtual void useSecondary(bool endUse=false);
    virtual void update(float deltaTime);
    virtual void renderItem(RenderWindow& renderWindow) { renderWindow.render(*this); }

    Rope& getRope() const { return *_rope; }
    
    State getState() const { return _currentState; }
    void setState(State state) { _currentState = state; }

private:
    Rope* _rope;
    State _currentState;
    float _currentRopeLength;
    bool _isGrabbingSurface;
};
