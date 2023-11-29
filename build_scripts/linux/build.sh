progname="ToTheTop"
linkflags="-lSDL2"
compflags="-Wall -Wextra -pedantic"

outdir="../../out/"

src="../../src/main.cpp\
     ../../src/input/input.cpp\
     ../../src/game/game.cpp"

mkdir $outdir
g++ -o $outdir$progname $src $compflags $linkflags
