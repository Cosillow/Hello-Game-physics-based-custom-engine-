#include <iostream>
#include "grapplinghook.hpp"
#include "constants.hpp"

void GrapplingHook::update(float deltaTime) {
    if (this->_currentState != GrapplingHook::State::Idle)
    {
        // animate the rope
        this->Body::applyForce(Constants::GRAVITY);
    }

    else if (this->_currentState == GrapplingHook::State::Retracting)
    {
        if (this->_isGrabbingSurface)
        {
            // pull player towards surface while rope retracts
        } else
        {
            // pull grappling hook towards player while rope retracts
        }
    }
    else if (this->_currentState == GrapplingHook::State::Extending)
    {

    }
    else if (this->_currentState == GrapplingHook::State::Idle) 
    {
        Body::setPosition(this->_player.getPosition());
    }

    Body::update(deltaTime);
}

void GrapplingHook::use(bool endUse)
{
    if (!endUse && !this->_isGrabbingSurface && this->_currentState == GrapplingHook::State::Idle)
    {
        
        // shoot grappling hook
        setState(GrapplingHook::State::Extending);

        
        float angleRadians = this->_player.getLookAngle() * (M_PI / 180.0f);
        float ratio = std::tan(angleRadians);

        float run = std::sqrt((Constants::GRAPPLING_HOOK_SPEED * Constants::GRAPPLING_HOOK_SPEED) / (1.0f + (ratio * ratio)));
        float rise = ratio * run;

        Body::applyImpulse({run, rise});

        std::cout << "shooting grappling hook: (" << run << ", " << rise << ")" << std::endl;
    } else if (endUse) {
        // retract grappling hook
        setState(GrapplingHook::State::Retracting);

    }
}

void GrapplingHook::useSecondary(bool endUse)
{
    // release hook from the wall
    if (this->_isGrabbingSurface && this->_currentState == GrapplingHook::State::Idle) {
        this->_isGrabbingSurface = false;
        this->_player.setState(Player::State::FreeFall);
    }
}
