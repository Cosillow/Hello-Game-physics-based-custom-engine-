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
* lock down a resolution and sprite size
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
* shoot something that you can control with WASD, like a ness attack
* balloon game where you float upwards, avoiding clouds, maybe enemies
 * if you hit a cloud, a balloon pops and you slow down for a bit
 * if you hit a cloud you lose a life/balloon
 * different balloon powerups
* camera will center player in the bottom center of the screen (hard y) and slow catching up x
* some incentive to go faster?
  * does less balloons mean you float slower?
* shop, with a hand that grabs you out of the air
* rainbows?
  * pot of gold
* dynamic weather?
  * wind gusts
  * rain
  * lightning
    * how would this work? clouds are already dangerous... unless clouds are safe and only dangerous if there is lightning
* day night cycle
* enemies
  * birds
  * sky pirates
  * harpies
  * drones
  * airplane
  * blimp
  * cloud mimics
  * crying cloud
  * sky diver
    * sky dive teams making formation
  * helicopter

### Story
* Balloon Cult!!

* player stumbles upon charismatic balloon guy
* introduces you to balloon society
* higher lvl balloon members have access to better things (maybe they run the shops)
* offers you special balloons to use
  * these balloons were taken from the special place above where the player is trying to go
  *  