#!/bin/sh

if [ -n "$1" ]; then
  echo "Creating project in $0"
else
  echo "Usage: $0 <path to project> (or .)"
  exit 1
fi

if test -f "$1/Makefile"; then
    echo "Project has already been initialized"
    exit 1
fi

BASEDIR=$(dirname $0)
cp $BASEDIR/Makefile $1
mkdir -p $1/inc
mkdir -p $1/src
