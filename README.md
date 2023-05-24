# Hello-Game
Alex and Connor's first C++ game


## setup
$
    sudo apt-get install libsdl2-dev
    sudo apt-get install libsdl2-image-dev
    ./buildRun.sh



bool CirclevsCircleOptimized( Circle a, Circle b )
{
  float r = a.radius + b.radius
  r *= r
  return r < (a.x + b.x)^2 + (a.y + b.y)^2
}