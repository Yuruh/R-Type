if [ -f "Makefile" ];then
   make clean;
   rm -f Makefile;
fi

if [ -f "CMakeCache.txt" ];then
    rm -f CMakeCache.txt;
fi

if [ -f "cmake_install.cmake" ];then
    rm -f cmake_install.cmake;
fi

if [ -d "CMakeFiles" ];then
    rm -rf CMakeFiles;
fi
