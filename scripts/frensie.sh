#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE FACEMC with CMAKE
##---------------------------------------------------------------------------##

EXTRA_ARGS=$@
TRILINOS_PREFIX_PATH=$(pwd)/../deps/install/trilinos
TRILINOS_SOURCE_PATH=$(pwd)/../deps/builds/trilinos
HDF5_PREFIX_PATH=$(pwd)/../deps/install/hdf5
MOAB_PREFIX_PATH=$(pwd)/../deps/install/moab
ODEPACK_PREFIX_PATH=$(pwd)/../deps/install/odepack
BOOST_PREFIX_PATH=$(pwd)/../deps/install/boost
GSL_PREFIX_PATH=$(pwd)/../deps/install/gsl
MPI_PREFIX_PATH=$(pwd)/../deps/install/mpi
DOXYGEN_PREFIX_PATH=$(pwd)/../deps/install/doxygen
FRENSIE_SRC=$(pwd)/../src
FRENSIE_INSTALL=$(pwd)/../frensie_install

##---------------------------------------------------------------------------##
## The Teuchos_TwoDArray class has a bug that needs to be fixed. This patch
## will work as a temporary solution.
patch -s -f $TRILINOS_PREFIX_PATH/include/Teuchos_TwoDArray.hpp \
   $FRENSIE_SRC/patches/Teuchos_TwoDArray_patch

source ~/.bashrc
source `python ../src/scripts/prefix.py ../deps/install`

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$FRENSIE_INSTALL \
    -D CMAKE_BUILD_TYPE:STRING=RELEASE \
    -D CMAKE_VERBOSE_CONFIGURE:BOOL=OFF \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D FRENSIE_ENABLE_DBC:BOOL=ON \
    -D FRENSIE_ENABLE_OPENMP:BOOL=ON \
    -D FRENSIE_ENABLE_MPI:BOOL=ON \
    -D FRENSIE_ENABLE_DAGMC:BOOL=OFF \
    -D TRILINOS_PREFIX:PATH=$TRILINOS_PREFIX_PATH \
    -D TRILINOS_SOURCE:PATH=$TRILINOS_SOURCE_PATH \
    -D MOAB_PREFIX:PATH=$MOAB_PREFIX_PATH \
    -D HDF5_PREFIX:PATH=$HDF5_PREFIX_PATH \
    -D ODEPACK_PREFIX:PATH=$ODEPACK_PREFIX_PATH \
    -D BOOST_PREFIX:PATH=$BOOST_PREFIX_PATH \
    -D GSL_PREFIX:PATH=$GSL_PREFIX_PATH \
    -D MPI_PREFIX:PATH=$MPI_PREFIX_PATH \
    -D DOXYGEN_PREFIX:PATH=$DOXYGEN_PREFIX_PATH \
    $EXTRA_ARGS \
    $FRENSIE_SRC

 
