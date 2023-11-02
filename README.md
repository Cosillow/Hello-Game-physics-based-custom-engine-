# Hello-Game
  Connor's first C++ game

## setup
  sudo apt-get install libsdl2-dev
  sudo apt-get install libsdl2-image-dev
  ./buildRun.sh

## TODO
* look at hitbox, make it not update every time?
* make oldposition and newposition protected
  * api following that
* figure out edges of platforms
* level editor
  * undo/redo with (command pattern)
  * tilemap = array of pointers to tile objects (flyweight pattern)
* shared and unique pointers
  * memory leaks?
* input handler (command pattern)
  * return Command* (command interface, having method execute(Player p))

### long (long) term
* openGL?

## game ideas
* I want only keyboard controls if possible, aiming with mouse is annoying, and its easier to play on a laptop, which should be possible, not intensive
* could have an aim circle that you can switch rotating left and right on player axis
*  