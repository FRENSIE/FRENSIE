#!/bin/bash

EXTRA_ARGS=$@

ROOT_SRC=/home/software/root/src
ROOT_INSTALL=/home/software/root


source $HOME/.bashrc

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$ROOT_INSTALL \
    -D CMAKE_BUILD_TYPE:STRING=RELEASE \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D fail-on-missing:BOOL=ON \
    -D all:BOOL=ON \
    -D testing:BOOL=ON \
    -D roottest:BOOL=OFF \
    -D rfio:BOOL=OFF \
    -D oracle:BOOL=OFF \
    -D odbc:BOOL=OFF \
    -D pythia6:BOOL=OFF \
    -D pythia8:BOOL=OFF \
    -D gfal:BOOL=OFF \
    -D chirp:BOOL=OFF \
    -D hdfs:BOOL=OFF \
    -D mathmore:BOOL=OFF \
    $EXTRA_ARGS \
    $ROOT_SRC
