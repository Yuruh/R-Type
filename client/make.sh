#./cleanCMake.sh;
cd ../shared;
./make.sh;
cd -;
cmake -DCMAKE_BUILD_TYPE=Debug .;
make;
