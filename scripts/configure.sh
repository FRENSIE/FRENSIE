#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE FACEMC with CMAKE
##---------------------------------------------------------------------------##

EXTRA_ARGS=$@
TRILINOS_PREFIX_PATH=$HOME/Software/trilinos
MOAB_PREFIX_PATH=$HOME/Software/MOAB
HDF5_PREFIX_PATH=$HOME/Software/HDF5
BOOST_PREFIX_PATH=$HOME/Software/boost
SPRNG_PREFIX_PATH=$HOME/Software/sprng
FACEMC_PATH=$HOME/research/transport/FACEMC/

##---------------------------------------------------------------------------##
## The Teuchos_TwoDArray class has a bug that needs to be fixed. This patch
## will work as a temporary solution.
patch -s -f $TRILINOS_PREFIX_PATH/include/Teuchos_TwoDArray.hpp \
    $FACEMC_PATH/patches/Teuchos_TwoDArray_patch

##---------------------------------------------------------------------------##

rm -rf CMakeCache.txt

##---------------------------------------------------------------------------##

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$PWD/../ \
    -D CMAKE_BUILD_TYPE:STRING=DEBUG \
    -D CMAKE_VERBOSE_CONFIGURE:BOOL=ON \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D FACEMC_ENABLE_DBC:BOOL=ON \
    -D TRILINOS_PREFIX:PATH=$TRILINOS_PREFIX_PATH \
    -D MOAB_PREFIX:PATH=$MOAB_PREFIX_PATH \
    -D HDF5_PREFIX:PATH=$HDF5_PREFIX_PATH \
    -D BOOST_PREFIX:PATH=$BOOST_PREFIX_PATH \
    -D SPRNG_PREFIX:PATH=$SPRNG_PREFIX_PATH \
    $EXTRA_ARGS \
    $FACEMC_PATH