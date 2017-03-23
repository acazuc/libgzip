arch="${arch:--m64}"
make --no-print-directory ARCH=$arch CC="g++ -std=c++14" AR="gcc-ar" RANLIB="gcc-ranlib" STRIP="strip" $@
