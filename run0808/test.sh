#! /bin/zsh

cd /home/apricot/Documents/Science/HPGe_Geant4/workdir/HPGeEfficency/build
g++ ./efficency.cpp -o efficency `root-config --cflags --libs`
./efficency
echo 'succeed' ${i}
