#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE FACEMC with CMAKE
##---------------------------------------------------------------------------##

EXTRA_ARGS=$@
TRILINOS_PREFIX_PATH=$HOME/trilinos-path
HDF5_PREFIX_PATH=$HOME/hdf5-path
MOAB_PREFIX_PATH=$HOME/moab-path
ODEPACK_PREFIX_PATH=$HOME/odepack-path
BOOST_PREFIX_PATH=$HOME/boost-path
GSL_PREFIX_PATH=$HOME/gsl-path
MPI_PREFIX_PATH=$HOME/mpi-path
DOXYGEN_PREFIX_PATH=$HOME/doxygen-path
FRENSIE_PREFIX_PATH=$HOME/frensie-path

##---------------------------------------------------------------------------##
## The Teuchos_TwoDArray class has a bug that needs to be fixed. This patch
## will work as a temporary solution.
patch -s -f $TRILINOS_PREFIX_PATH/include/Teuchos_TwoDArray.hpp \
   $FRENSIE_PREFIX_PATH/src/patches/Teuchos_TwoDArray_patch

source ~/.bashrc

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$FRENSIE_PREFIX_PATH \
    -D CMAKE_BUILD_TYPE:STRING=RELEASE \
    -D CMAKE_VERBOSE_CONFIGURE:BOOL=OFF \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D FRENSIE_ENABLE_DBC:BOOL=ON \
    -D FRENSIE_ENABLE_OPENMP:BOOL=ON \
    -D FRENSIE_ENABLE_MPI:BOOL=ON \
    -D FRENSIE_ENABLE_DAGMC:BOOL=OFF \
    -D TRILINOS_PREFIX:PATH=$TRILINOS_PREFIX_PATH \
    -D MOAB_PREFIX:PATH=$MOAB_PREFIX_PATH \
    -D HDF5_PREFIX:PATH=$HDF5_PREFIX_PATH \
    -D ODEPACK_PREFIX:PATH=$ODEPACK_PREFIX_PATH \
    -D BOOST_PREFIX:PATH=$BOOST_PREFIX_PATH \
    -D GSL_PREFIX:PATH=$GSL_PREFIX_PATH \
    -D MPI_PREFIX:PATH=$MPI_PREFIX_PATH \
    -D DOXYGEN_PREFIX:PATH=$DOXYGEN_PREFIX_PATH \
    $EXTRA_ARGS \
    $FRENSIE_PREFIX_PATH/src

 
