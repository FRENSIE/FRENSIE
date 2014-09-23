Installation {#installation}
=====

## Dependencies 
To promote rapid scientific software development and research, FRENSIE is built
off of a large number of software libraries. The software that FRENSIE
depends on is listed below.

1. [HDF5 1.8.13](http://www.hdfgroup.org/HDF5)
2. [OpenMPI 1.8.2](http://www.open-mpi.org/)
3. [Cubit 14.0](https://cubit.sandia.gov/index.html) - optional
4. [CGM 14.1pre](http://trac.mcs.anl.gov/projects/ITAPS/wiki/CGM) - only with Cubit
5. [MOAB 4.6.3](http://trac.mcs.anl.gov/projects/ITAPS/wiki/MOAB)
6. [LAPACK 3.5.0](http://www.netlib.org/lapack/)
7. [Trilinos 11.10.2](http://trilinos.org/)
8. [ODEPACK](http://computation.llnl.gov/casc/odepack/)
9. [Boost 1.56.0](http://www.boost.org/)
10. [GSL 1.16](http://www.gnu.org/software/gsl/)
11. [Doxygen 1.8.8](http://www.stack.nl/~dimitri/doxygen/index.html)

FRENSIE also requires a GNU compiler (4.7.3 or greater) and CMake version 3.0.1 to build correctly. Doxygen version 1.8.8 is recommended but version 1.8.2 and above will also work. All of the above software libraries will be built from source. This process will be described in the next section.

## Building Dependent Software Libraries
Before any of the software libraries are built, verify that the system has CMake version 3.0.1 installed. If CMake is not installed or an older version is present, build CMake 3.0.1 using the instructions below.

When building software libraries and executables, the following directory structure should be adopted: software/package/package.xx.xx.xx, software/package/build, software/package/src. "package" will be the name of the particular software package. "package.xx.xx.xx" comes from unpacking the compressed source files (e.g. package.tar.gz). The src directory is created by making a softlink to the package.xx.xx.xx directory. This is done to make the build a bit easier.

Please note that the software libraries should be built in the order that they
are described.

### Checking out FRENSIE
1. create a working directory where FRENSIE will be built (e.g. software/frensie)
2. move to the frensie directory
3. run `git clone git@github.com:aprobinson/FRENSIE.git`
4. run `ln -s FRENSIE src`

### Building CMake
1. download the [CMake 3.0.1 source](http://www.cmake.org/cmake/resources/software.html)
2. move the cmake-3.0.1.tar.gz file to the cmake directory (e.g. software/cmake)
3. move to the cmake directory
4. run `tar -xvf cmake-3.0.1.tar.gz`
5. run `ln -s cmake-3.0.1 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/cmake/build)
8. run `../src/configure --prefix=absolute-path-to_software/cmake`
9. run `make -j n`, where n is the number of threads to use while building
10. run `make test`
11. run `make install`
12. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/cmake/bin:$PATH`
13. run `exec bash`
14. run `cmake --version` and verify that the output is 3.0.1

### Building HDF5
1. download the [HDF5 1.8.13 source](http://www.hdfgroup.org/HDF5/release/obtainsrc.html)
2. move the hdf5-1.8.13.tar.gz file to the hdf5 directory (e.g. software/hdf5)
3. move to the hdf5 directory
4. run `tar -xvf hdf5-1.8.13.tar.gz`
5. run `ln -s hdf5-1.8.13 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/hdf5/build)
8. copy `FRENSIE/scripts/hdf5.sh` into the build directory
9. change the variables in the script to reflect the desired system paths
10. run `./hdf5.sh` to configure hdf5
11. run `make -j n`
12. run `make test`
13. run `make install`
14. update the `export PATH` line in the .bashrc file: `export PATH=absolute-path-to_software/cmake/bin:absolute-path-to_software/hdf5/bin:$PATH`
15. run `exec bash`

### Building Open MPI
1. download the [Open MPI 1.8.2 source](http://www.open-mpi.org/software/ompi/v1.8/)
2. move the openmpi-1.8.2.tar.gz file to the mpi directory (e.g. software/mpi)
3. move to the mpi directory
4. run `tar -xvf openmpi-1.8.2.tar.gz`
5. run `ln -s openmpi-1.8.2 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/mpi/build)
8. run `../src/configure --prefix=absolute-path-to_software/mpi`
9. run `make -j n`
10. run `make check`
11. run `make install`
12. update the `export PATH` line in the .bashrc file: `export PATH=absolute-path-to_software/cmake/bin:absolute-path-to_software/hdf5/bin:absolute-path-to_software/mpi/bin:$PATH`
13. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/mpi/lib:$LD_LIBRARY_PATH`
14. run `exec bash`

### Building Cubit - Optional
1. Cubit is not open source software so a [license](https://cubit.sandia.gov/public/licensing.html) must be acquired.
2. The binary files will be be available for download once a license has been acquired
3. move the Cubit-14.0-Lin64.tar.gz file to the cubit14.0 directory (e.g. software/cubit14.0)
4. run `tar -xvf Cubit-14.0-Lin64.tar.gz`
5. update the `export PATH` line in the .bashrc file: `export PATH=absolute-path-to_software/cmake/bin:absolute-path-to_software/hdf5/bin:absolute-path-to_software/mpi/bin:absolute-path-to_software/cubit14.0:$PATH`
6. update the `export LD_LIBRARY_PATH` line in the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/mpi/lib:absolute-path-to_software/cubit14.0/bin:$LD_LIBRARY_PATH`
7. run `exec bash`

### Building CGM - Only with Cubit
1. download the [CGM 14.1pre source](http://ftp.mcs.anl.gov/pub/fathom/cgm-nightly-trunk.tar.gz)
2. move the cgm-nightly-trunk.tar.gz file to the cgm directory (e.g. software/cgm)
3. move to the cgm directory
4. run `tar -xvf cgm-nightly-trunk.tar.gz`
5. run `ln -s cgma-14.1pre src`
6. run `mkdir build`
7. move to the build directory (e.g. software/cgm/build)
8. run `../src/configure --enable-optimize --disable-debug --with-cubit=absolute-path-to_software/cubit14.0 --prefix=absolute-path-to_software/cgm`
9. run `make -j n`
10. run `make check`
11. run `make install`

### Building MOAB 
1. download the [MOAB 4.6.3 source](http://ftp.mcs.anl.gov/pub/fathom/moab-4.6.3.tar.gz)
2. move the moab-4.6.3.tar.gz file to the moab directory (e.g. software/moab)
3. move to the moab directory
4. run `tar -xvf moab-4.6.3.tar.gz`
5. run `ln -s moab-4.6.3 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/moab/build)
8. if DagMC is desired (Cubit 14.0 and CGM must be built): 
   * run `../src/configure --enable-optimize --disable-debug --with-cgm=absolute-path-to_software/cgm/ --with-hdf5=absolute-path-to_software/hdf5 --prefix=absolute-path-to_software/moab/`
   * else run `../src/configure --enable-optimize --disable-debug --with-hdf5=absolute-path-to_software/hdf5 --prefix=absolute-path-to_software/moab/`
9. run `make -j n`
10. run `make check`
11. run `make install`
12. update the `export PATH` line in the .bashrc file: `export PATH=absolute-path-to_software/cmake/bin:absolute-path-to_software/hdf5/bin:absolute-path-to_software/mpi/bin:absolute-path-to_software/cubit14.0:absolute-path-to_software/moab/bin:$PATH`
13. run `exec bash`

### Building LAPACK
1. download the [LAPACK 3.5.0 source](http://www.netlib.org/lapack/lapack-3.5.0.tgz)
2. move the lapack-3.5.0.tgz file to the lapack directory (e.g. software/lapack)
3. move to the lapack directory
4. run `tar -xvf lapack-3.5.0.tgz`
5. run `ln -s lapack-3.5.0 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/lapack/build)
8. copy `FRENSIE/scripts/lapack.sh` into the build directory
9. change the variables in the script to reflect the desired system paths
10. run `./lapack.sh` to configure lapack
11. run `make -j n`
12. run `make test`
13. run `make install`
14. update the `export LD_LIBRARY_PATH` line in the .bashrc file: ``export LD_LIBRARY_PATH=absolute-path-to_software/mpi/lib:absolute-path-to_software/cubit14.0/bin:absolute-path-to_software/lapack/lib:$LD_LIBRARY_PATH`
15. run `exec bash`

### Building Trilinos 
1. download the [Trilinos 11.10.2 source](http://trilinos.org/download/)
2. move the trilinos-11.10.2-Source.tar.gz file to the trilinos directory (e.g. software/trilinos)
3. move to the trilinos directory
4. run `tar -xvf trilinos-11.10.2-Source.tar.gz`
5. run `ln -s trilinos-11.10.2.Source src`
6. run `mkdir build`
7. move to the build directory (e.g. software/trilinos/build)
8. copy `FRENSIE/scripts/trilinos.sh` into the build directory 
9. change the variables in the script to reflect the desired system paths
10. run `./trilinos.sh` to configure trilinos
11. run `make -j n`
12. run `make test`
13. run `make install`
14. update the `export LD_LIBRARY_PATH` line in the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/mpi/lib:absolute-path-to_software/cubit14.0/bin:absolute-path-to_software/lapack/lib:absolute-path-to_software/trilinos/lib:$LD_LIBRARY_PATH`
15. run `exec bash`

### Building ODEPACK
1. download the [ODEPACK source](http://computation.llnl.gov/casc/odepack/download/opkd_agree.html)
 * odkd-sum.txt
 * opkdmain.f
 * opkda1.f
 * opkda2.f
 * opkddemos.txt
2. move the above files to the odepack directory (e.g. software/odepack)
3. copy `FRENSIE/scripts/odepack.sh` into the odepack directory
4. run `./odepack.sh` to build libodepack.a

### Building Boost
1. download the [Boost 1.56.0 source](http://sourceforge.net/projects/boost/files/boost/1.56.0/)
2. move the boost_1_56_0.tar.gz file to the boost directory (e.g. software/boost)
3. move to the boost directory
4. run `tar -xvf boost_1_56_0.tar.gz`
5. move to the boost_1_56_0 directory (e.g. software/boost/boost_1_56_0)
6. run `./bootstrap.sh --prefix=absolute-path-to_software/boost`
7. run `./b2`
8. run `./b2 install`
9. update the `export LD_LIBRARY_PATH` line in the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/mpi/lib:absolute-path-to_software/cubit14.0/bin:absolute-path-to_software/lapack/lib:absolute-path-to_software/trilinos/lib:absolute-path-to_software/boost/lib:$LD_LIBRARY_PATH`
10. run `exec bash`

### Building the GNU Scientific Library (GSL)
1. download the [GSL 1.16 source](http://www.gnu.org/software/gsl/)
2. move the `gsl-1.16.tar.gz` file to the gsl directory (e.g. software/gsl)
3. move to the gsl directory
4. run `tar -xvf gsl-1.16.tar.gz`
5. run `ln -s gsl-1.16 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/gsl/build)
8. run `../src/configure --prefix=absolute-path-to_software/gsl`
9. run `make -j n`
10. run `make check`
11. run `make install`
12. update the `export LD_LIBRARY_PATH` line in the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/mpi/lib:absolute-path-to_software/cubit14.0/bin:absolute-path-to_software/lapack/lib:absolute-path-to_software/trilinos/lib:absolute-path-to_software/boost/lib:absolute-path-to_software/gsl/bin:$LD_LIBRARY_PATH`
13. run `exec bash`

### Building Doxygen
1. download the [Doxygen 1.8.8 source](http://sourceforge.net/projects/doxygen/files/)
2. move the `doxygen-1.8.8.src.tar.gz` file to the doxygen directory (e.g. software/gsl)
3. move to the doxygen directory
4. run `tar -xvf doxygen-1.8.8.src.tar.gz`
5. move to the doxygen-1.8.8 directory
6. run `./configure --prefix=absolute-path-to_software/doxygen`
7. run `make -j n`
8. run `make test`
9. run `make install`
10. update the `export PATH` line in the .bashrc file: `export PATH=absolute-path-to_software/cmake/bin:absolute-path-to_software/hdf5/bin:absolute-path-to_software/mpi/bin:absolute-path-to_software/cubit14.0:absolute-path-to_software/moab/bin:absolute-path-to_software/doxygen/bin:$PATH`
11. run `exec bash`

## Building FRENSIE
At this point all of the dependent software libraries should have been built. If any errors were encountered do not try to proceed to building FRENSIE. If no errors were encountered, follow the instructions below.

1. move to the frensie working directory - not the repo itself (e.g. software/frensie)
2. run `mkdir build`
3. move to the build directory (e.g. software/frensie/build)
4. copy the `FRENSIE/scripts/frensie.sh` into the build directory
5. change the variables in the script to reflect the desired system paths
6. run `./frensie.sh` to configure FRENSIE
7. run `make -j n`
8. run `make test`
9. run `make manual`
10. run `make install`

Because this will eventually be an open source project, the goal is to be able to build FRENSIE without having to acquire commercial software licenses. Currently, the geometry capabilities within FRENSIE are only activated when the DagMC configure option is set to ON (e.g. `-D FRENSIE_ENABLE_DAGMC:BOOL=ON`), which requires a CUBIT license. In the future, more software libraries will be incorporated into FRENSIE which will allow for geometry capabilities to be built without building DagMC.

Note: There are several other configure options that can be changed in the frensie.sh script. `-D FRENSIE_ENABLE_DBC:BOOL=ON` turns on very thorough Design-by-Contract checks that can be a very useful debugging tool. `-D FRENSIE_ENABLE_OPENMP:BOOL=ON` enables OpenMP thread support. `-D FRENSIE_ENABLE_MPI:BOOL=ON` enables MPI support. If your system already has Doxygen 1.8.2 or above, there is no need to install version 1.8.8. Just delete the `-D DOXYGEN_PREFIX` variable from the frensie.sh script.

## Feedback
If any issues are encountered during the build process please direct your questions to [Alex Robinson](https://github.com/aprobinson)