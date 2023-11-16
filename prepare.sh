#!/usr/bin/env sh

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
