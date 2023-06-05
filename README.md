# Hello-Game
Alex and Connor's first C++ game


## setup
$
    sudo apt-get install libsdl2-dev
    sudo apt-get install libsdl2-image-dev
    ./buildRun.sh


TODO: make the grappling hook pull the player to the wall with a consistant force over time so that the player can release from the tension when they choose. This means I need to finilize my force system

bool CirclevsCircleOptimized( Circle a, Circle b )
{
  float r = a.radius + b.radius
  r *= r
  return r < (a.x + b.x)^2 + (a.y + b.y)^2
}
