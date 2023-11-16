#!/usr/bin/env sh
# Alexis Megas.

NAME=$1
VERSION=$2

if [ -z "$NAME" -o -z "$VERSION" ]; then
    echo "Usage: $0 <NAME> <VERSION>."
    exit 1
fi

for FOLDER in Distributions/DEBIAN; do
    sed -i "s/Version: .*/Version: $VERSION/" $FOLDER/control
done

for file in Distributions/build*; do
    sed -i "s/$NAME-.*_/$NAME-$VERSION\_/" $file
done

file=badger.pro

sed -i "s/QMAKE_CLEAN += Badger/QMAKE_CLEAN += $NAME/" $file
sed -i "s/PROJECTNAME = Badger/PROJECTNAME = $NAME/" $file
sed -i "s/TARGET = Badger/TARGET = $NAME/" $file
