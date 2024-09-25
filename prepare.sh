#!/usr/bin/env sh
# Alexis Megas.

NAME=$1
VERSION=$2

if [ -z "$NAME" -o -z "$VERSION" ]; then
    echo "Usage: $0 <NAME> <VERSION>."
    exit 1
fi

for FOLDER in Distributions/DEBIAN; do
    sed -i "s/NAME/$NAME/" $FOLDER/control
    sed -i "s/Version: .*/Version: $VERSION/" $FOLDER/control
done

for file in Distributions/build*; do
    sed -i "s/NAME-.*_/$NAME-$VERSION\_/" $file
    sed -i "s/NAME/$NAME/g" $file
done

file=badger.pro

sed -i "s/QMAKE_CLEAN\s*+=\s*NAME/QMAKE_CLEAN += $NAME/" $file
sed -i "s/PROJECTNAME\s*=\s*NAME/PROJECTNAME = $NAME/" $file
sed -i "s/TARGET\s*=\s*NAME/TARGET = $NAME/" $file

file=badger.sh

sed -i "s/\/opt\/NAME\/NAME/\/opt\/$NAME\/$NAME/" $file
sed -i "s/\/tmp\/NAME/\/tmp\/$NAME/" $file
