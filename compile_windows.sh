arch="${ARCH:--m64}"
make --no-print-directory ARCH=$arch CC="x86_64-w64-mingw32-g++ -std=c++11" AR="x86_64-w64-mingw32-ar" RANLIB="x86_64-w64-mingw32-ranlib" STRIP="x86_64-w64-mingw32-strip" ADDITIONAL_CFLAGS="-Wl,-subsystem,windows" $@
