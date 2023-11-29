progname="tothetop"
linkflags="-lSDL2"
compflags="-Wall -Wextra -pedantic"

outdir="../../out/"

src="../../src/main.cpp\
     ../../src/player/player.cpp\
     ../../src/input/input.cpp\
     ../../src/game/game.cpp"

g++ -o $outdir$progname $src $compflags $linkflags
