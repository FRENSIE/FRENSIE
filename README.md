Installation {#installation}
=====

## Dependencies
To promote rapid scientific software development and research, FRENSIE is built
off of a large number of software libraries. The software libraries that FRENSIE
depends on are listed below.

1. [OpenMPI 1.8.2+](http://www.open-mpi.org/) - optional
2. [HDF5 1.8.13+](http://www.hdfgroup.org/HDF5) - optional
3. [Python 2.7+](https://www.python.org/) 
4. [Numpy 1.8+](http://www.numpy.org/) 
5. [SWIG 4.0+](https://github.com/swig/swig)
6. [Boost 1.72.0+](http://www.boost.org/)
7. [MOAB 5.0](https://bitbucket.org/fathomteam/moab) - optional
8. [DagMC 2.8+](http://svalinn.github.io/DAGMC/) - optional
9. [ROOT 6.04/02+](https://root.cern.ch/content/release-60402) - optional

Note that OpenMPI is only required if you plan on running FRENSIE on a
distributed memory system. HDF5 is only required if you plan on exporting
internal FRENSIE data in the 'h5fa' format or if you plan on installing MOAB.
MOAB is required if you plan on using tetrahedral meshes with FRENSIE or if
you plan on exporting hexahedral mesh data. If you plan on using CAD geometries
for particle simulations you will need both DagMC and MOAB (to process the CAD
geometries into the required 'h5m' format you will need
[Trelis](https://www.csimsoft.com/trelis)). ROOT geometries can also be used
for particle simulations if the ROOT package is built. Because users interact
with FRENSIE through Python, the Python, Numpy and SWIG packages, are all
required. Building FRENSIE without the optional packages will result in
faster build times which can be useful for certain development tasks.

Several of the above software libraries will be built from source. Others can
be installed using your system's package manager. This process will be
described in the next sections.

### Additional Software

1. GNU compiler (g++ 6.0+)
2. [CMake 3.17.1+](https://cmake.org/)
3. [git 2.14+](https://git-scm.com/)
4. [Doxygen 1.8.6+](http://www.doxygen.nl/) - optional
5. [Trelis 16.3](https://www.csimsoft.com/trelis) - optional

FRENSIE requires a GNU compiler (6.0 or greater), CMake (3.0.1 or
greater) and git (1.9.1 or greater) to build correctly. If you plan on building
the FRENSIE documentation, Doxygen (1.8.6 or greater) is also required. 

Trelis is used to process a CAD geometry into the 'h5m' format required by the
DagMC package. Once you have obtained a license for Trelis, a useful
installation guide can be found
[here](http://svalinn.github.io/DAGMC/install/plugin.html).

## Building Dependent Software Libraries
Before any of the software libraries are built, verify that the system has
CMake version 3.17.1 or greater installed. If CMake is not installed or an
older version is present, build CMake using the instructions below.

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
3. run `git clone git@github.com:FRENSIE/FRENSIE.git`
4. run `ln -s FRENSIE src`

### Building Git
1. run `sudo apt-get install git`

### Building CMake
**Basic:**

1. run `sudo apt-get install cmake`
2. run `cmake --version` and verify that the output is >= 3.17.1. If the output
        is less than 3.17.1 proceed to the advanced build instructions

**Advanced:**

1. download the latest source release [CMake 3.17.1+ source](https://cmake.org/download/)
2. move the cmake-3.x.tar.gz file to the cmake directory (e.g. software/cmake)
3. move to the cmake directory
4. run `tar -xvf cmake-3.x.tar.gz`
5. run `ln -s cmake-x src`
6. run `mkdir build`
7. move to the build directory (e.g. software/cmake/build)
8. run `../src/configure --prefix=absolute-path-to_software/cmake`
9. run `make -j n`, where n is the number of threads to use while building
10. run `make test`
11. run `make install`
12. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/cmake/bin:$PATH`
13. run `exec bash`
14. run `cmake --version` and verify that the output is 3.x

### Building Doxygen - optional
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

### Building Open MPI - optional
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

### Building HDF5 - optional
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
10. run `../src/configure --enable-optimized --enable-shared --enable-cxx --enable-hl --disable-debug --prefix=absolute-path-to_software/hdf5`
11. run `make -j n`
12. run `make test`
13. run `make install`
14. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/hdf5/bin:$PATH`
15. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/hdf5/lib:$LD_LIBRARY_PATH`
16. run `exec bash`

### Building Python and NumPy
1. run `sudo apt-get install python python-dev python-numpy`

### Building SWIG
**Basic:**

1. run `sudo apt-get install swig`
2. run `swig -version` and verify that the output is >= 4.0

**Advanced**

1. create a swig directory (e.g. software/swig)
2. move to the swig directory
3. run `git clone git@github.com:swig/swig.git`
4. run `ln -s swig src`
5. run `mkdir build`
6. move to the build directory (e.g. software/swig/build)
7. run `../src/configure --prefix=absolute-path-to_software/swig`
8. run `make -j n`
9. run `make install`
10. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/swig/bin:$PATH`

### Building Boost
**Basic:**

1. run `sudo apt-get install libboost-all-dev`

**Advanced:**

1. download the [Boost 1.72.0 source](http://sourceforge.net/projects/boost/files/boost/1.72.0/)
2. move the boost_1_72_0.tar.gz file to the boost directory (e.g. software/boost)
3. move to the boost directory
4. run `tar -xvf boost_1_72_0.tar.gz`
5. move to the boost_1_72_0 directory (e.g. software/boost/boost_1_72_0)
6. run `./bootstrap.sh --prefix=absolute-path-to_software/boost`
7. if OpenMPI has been built, run `sed -i "$ a using mpi ;" project-config.jam`
8. run `./b2 -jn --prefix=absolute-path-to_software/boost -s NO_BZIP2=1 link=shared runtime-link=shared install`, where n is the number of threads to use while building
9. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/boost/lib:$LD_LIBRARY_PATH`
10. run `exec bash`

### Building MOAB - optional
1. create a moab directory (e.g. software/moab)
2. move to the moab directory
3. run `git clone https://bitbucket.org/aprobinson/moab.git`
4. move to the moab directory (e.g. software/moab/moab)
5. run `git checkout Version5.1.0`
6. run `autoreconf -fi`
7. move up a directory (e.g. software/moab)
8. run `ln -s moab src`
9. run `mkdir build`
10. move to the build directory (e.g. software/moab/build)
11. run `sudo apt-get install libeigen3-dev`
12.
  * **Basic HDF5 Build:**
    * run `../src/configure --enable-optimize --enable-shared --disable-debug --with-hdf5 --prefix=absolute-path-to_software/moab/`
  * **Advanced HDF5 Build:**
    * run `../src/configure --enable-optimize --enable-shared --disable-debug --with-hdf5=absolute-path-to_software/hdf5 --prefix=absolute-path-to_software/moab/`
13. run `make -j n`
14. run `make check`
15. run `make install`
16. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/moab/bin:$PATH`
17. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/moab/lib:$LD_LIBRARY_PATH`
18. run `exec bash`

### Building DagMC - optional
1. create a dagmc directory (e.g. software/dagmc)
2. move to the dagmc directory
3. run `git clone https://github.com/FRENSIE/DAGMC.git`
4. move to the DAGMC directory (e.g. software/dagmc/DAGMC)
5. run `git checkout develop`
6. move up a directory (e.g. software/dagmc)
7. run `ln -s DAGMC src`
7. run `mkdir build`
8. move to the build directory (e.g. software/dagmc/build)
9. if HDF5 was built from source, run `env HDF5_ROOT=absolute-path-to_software/hdf5`
10. run `cmake ../src -DCMAKE_INSTALL_PREFIX=absolute-path-to_software/dagmc -DCMAKE_BUILD_TYPE:STRING=Release -DMOAB_DIR=absolute-path-to_software/moab`
11. run `make -j n`
12. run `make install`
13. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/dagmc/bin:$PATH`
14. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_software/dagmc/lib:$LD_LIBRARY_PATH`
14. run `exec bash`

### Building ROOT - optional
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
8. run `make test`
9. run `make manual`
10. run `make install`
11. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/frensie/bin:$PATH`
12. add the following line to the .bashrc file: `export PYTHONPATH=absolute-path-to_software/frensie/bin:$PYTHONPATH`
13. add the following line to the .bashrc file: `export PYTHONPATH=absolute-path-to_software/frensie/lib/python2.7/site-packages:$PYTHONPATH`

**Note 1**: There are several other configure options that can be changed in
the frensie.sh script:
 * `-D FRENSIE_ENABLE_DBC:BOOL=OFF` turns off very thorough Design-by-Contract checks (commonly done with release builds).
 * `-D FRENSIE_ENABLE_PROFILING:BOOL=ON` enables profiling (only in debug builds).
 * `-D FRENSIE_ENABLE_CONVERAGE:BOOL=ON` enables coverage testing (only in debug builds).
 * `-D FRENSIE_ENABLE_OPENMP:BOOL=OFF` disables OpenMP thread support.
 * `-D FRENSIE_ENABLE_MPI:BOOL=ON` enables MPI support.
 * `-D FRENSIE_ENABLE_HDF5:BOOL=ON` enables HDF5 support.
 * `-D FRENSIE_ENABLE_MOAB:BOOL=ON` enables MOAB support.
 * `-D FRENSIE_ENABLE_DAGMC:BOOL=ON` enables the DagMC geometry interfaces.
 * `-D FRENSIE_ENABLE_ROOT:BOOL=ON` enables the ROOT geometry interfaces.
 * `-D FRENSIE_ENABLE_COLOR_OUTPUT:BOOL=OFF` disables color output in TTY shells.
 * `-D FRENSIE_ENABLE_EXPLICIT_TEMPLATE_INST:BOOL=OFF` disables explicit template instantiation. Build times will be shorter when this is enabled.
 * `-D FRENSIE_ENABLE_MANUAL:BOOL=OFF` prevents the user from building the FRENSIE manual using Doxygen (useful if Doxygen is not available).

**Note 2**: To help the build system locate packages in non-standard locations,
the following CMake variables can be set:
 * `-D DOXYGEN_PREFIX:PATH=path-to-doxygen-install-dir` indicates where the doxygen install directory is located. If your system already has Doxygen 1.8.2 or above, there is no need to install version 1.8.8 and this option can be deleted from the frensie.sh script.
 * `-D MPI_PREFIX:PATH=path-to-mpi-install-dir` indicates where the custom MPI install directory is located.
 * `-D HDF5_PREFIX:PATH=path-to-hdf5-install-dir` indicates where the custom HDF5 install directory is located.
 * `-D SWIG_PREFIX:PATH=path-to-swig-install-dir` indicates where the custom SWIG install directory is located.
 * `-D BOOST_PREFIX:PATH=path-to-boost-install-dir` indicates where the custom Boost install directory is located.
 * `-D MOAB_PREFIX:PATH=path-to-moab-install-dir` indicates where the custom MOAB install directory is located.
 * `-D DAGMC_PREFIX:PATH=path-to-dagmc-install-dir` indicates where the custom DAGMC install directory is located.
 * `-D ROOT_PREFIX:PATH=path-to-root-install-dir` indicates where the custom ROOT install directory is located.
 * `-D BUILDNAME_PREFIX:STRING=my-build-name` sets the custom build name that will be displayed on the CDash dashboard (only used when FRENSIE_ENABLE_DASHBOARD_CLIENT is set to ON).
 * `-D XSDIR_DIR:PATH=path-to-mcnp-data` indicates where the nuclear data used by MCNP6 is located on the system (specifically, where the desired xsdir file is located). 

**Note 3**: Each FRENSIE package has a custom build target, a custom test build
target and a custom test run target. For a given package PACKAGE the three
targets will have the following names:
 1. PACKAGE,
 2. PACKAGE_tests,
 3. test-PACKAGE.
If you want to build the utility_core package, you would run
`make utility_core` or `make -j8 utility_core`. If you want to build all of
the utility_core package tests, you would run `make utility_core_tests` or
`make -j8 utility_core_tests`. Once the package tests have been built you can
run the tests by running `make test-utility_core`.

FRENSIE has the following packages:
 * utility_core
 * utility_mpi
 * utility_archive
 * utility_system
 * utility_prng
 * utility_interpolation
 * utility_grid
 * utility_distribution
 * utility_stats
 * utility_integrator
 * utility_mesh
 * geometry_core
 * geometry_dagmc (if DagMC is enabled)
 * geometry_root (if ROOT is enabled)
 * data_core
 * data_ace
 * data_endf
 * data_endl
 * data_native
 * data_database
 * data_xsdir
 * monte_carlo_core
 * monte_carlo_collision_core
 * monte_carlo_collisoin_photon
 * monte_carlo_collision_electron
 * monte_carlo_collision_neutron
 * monte_carlo_collision_kernel
 * monte_carlo_active_region_core
 * monte_carlo_active_region_response
 * monte_carlo_active_region_source
 * monte_carlo_event_core
 * monte_carlo_event_estimator
 * monte_carlo_event_particle_tracker
 * monte_carlo_event_forced_collisions
 * monte_carlo_event_population_control
 * monte_carlo_event_dispatcher
 * monte_carlo_manager
 * data_gen_endl
 * data_gen_electron_photon
 * data_gen_free_gas_sab
 * pyfrensie

**Note 4**: The FRENSIE manual is generated using doxygen (using the make
manual command). After running make install, a link to the manual will be
placed in the doc directory of the install directory. This manual must be
opened in your web browser of choice (e.g. google-chrome manual.html).

## Running FRENSIE
Before running FRENSIE, a database must be generated. This database is used by
FRENSIE to load the various data files requested by the user (it functions in
a similar way to the MCNP xsdir file). Simply run `generate_database.sh` to
generate the database.

Once the database has been generated, review the example problems and the
manual. Additional example problems can be found at
[frensie-tests](https://github.com/FRENSIE/FRENSIE-tests).

## Dashboard
**The dashboard is not currently active - the following comments have been kept
in the event that the dashboard is reactivated again in the future.**

A private [dashboard](http://cdash.ep.wisc.edu) has been set up for developers. Please register with the dashboard and send an email to [Alex Robinson](https://github.com/aprobinson) indicating that you would like to have access to the dashboard.

To set up a dashboard client, simply set the dashboard client setup configure option to on (e.g. `-D SETUP_DASHBOARD_CLIENT:BOOL=ON`). This will add three new make targets: `make Experimental`, `make Nightly` and `make Continuous`. The experimental target should be used to test that the client has been set up correctly. The nightly and continuous targets can be executed on the client machine at regular intervals using cron and crontab (if on a Linux system). However, it is recommended that these targets are never used and instead the shell scripts frensie-run-nightly.sh and frensie-run-ci.sh (found in the scripts directory) are used. Because cron only loads a few environment variables when it executes commands, it is necessary to write shell scripts that load the necessary environment variables, which is what the two scripts do.

Before setting up the crontab entries, a separate frensie build should be created (following the steps above) for nightly builds (e.g. software/frensie-nightly) and for continuous builds (e.g. software/frensie-ci, if a continuous integration system is desired). Once those builds have been completed, the crontab entries can be created by executing `crontab -e`. This will open up the table with the default text editor. At the bottom of this file, add the following lines:
* `0 1 * * * abs-path-to-nightly-build-dir/frensie-run-nightly.sh`
* `*/5 * * * * abs-path-to-ci-build-dir/frensie-run-ci.sh`

The second line can be omitted if the client will only do nightly builds. Note that the first line tells cron to run the nightly script every day at 1:00 AM. The second line tells cron to run the ci script every 5 minutes (if no changes to the master branch have occurred nothing happens).
