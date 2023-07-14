#! /bin/zsh
for ((i=10; i<=1000; i+=10)); do
    cd /home/apricot/Documents/Science/HPGe_Geant4/workdir/${i}egr/build
    rm CMakeCache.txt
    rm log*
    cmake ..
    make
    ./exampleB1 runuser2.mac > log${i}.txt
    cp log${i}.txt ../../log/
    echo 'succeed' ${i}
done
