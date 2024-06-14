#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra"
LIBS="-lraylib"

gcc $CFLAGS -o haaragame main.c $LIBS
