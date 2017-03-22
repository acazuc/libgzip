#!/bin/bash
arch="${arch:--m64}"
if [[ "$arch" = "-m64" ]]
then
	prefix="x86_64";
else
	prefix="i686";
fi
make --no-print-directory ARCH=$arch CC="$prefix-w64-mingw32-g++ -std=c++11" AR="$prefix-w64-mingw32-gcc-ar" RANLIB="$prefix-w64-mingw32-gcc-ranlib" STRIP="$prefix-w64-mingw32-strip" ADDITIONAL_CFLAGS="-Wl,-subsystem,windows" $@
