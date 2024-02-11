#!/usr/bin/env bash
# Alexis Megas.

if [ ! -x /usr/bin/dpkg-deb ]; then
    echo "Please install dpkg-deb."
    exit
fi

if [ ! -x /usr/bin/fakeroot ]; then
    echo "Please install fakeroot."
    exit 1
fi

if [ ! -r badger.pro ]; then
    echo "Please execute $0 from the primary directory."
    exit 1
fi

# Preparing ./opt/badger:

make distclean 2>/dev/null
mkdir -p ./opt/badger
qmake -o Makefile
lupdate badger.pro 2>/dev/null && lrelease badger.pro 2>/dev/null
make -j $(nproc)
cp -p ./NAME ./opt/badger/.
cp -p ./badger.sh ./opt/badger/.
cp -pr ./Images ./opt/badger/.

# Preparing Badger-x.deb:

mkdir -p debian/opt
cp -pr ./Distributions/DEBIAN debian/.
cp -r ./opt/badger debian/opt/.
fakeroot dpkg-deb --build debian badger-2024.02.11_amd64.deb
make distclean
rm -fr ./opt
rm -fr debian
