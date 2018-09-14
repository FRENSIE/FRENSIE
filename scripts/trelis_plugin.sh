#!/bin/bash

EXTRA_ARGS=$@

PLUGIN_SRC=
TRELIS_PREFIX=
MOAB_PREFIX=
DAGMC_PREFIX=

source $HOME/.bashrc

cmake --version

# Configure the trelis plugin
cmake \
    -D CMAKE_PREFIX_PATH=${TRELIS_PREFIX}/bin \
    -D MOAB_DIR=${MOAB_PREFIX}/lib \
    -D DAGMC_DIR=${DAGMC_PREFIX} \
    $EXTRA_ARGS \
    $PLUGIN_SRC

# Make plugin
make

# Copy plugin into trelis bin directory
cp ./libsvalinn_plugin.so ${TRELIS_PREFIX}/bin/
