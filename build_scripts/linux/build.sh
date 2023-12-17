progname="ToTheTop"
linkflags="-lSDL2"
compflags="-Wall -Wextra -pedantic -std=c++11"

outdir="../../out/"

src="../../src/main.cpp\
     ../../src/input/input.cpp\
     ../../src/game/game.cpp\
     ../../src/ecs/scene.cpp"

mkdir $outdir
g++ -o $outdir$progname $src $compflags $linkflags
