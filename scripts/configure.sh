#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE FACEMC with CMAKE
##---------------------------------------------------------------------------##

EXTRA_ARGS=$@

rm -rf CMakeCache.txt

##---------------------------------------------------------------------------##

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$PWD/../ \
    -D CMAKE_BUILD_TYPE:STRING=DEBUG \
    -D CMAKE_VERBOSE_CONFIGURE:BOOL=ON \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D FACEMC_ENABLE_DBC:BOOL=ON \
    -D TRILINOS_PREFIX:PATH=/home/alex/Software/trilinos \
    -D MOAB_PREFIX:PATH=/home/alex/Software/MOAB \
    -D HDF5_PREFIX:PATH=/home/alex/Software/HDF5 \
    -D BOOST_PREFIX:PATH=/home/alex/Software/boost \
    -D SPRNG_PREFIX:PATH=/home/alex/Software/sprng \
    $EXTRA_ARGS \
    /home/alex/research/transport/FACEMC