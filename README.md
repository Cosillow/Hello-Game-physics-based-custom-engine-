# Hello-Game
  Connor's first C++ game

## Building
```sh
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev

# for windows cross compile
sudo apt-get install mingw-w64
sudo apt-get install mingw-w64-tools

# build libraries statically for the cross compile
# first download the source
# then cd into root and run the script
# installed locally: /usr/local/win64/
PREFIX=/usr/local/win64
TOOLSET=x86_64-w64-mingw32
CROSSPATH=$PREFIX/$TOOLSET
# https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5
mkdir build && cd build
export CC="$TOOLSET-gcc -static-libgcc"
../configure --target=$TOOLSET --host=$TOOLSET --build=x86_64-linux --prefix=$CROSSPATH
make -j && sudo make install
# https://zlib.net/

```

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
* achievements (observer pattern/event queue)
* audio queues (observer pattern/event queue)

### long (long) term
* openGL?

## Game ideas
* I want only keyboard controls if possible, aiming with mouse is annoying, and its easier to play on a laptop, which should be possible, not intensive
* could have an aim circle that you can switch rotating left and right on player axis
