#!/usr/bin/env sh

NAME=$1
VERSION=$2

if [ -z "$NAME" -o -z "$VERSION" ]; then
    echo "Usage: $0 <NAME> <VERSION>."
    exit 1
fi
