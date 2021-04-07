#!/bin/bash

EXTRA_ARGS=$@

DAGMC_SRC=
DAGMC_INSTALL=

source $HOME/.bashrc

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$DAGMC_INSTALL \
    $EXTRA_ARGS \
    $DAGMC_SRC