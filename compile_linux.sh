arch="${ARCH:--m64}"
make --no-print-directory ARCH=$arch CC="g++ -std=c++14" AR="ar" RANLIB="ranlib" STRIP="strip" $@
