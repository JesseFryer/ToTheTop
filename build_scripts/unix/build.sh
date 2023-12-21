
progname="ToTheTop"
linkflags="-lSDL2"
compflags="-Wall -Wextra -pedantic -std=c++11"

outdir="../../out/"

src="../../src/main.cpp\
     ../../src/input/input.cpp\
     ../../src/app/app.cpp\
     ../../src/scene/scene.cpp\
     ../../src/components/components.cpp\
     ../../src/entities/entities.cpp\
     ../../src/game/systems.cpp"

mkdir $outdir > /dev/null 2> /dev/null
g++ -o $outdir$progname $src $compflags $linkflags
