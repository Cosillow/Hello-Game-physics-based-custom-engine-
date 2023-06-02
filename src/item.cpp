#include "item.hpp"
#include "player.hpp"

Item::Item(Player& player): Body(player.getPosition()),
_player(player) {};