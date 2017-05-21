clear
rm -r build/
mkdir build && cd build
cmake ..
make
cp $OCTOPUS/vmware .
