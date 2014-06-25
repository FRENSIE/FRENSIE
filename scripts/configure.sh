#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE FACEMC with CMAKE
##---------------------------------------------------------------------------##

EXTRA_ARGS=$@
TRILINOS_PREFIX_PATH=$HOME/software/trilinos
MOAB_PREFIX_PATH=$HOME/software/moab
HDF5_PREFIX_PATH=$HOME/software/hdf5
ODEPACK_PREFIX_PATH=$HOME/software/odepack
BOOST_PREFIX_PATH=$HOME/software/boost
FACEMC_PATH=$HOME/summer_2014/transmutation/FRENSIE/

##---------------------------------------------------------------------------##
## The Teuchos_TwoDArray class has a bug that needs to be fixed. This patch
## will work as a temporary solution.
patch -s -f $TRILINOS_PREFIX_PATH/include/Teuchos_TwoDArray.hpp \
    $FACEMC_PATH/patches/Teuchos_TwoDArray_patch

##---------------------------------------------------------------------------##

rm -rf CMakeCache.txt

##---------------------------------------------------------------------------##

/home/asb/software/cmake/bin/cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$PWD/../ \
    -D CMAKE_BUILD_TYPE:STRING=DEBUG \
    -D CMAKE_VERBOSE_CONFIGURE:BOOL=ON \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D FRENSIE_ENABLE_DBC:BOOL=ON \
    -D TRILINOS_PREFIX:PATH=$TRILINOS_PREFIX_PATH \
    -D MOAB_PREFIX:PATH=$MOAB_PREFIX_PATH \
    -D HDF5_PREFIX:PATH=$HDF5_PREFIX_PATH \
    -D ODEPACK_PREFIX:PATH=$ODEPACK_PREFIX_PATH \
    -D BOOST_PREFIX:PATH=$BOOST_PREFIX_PATH \
    -D CMAKE_CXX_COMPILER:FILEPATH=/home/asb/software/gcc/bin/c++ \
    -D CMAKE_C_COMPILER:FILEPATH=/home/asb/software/gcc/bin/gcc \
    -D CMAKE_Fortran_COMPILER:FILEPATH=/home/asb/software/gcc/bin/gfortran \
    $EXTRA_ARGS \
    $FACEMC_PATH

 
