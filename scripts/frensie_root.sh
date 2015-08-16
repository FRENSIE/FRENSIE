#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE FACEMC with CMAKE
##---------------------------------------------------------------------------##

# Export a python script to convert relative paths to absoulte paths.
# Delete this python script before this bash script exits
ABSPATHEXE="__abspath.py"
echo "import os; import sys; sys.stdout.write(os.path.abspath(sys.argv[1]))" > $ABSPATHEXE

EXTRA_ARGS=$@
TRILINOS_PREFIX_PATH=/home/software/trilinos
TRILINOS_SOURCE_PATH=/home/software/trilinos/src
HDF5_PREFIX_PATH=/home/software/hdf5
MOAB_PREFIX_PATH=/home/software/moab
MOAB_SOURCE_PATH=/home/software/moab/src
ODEPACK_PREFIX_PATH=/home/software/odepack
BOOST_PREFIX_PATH=/home/software/boost
GSL_PREFIX_PATH=/home/software/gsl
MPI_PREFIX_PATH=/home/software/mpi
ROOT_PREFIX_PATH=/home/software/root
DOXYGEN_PREFIX_PATH=
FRENSIE_SRC=/home/ecmoll/frensie/root/FRENSIE
FRENSIE_INSTALL=/home/ecmoll/frensie/root/build

# No longer needed after this point.
# Move lower if $ABSPATHEXE needs to be used below this.
rm "__abspath.py"

source ~/.bashrc
`python ../FRENSIE/scripts/prefix.py ../deps/install`

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$FRENSIE_INSTALL \
    -D CMAKE_BUILD_TYPE:STRING=RELEASE \
    -D CMAKE_VERBOSE_CONFIGURE:BOOL=OFF \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D FRENSIE_ENABLE_DBC:BOOL=ON \
    -D FRENSIE_ENABLE_OPENMP:BOOL=ON \
    -D FRENSIE_ENABLE_MPI:BOOL=ON \
    -D FRENSIE_ENABLE_DAGMC:BOOL=ON \
    -D FRENSIE_ENABLE_ROOT:BOOL=ON \
    -D FRENSIE_ENABLE_PROFILING:BOOL=OFF \
    -D FRENSIE_ENABLE_COVERAGE:BOOL=OFF \
    -D TRILINOS_PREFIX:PATH=$TRILINOS_PREFIX_PATH \
    -D TRILINOS_SOURCE:PATH=$TRILINOS_SOURCE_PATH \
    -D ROOT_PREFIX:PATH=$ROOT_PREFIX_PATH \
    -D MOAB_PREFIX:PATH=$MOAB_PREFIX_PATH \
    -D MOAB_SOURCE:PATH=$MOAB_SOURCE_PATH \
    -D HDF5_PREFIX:PATH=$HDF5_PREFIX_PATH \
    -D ODEPACK_PREFIX:PATH=$ODEPACK_PREFIX_PATH \
    -D BOOST_PREFIX:PATH=$BOOST_PREFIX_PATH \
    -D GSL_PREFIX:PATH=$GSL_PREFIX_PATH \
    -D MPI_PREFIX:PATH=$MPI_PREFIX_PATH \
    -D DOXYGEN_PREFIX:PATH=$DOXYGEN_PREFIX_PATH \
    -D MCNP_DATA_DIR:PATH=/home/software/mcnpdata \
    -D SETUP_DASHBOARD_CLIENT:BOOL=OFF \
    $EXTRA_ARGS \
    $FRENSIE_SRC

 
