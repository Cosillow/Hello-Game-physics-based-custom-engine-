# Hello-Game
  Connor's first C++ game

## Building
```sh
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev

# for windows cross compile on linux
sudo apt-get install mingw-w64
sudo apt-get install mingw-w64-tools
# download the mingw version of sdl and sdl-image
# make cross both libraries
# https://github.com/libsdl-org/SDL/releases
# https://github.com/libsdl-org/SDL_image/releases
```

## TODO
* buffer switch for hitbox being touched
  * touchedNext
  * then switch touchNext when it updates probably
  * also try to condense/finilize touchingGround and inCollision
    * and player and hitbox
* friction options
* add zoom functionality to camera
  * and different camerea tracking options (camera types, something)
* VerletBody and EulerBody ?
* level editor
  * undo/redo with (command pattern)
  * tilemap = array of pointers to tile objects (flyweight pattern)
* shared and unique pointers
  * memory leaks?
* input handler (command pattern)
  * return Command* (command interface, having method execute(Player p))
* achievements (observer pattern/event queue)
* audio queues (observer pattern/event queue)

### long (long) term
* openGL?

## Game ideas
* I want only keyboard controls if possible, aiming with mouse is annoying, and its easier to play on a laptop, which should be possible, not intensive
* could have an aim circle that you can switch rotating left and right on player axis
* balloons that make you float up, and enemies can attack them
  * could be linked to life in the game
  * or just be a powerup
* shoot something that you can control with WASD, like a ness attack
