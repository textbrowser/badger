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
lupdate badger.pro && lrelease badger.pro
make -j $(nproc)
cp -p ./Badger ./opt/badger/.
cp -p ./badger.sh ./opt/badger/.
cp -pr ./Images ./opt/badger/.

# Preparing Badger-x.deb:

mkdir -p badger-debian/opt
cp -pr ./Distributions/DEBIAN badger-debian/.
cp -r ./opt/badger badger-debian/opt/.
fakeroot dpkg-deb --build badger-debian Badger-2023.11.15_amd64.deb
make distclean
rm -fr ./opt
rm -fr badger-debian
