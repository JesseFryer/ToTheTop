progname=tothetop
linkflags=-lSDL2

outdir="../../out/"

src="../../src/main.cpp\
     ../../src/player/player.cpp\
     ../../src/input/input.cpp\
     ../../src/game/game.cpp"

g++ -o $outdir$progname $src $linkflags
