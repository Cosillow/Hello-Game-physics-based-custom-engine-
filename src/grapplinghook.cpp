#include <iostream>
#include "grapplinghook.hpp"
#include "constants.hpp"

void GrapplingHook::update(float deltaTime) {
    if (_currentState != GrapplingHook::State::Idle)
    {
        // animate the rope
        this->_rope->setAnchorPoints(this->_player.getPosition(), GrapplingHook::Entity::getPosition());
        std::cout << "anchor points: (" << this->_rope->getEndAnchor().x << ", " << this->_rope->getEndAnchor().y << ") | (" << this->_rope->getStartAnchor().x << ", " << this->_rope->getStartAnchor().y << ")" << std::endl;
    }

    else if (_currentState == GrapplingHook::State::Retracting)
    {
        if (this->_isGrabbingSurface)
        {
            // pull player towards surface while rope retracts
        } else
        {
            // pull grappling hook towards player while rope retracts
        }
    }
    else if (_currentState == GrapplingHook::State::Extending)
    {

    }
    else if (_currentState == GrapplingHook::State::Idle) 
    {
        Entity::setPosition(this->_player.getBoundingBoxCenter());
    }

    Entity::update(deltaTime);
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



        Entity::addForce(Entity::ForceType::Gravity);
        Entity::applyImpulse({run, rise});

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
