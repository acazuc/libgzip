arch="${ARCH:--m64}"
make --no-print-directory ARCH=$arch CC="g++ -std=c++14" AR="gcc-ar" ARFLAGS="--plugin /usr/lib/gcc/x86_64-linux-gnu/6/liblto_plugin.so" RANLIB="gcc-ranlib" RANLIBFLAGS="--plugin /usr/lib/gcc/x86_64-linux-gnu/6/liblto_plugin.so" STRIP="strip" $@
