Installation {#installation}
=====

## Dependencies
To promote rapid scientific software development and research, FRENSIE is built
off of a large number of software libraries. The software libraries that FRENSIE
depends on are listed below.

1. [HDF5 1.8.13+](http://www.hdfgroup.org/HDF5)
2. [OpenMPI 1.8.2](http://www.open-mpi.org/) - optional
3. [Cubit 14.0](https://cubit.sandia.gov/index.html) - optional
4. [CGM 14.1pre](http://trac.mcs.anl.gov/projects/ITAPS/wiki/CGM) - only with Cubit
5. [MOAB 4.6.3](http://trac.mcs.anl.gov/projects/ITAPS/wiki/MOAB)
6. [Trilinos 11.14.3](http://trilinos.org/)
7. [Boost 1.56.0+](http://www.boost.org/)
8. [ROOT 6.04/02+](https://root.cern.ch/content/release-60402) - optional
9. [Python 2.7+](https://www.python.org/) - optional
10. [Numpy 1.8+](http://www.numpy.org/) - optional
11. [H5Py 2.4+](http://www.h5py.org/) - optional
12. [SWIG 3.0.8+](http://www.swig.org/) - optional

Note that OpenMPI is only required if you plan on running FRENSIE on a
distributed memory system. Cubit is only required if you plan on using CAD
geometries for particle simulations. If Cubit is used, CGM must also be
built. If you do not plan on doing particle simulations both ROOT and Cubit
can be neglected. If the FRENSIE python interfaces will be used the Python,
SWIG, Numpy and H5Py packages will also be required. Building FRENSIE without
these optional packages will result in faster build times which can be useful
for certain development tasks.

FRENSIE also requires a GNU compiler (4.7.3 or greater), CMake (3.0.1 or
greater) and git (1.9.1 or greater) to build correctly. If you plan on building
the FRENSIE documentation, Doxygen (1.8.6 or greater) is also required. Several
of the above software libraries will be built from source. Others can be
installed using your system's package manager. This process will be described
in the next section.

## Building Dependent Software Libraries
Before any of the software libraries are built, verify that the system has
CMake version 3.0.1 or greater installed. If CMake is not installed or an older
version is present, build CMake using the instructions below.

When building software libraries and executables from source, the following
directory structure should be adopted: software/package/package.xx.xx.xx,
software/package/build, software/package/src. "package" will be the name of the
particular software package. "package.xx.xx.xx" comes from unpacking the
compressed source files (e.g. package.tar.gz). The src directory is created by
making a softlink to the package.xx.xx.xx directory. This is done to make the
build a bit easier.

Please note that the software libraries should be built in the order that they
are described.

### Checking out FRENSIE
1. create a working directory where FRENSIE will be built (e.g. software/frensie)
2. move to the frensie directory
3. run `git clone git@github.com:aprobinson/FRENSIE.git`
4. run `ln -s FRENSIE src`

### Building CMake
**Basic:**

1. run `sudo apt-get install cmake`
2. run `cmake --version` and verify that the output is >= 3.0.1 or greater

**Advanced:**

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

### Building Doxygen
**Basic:**

1. run `sudo apt-get install doxygen`
2. run `doxygen --version` and verify that the output is >= 1.8.6

**Advanced:**

1. download the [Doxygen 1.8.8 source](http://sourceforge.net/projects/doxygen/files/)
2. move the `doxygen-1.8.8.src.tar.gz` file to the doxygen directory (e.g. software/doxygen)
3. move to the doxygen directory
4. run `tar -xvf doxygen-1.8.8.src.tar.gz`
5. move to the doxygen-1.8.8 directory
6. run `./configure --prefix=absolute-path-to_software/doxygen`
7. run `make -j n`
8. run `make test`
9. run `make install`
10. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/doxygen/bin:$PATH`
11. run `exec bash`

### Building Python, NumPy, H5Py - Optional
1. run `sudo apt-get install python python-dev python-numpy python-h5py`

### Building SWIG - Only with Python
**Basic:**

1. run `sudo apt-get install swig`

**Advanced**

1. download the [SWIG 3.0.8 source](http://www.swig.org/download.html)
2. move the swig swig-3.0.8.tar.gz file to the swig directory (e.g. software/swig)
4. run `tar -xvf swig-3.0.8.tar.gz`
5. run `ln -s swig-3.0.8 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/swig/build)
8. run `../src/configure --enable-cpp11-testing --prefix=absolute-path-to_software/swig`
9. run `make -j n`
11. run `make install`
12. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/swig/bin:$PATH`

### Building HDF5
**Basic:**

1. run `sudo apt-get install hdf5-tools libhdf5-dev`
2. run `h5ls --version` and verify that the output is >= 1.8.11

**Advanced:**

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
14. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/hdf5/bin:$PATH`
15. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/hdf5/lib:$LD_LIBRARY_PATH`
16. run `exec bash`

### Building Open MPI - Optional
**Basic:**

1. run `sudo apt-get install openmpi-bin libopenmpi-dev`
2. run `mpiexec --version` and verify that the output is >= 1.6.5

**Advanced:**

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
12. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/mpi/bin:$PATH`
13. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/mpi/lib:$LD_LIBRARY_PATH`
14. run `exec bash`

### Building Cubit - Optional
1. Cubit is not open source software so a [license](https://cubit.sandia.gov/public/licensing.html) must be acquired.
2. The binary files will be be available for download once a license has been acquired
3. move the Cubit-14.0-Lin64.tar.gz file to the cubit14.0 directory (e.g. software/cubit14.0)
4. run `tar -xvf Cubit-14.0-Lin64.tar.gz`
5. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/cubit14.0:$PATH`
6. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/cubit14.0/bin:$LD_LIBRARY_PATH`
7. run `exec bash`

### Building CGM - Only with Cubit
1. download the [CGM 14.1pre source](http://ftp.mcs.anl.gov/pub/fathom/cgm-nightly-trunk.tar.gz)
2. move the cgm-nightly-trunk.tar.gz file to the cgm directory (e.g. software/cgm)
3. move to the cgm directory
4. run `tar -xvf cgm-nightly-trunk.tar.gz`
5. run `ln -s cgma-14.1pre src`
6. run `mkdir build`
7. move to the build directory (e.g. software/cgm/build)
8. run `../src/configure --enable-optimize --enable-shared --disable-debug CXXFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 --with-cubit=absolute-path-to_software/cubit14.0 --prefix=absolute-path-to_software/cgm`
9. run `make -j n`
10. run `make check`
11. run `make install`
12. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/cgm/lib:$LD_LIBRARY_PATH`

### Building MOAB
1. download the [MOAB 4.6.3 source](http://ftp.mcs.anl.gov/pub/fathom/moab-4.6.3.tar.gz)
2. move the moab-4.6.3.tar.gz file to the moab directory (e.g. software/moab)
3. move to the moab directory
4. run `tar -xvf moab-4.6.3.tar.gz`
5. run `ln -s moab-4.6.3 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/moab/build)
8.
  * **Basic HDF5 Build:**
    * if DagMC is desired (Cubit 14.0 and CGM must be built):
    run `../src/configure --enable-optimize --enable-shared --disable-debug CXXFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 --with-cgm=absolute-path-to_software/cgm/ --with-hdf5 --prefix=absolute-path-to_software/moab/`
    * else run `../src/configure --enable-optimize --enable-shared --disable-debug CXXFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 --with-hdf5 --prefix=absolute-path-to_software/moab/`
  * **Advanced HDF5 Build:**
    * if DagMC is desired (Cubit 14.0 and CGM must be built):
    run `../src/configure --enable-optimize --enable-shared --disable-debug CXXFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 --with-cgm=absolute-path-to_software/cgm/ --with-hdf5=absolute-path-to_software/hdf5 --prefix=absolute-path-to_software/moab/`
    * else run `../src/configure --enable-optimize --enable-shared --disable-debug CXXFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 --with-hdf5=absolute-path-to_software/hdf5 --prefix=absolute-path-to_software/moab/`
9. run `make -j n`
10. run `make check`
11. run `make install`
12. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/moab/bin:$PATH`
13. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/moab/lib:$LD_LIBRARY_PATH`
14. run `exec bash`

### Building Boost
**Basic:**

1. run `sudo apt-get install libboost-all-dev`

**Advanced:**

1. download the [Boost 1.56.0 source](http://sourceforge.net/projects/boost/files/boost/1.56.0/)
2. move the boost_1_56_0.tar.gz file to the boost directory (e.g. software/boost)
3. move to the boost directory
4. run `tar -xvf boost_1_56_0.tar.gz`
5. move to the boost_1_56_0 directory (e.g. software/boost/boost_1_56_0)
6. run `./bootstrap.sh --prefix=absolute-path-to_software/boost`
7. run `./b2  --prefix=absolute-path-to_software/boost -s NO_BZIP2=1 link=shared runtime-link=shared cxxflags="-D_GLIBCXX_USE_CXX11_ABI=0"`
8. run `./b2 install`
9. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/boost/lib:$LD_LIBRARY_PATH`
10. run `exec bash`

### Building Trilinos
1. download the [Trilinos 11.14.3 source](http://trilinos.org/download/)
2. move the trilinos-11.14.3-Source.tar.gz file to the trilinos directory (e.g. software/trilinos)
3. move to the trilinos directory
4. run `tar -xvf trilinos-11.14.3-Source.tar.gz`
5. run `ln -s trilinos-11.14.3.Source src`
6. run `mkdir build`
7. move to the build directory (e.g. software/trilinos/build)
8. copy `FRENSIE/scripts/trilinos-basic.sh` into the build directory
9. change the variables in the script to reflect the desired system paths
10. run `./trilinos-basic.sh` to configure trilinos
11. run `make -j n`
12. run `make test`
13. run `make install`
14. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/trilinos/lib:$LD_LIBRARY_PATH`
15. add the following line to the .bashrc file: `export PYTHONPATH=absolute-path-to_software/trilinos/lib/python2.7/site-packages:$PYTHONPATH`
15. run `exec bash`

Note: If your system does not have LAPACK installed Trilinos will give you
a configure error. You can use your system's package manager to install LAPACK
or you can build if from source using the following instructions below. If
you build LAPACK from source, use the FRENSIE/scripts/trilinos.sh script
instead of the FRENSIE/scripts/trilinos-basic.sh script since it will allow
you to specify the location of your custom build LAPACK package.

**Basic:**

1. run `sudo apt-get install liblapack-dev liblapack3`

Note: If on Ubuntu 16.04 this is the recommended way to install lapack. The
advanced install below will result in an runtime error when importing numpy in
python.

**Advanced:**

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
14. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/lapack/lib:$LD_LIBRARY_PATH`
15. run `exec bash`

### Building ROOT - Optional
**Basic:**

1. download the appropriate [ROOT 6.04/02 binaries](https://root.cern.ch/content/release-60402)
2. move the binary file to the software directory (e.g. software)
4. run `tar -xvf root_v6.04.02*` - Note: This will create a directory called root.
5. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/root/bin:$PATH`
6. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/root/lib:$LD_LIBRARY_PATH`

If you are using g++ 5.3+ these precompiled binaries will no longer work
(using the root executable will result in an error). Use the advanced build
instructions below instead.

**Advanced:**

1. download the [ROOT 6.04/16 source](https://root.cern.ch/download/root_v6.04.16.source.tar.gz)
2. move the root_v6.04.16.source.tar.gz file to the root directory (e.g. software/root)
3. move to the root directory
4. run `tar -xvf root_v6.04.16.source.tar.gz`
5. run `ln -s root_v6.04.16 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/root/build)
8. copy `FRENSIE/scripts/root.sh` into the build directory
9. change the variables in the script to reflect the desired system paths
10. run `sudo apt-get install libx11-dev libxpm-dev libxft-dev libxext-dev`
11. run `./root.sh`
12. run `make -j n`
13. run `make install`
14. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/root/bin:$PATH`
15. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/root/lib:$LD_LIBRARY_PATH`

## Building FRENSIE
At this point all of the dependent software libraries should have been built. If any errors were encountered do not try to proceed to building FRENSIE. If no errors were encountered, follow the instructions below.

1. move to the frensie working directory - not the repo itself (e.g. software/frensie)
2. run `mkdir build`
3. move to the build directory (e.g. software/frensie/build)
4. copy the `FRENSIE/scripts/frensie.sh`
5. change the variables in the script to reflect the desired system paths (if
   the basic build instructions where use for a package the PACKAGE_PREFIX
   variable can be left blank in the script).
6. run `./frensie.sh` to configure FRENSIE
7. run `make -j n`
8. run `make test-fast`
9. run `make test-facemc` - WARNING: these tests can be slow!
9. run `make manual`
10. run `make install`

**Note 1**: There are several other configure options that can be changed in
the frensie.sh script:
 * `-D FRENSIE_ENABLE_DBC:BOOL=OFF` turns off very thorough Design-by-Contract checks (commonly done with release builds).
 * `-D FRENSIE_ENABLE_PROFILING:BOOL=ON` enables profiling (only in debug builds).
 * `-D FRENSIE_ENABLE_CONVERAGE:BOOL=ON` enables coverage testing (only in debug builds).
 * `-D FRENSIE_ENABLE_OPENMP:BOOL=OFF` disables OpenMP thread support.
 * `-D FRENSIE_ENABLE_MPI:BOOL=ON` enables MPI support.
 * `-D FRENSIE_ENABLE_PYTHON:BOOL=ON` enables the FRENSIE python interfaces.
 * `-D FRENSIE_ENABLE_ROOT:BOOL=ON` enables the ROOT geometry interfaces.
 * `-D FRENSIE_ENABLE_DAGMC:BOOL=ON` enables the DagMC geometry interfaces.
 * `-D FRENSIE_ENABLE_DASHBOARD_CLIENT:BOOL=ON` allows the system to act as a dashboard client (by running make Experimental, make Continuous and make Nightly).
 * `-D FRENSIE_ENABLE_MANUAL:BOOL=OFF` prevents the user from building the FRENSIE manual using Doxygen (useful if Doxygen is not available).

**Note 2**: To help the build system locate packages in non-standard locations,
the following CMake variables can be set:
 * `-D HDF5_PREFIX:PATH=path-to-hdf5-install-dir` indicates where the custom HDF5 install directory is located.
 * `-D MPI_PREFIX:PATH=path-to-mpi-install-dir` indicates where the custom MPI install directory is located.
 * `-D MOAB_PREFIX:PATH=path-to-mpi-install-dir` indicates where the custom MOAB install directory is located.
 * `-D MOAB_SOURCE:PATH=path-to-moab-src-dir` indicates where the MOAB source directory is located if it is separate from the MOAB install prefix.
 * `-D TRILINOS_PREFIX:PATH=path-to-trilinos-install-dir` indicates where the custom Trilinos install directory is located.
 * `-D TRILINOS_SOURCE:PATH=path-to-trilinos-src-dir` indicates where the Trilinos source directory is located if it is separate from the Trilinos install prefix.
 * `-D BOOST_PREFIX:PATH=path-to-boost-install-dir` indicates where the custom Boost install directory is located.
 * `-D ROOT_PREFIX:PATH=path-to-root-install-dir` indicates where the custom ROOT install directory is located.
 * `-D SWIG_PREFIX:PATH=path-to-swig-install-dir` indicates where the custom SWIG install directory is located.
 * `-D DOXYGEN_PREFIX:PATH=path-to-doxygen-install-dir` indicates where the doxygen install directory is located. If your system already has Doxygen 1.8.2 or above, there is no need to install version 1.8.8 and this option can be deleted from the frensie.sh script.
 * `-D BUILDNAME_PREFIX:STRING=my-build-name` sets the custom build name that will be displayed on the CDash dashboard (only used when FRENSIE_ENABLE_DASHBOARD_CLIENT is set to ON).
 * `-D MCNP_DATA_DIR:PATH=path-to-mcnp-data` indicates where the nuclear data used by MCNP6 is located on the system. When this configure option is used, the FACEMC executable can be tested using the nuclear data used by MCNP6 by running `make test` or `make test-slow`. To disable these tests delete this configure option from the frensie.sh script.

The FRENSIE build system needs to know where the Trilinos source files
and Moab source files are. Therefore, there are two optional CMake variables
called TRILINOS_SOURCE and MOAB_SOURCE that can be set if the source files are
in a non-standard location (not in TRILINOS_PREFIX/src or MOAB_PREFIX/src ).
This variable is shown in the frensie.sh script.

There are two reasons why the Trilinos source file location is needed. The
first is that Trilinos provides a standard unit test main file that can
be used to compile basic unit test suites. The second reason is because of
a bug that has been found in the Teuchos_TwoDArray.hpp file. A patch file
has been created and will be applied by the build system.

The reason why the moab source file location is needed is because of a race
condition that was found in the DagMC.cpp file. Without patching this file
the only safe way to run DagMC with threads is by placing omp critical blocks
around each DagMC call, which results in very poor thread scaling. A patch
file has been created which will be applied by the build system. The first time
the patch is applied, the build system will report an error and indicate that
moab must be rebuilt before it can proceed. After rebuilding moab by simply
going to the moab build directory and running `make -j n` and `make install`
frensie can be reconfigured by running the frensie.sh script and the build
system should report no errors. After applying the patch to fix the race
condition close to linear thread scaling should be observed.

## Dashboard
A private [dashboard](http://cdash.ep.wisc.edu) has been set up for developers. Please register with the dashboard and send an email to [Alex Robinson](https://github.com/aprobinson) indicating that you would like to have access to the dashboard.

To set up a dashboard client, simply set the dashboard client setup configure option to on (e.g. `-D SETUP_DASHBOARD_CLIENT:BOOL=ON`). This will add three new make targets: `make Experimental`, `make Nightly` and `make Continuous`. The experimental target should be used to test that the client has been set up correctly. The nightly and continuous targets can be executed on the client machine at regular intervals using cron and crontab (if on a Linux system). However, it is recommended that these targets are never used and instead the shell scripts frensie-run-nightly.sh and frensie-run-ci.sh (found in the scripts directory) are used. Because cron only loads a few environment variables when it executes commands, it is necessary to write shell scripts that load the necessary environment variables, which is what the two scripts do.

Before setting up the crontab entries, a separate frensie build should be created (following the steps above) for nightly builds (e.g. software/frensie-nightly) and for continuous builds (e.g. software/frensie-ci, if a continuous integration system is desired). Once those builds have been completed, the crontab entries can be created by executing `crontab -e`. This will open up the table with the default text editor. At the bottom of this file, add the following lines:
* `0 1 * * * abs-path-to-nightly-build-dir/frensie-run-nightly.sh`
* `*/5 * * * * abs-path-to-ci-build-dir/frensie-run-ci.sh`

The second line can be omitted if the client will only do nightly builds. Note that the first line tells cron to run the nightly script every day at 1:00 AM. The second line tells cron to run the ci script every 5 minutes (if no changes to the master branch have occured nothing happens).

## Feedback
If any issues are encountered during the build process please direct your questions to [Alex Robinson](https://github.com/aprobinson), [Eli Moll](https://github.com/ecmoll) or [Luke Kersting](https://github.com/lkersting).
