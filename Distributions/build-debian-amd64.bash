#!/usr/bin/env bash

# Alexis Megas.

if [ ! -x /usr/bin/dpkg-deb ]
then
    echo "Please install dpkg-deb."
    exit 1
fi

if [ ! -x /usr/bin/fakeroot ]
then
    echo "Please install fakeroot."
    exit 1
fi

if [ ! -r glitch.pro ]
then
    echo "Please issue $0 from the primary directory."
    exit 1
fi

# Prepare ./opt/glitch.

make distclean 2>/dev/null
mkdir -p ./opt/glitch/Documentation
qmake -o Makefile glitch.pro
lupdate glitch.pro 2>/dev/null
lrelease glitch.pro 2>/dev/null
make -j $(nproc)
cp -p ./Documentation/*.1 ./opt/glitch/Documentation/.
cp -p ./Glitch ./opt/glitch/.
cp -p ./Icons/Logo/glitch-logo.png ./opt/glitch/.
cp -p ./glitch.sh ./opt/glitch/.
cp -pr ./Documentation/Arduino ./opt/glitch/Documentation/.
cp -pr ./Examples ./opt/glitch/.

# Prepare Glitch-x.deb.

mkdir -p glitch-debian/opt
cp -pr ./Distributions/DEBIAN glitch-debian/.
cp -r ./opt/glitch glitch-debian/opt/.
fakeroot dpkg-deb --build glitch-debian Glitch-2025.05.03_amd64.deb
rm -fr ./opt
rm -fr glitch-debian
make distclean
