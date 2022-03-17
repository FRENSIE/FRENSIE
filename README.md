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
During this process of installing dependencies, there are two important paths for 
the FRENSIE user to decide. For every package, there will be a `/path/to/build/package/`,
where compressed source files will be unpacked and built. There will also be a 
`/path/to/install/package`, which will be used during the configuration step. Inside 
`/path/to/build/package/`, a few more directories will be created. For example, after 
unpacking "package.xx.xx.xx", where the x's signify the version used, there would be a
`/path/to/build/package/package.xx.xx.xx` directory created. A `build` directory will 
typically be created inside `/path/to/build/package/`, where cmake commands will be run. 
There will also be a `src` directory created via soft-link to the the directory unpacked 
from the compressed source files. This standard `src` soft-link helps the build process 
be generalized for different versions of packages. Finally during configuration, the 
`/path/to/install/package` will be decided. This is the location of installation and
does not have to be the same as `/path/to/build/package`, though it can be. There 
may be reasons why a user will wish to make these different. After installing, an 
environment variable will be set inside a user's `.bashrc` script. This will use the
`/path/to/install/package` path.

Throughout these instructions, we have chosen the `/path/to/build/` to be a directory called
`/software/`. Thus, for these instructions all dependency packages will be built in
`/software/package/`. These instructions will also choose to make the `/path/to/install/package`
to be the same as `/path/to/build/package/`, namely `/software/package/`. For this choice,
inside `/software/package/`, there will be the standard `build` and `src` directories mentioned
before along with all directories created during installation. Some examples of directories
created during installation include a `/bin/`, `/lib/`, or `doc` directory.

**Please note that the software libraries should be built in the order that they
are described.**

### Checking out FRENSIE
1. create a working directory where FRENSIE will be built (e.g. software/frensie): `mkdir /software/frensie`
2. move to the frensie directory: `cd /software/frensie`
3. clone the repository: `git clone https://github.com/FRENSIE/FRENSIE.git`
4. make a symbolic link to the new directory: `ln -s FRENSIE src`

### Building Git
1. run `sudo apt-get install git`

**Before any of the software libraries are built, verify that the system has
CMake version 3.17.1 or greater installed. If CMake is not installed or an
older version is present, build CMake using the instructions below.**

### Building CMake
**Basic:**

1. run `sudo apt-get install cmake`
2. prompt for the cmake version with `cmake --version` and verify that the output is >= 3.17.1. If the output
        is less than 3.17.1 proceed to the advanced build instructions

**Advanced:**

1. download the latest source release of cmake [CMake 3.17.1+ source](https://cmake.org/download/)
2. create a directory for cmake (e.g. software/cmake): `mkdir /software/cmake`
3. move the cmake-3.x.tar.gz file to the cmake directory: `mv cmake-3.x.tar.gz /software/cmake/`
4. move to the cmake directory: `cd /software/cmake/`
5. extract the files from the tar file with `tar -xvf cmake-3.x.tar.gz`
6. make a symbolic link to the new directory: `ln -s cmake-3.x src`
7. create a build directory: `mkdir build`
8. move to the build directory (e.g. software/cmake/build): `cd build`
9. configure software build for this system `../src/configure --prefix=/path/to/install/cmake`
10. launch the build of CMake `make -j n`, where n is the number of threads to use while building
11. test the build with `make test`
12. install CMake with `make install`
13. set the environment variable for the `/path/to/install/package` by adding this line to the .bashrc file: `export PATH=/path/to/install/cmake/bin:$PATH`
14. make sure this variable is set by running `exec bash`
15. Check the version of cmake with `cmake --version` and verify that the output is 3.x

### Building Doxygen - optional
**Basic:**

1. run `sudo apt-get install doxygen`
2. run `doxygen --version` and verify that the output is >= 1.8.6

**Advanced:**

1. download the [Doxygen 1.8.8 source](http://sourceforge.net/projects/doxygen/files/)
2. create a directory for doxygen (e.g. software/doxygen): `mkdir /software/doxygen`
3. move the `doxygen-1.8.8.src.tar.gz` file to the doxygen directory : `mv doxygen-1.8.8.src.tar.gz /software/doxygen`
4. move to the doxygen directory: `cd doxygen`
5. extract the files from the tar file with `tar -xvf doxygen-1.8.8.src.tar.gz`
6. move to the doxygen-1.8.8 directory: `cd doxygen-1.8.8`
7. run `./configure --prefix=/path/to/install/doxygen`
8. launch the build of Doxygen with `make -j n`, where n is the number of threads to use while building
9. test the build with `make test`
10. install Doxygen with `make install`
11. set the environment variable for the `/path/to/install/package` by adding this line to the .bashrc file: `export PATH=/path/to/install/doxygen/bin:$PATH`
12. make sure this variable is set by running `exec bash`

### Building Open MPI - optional
**Basic:**

1. run `sudo apt-get install openmpi-bin libopenmpi-dev`
2. run `mpiexec --version` and verify that the output is >= 1.6.5

**Advanced:**

1. download the [Open MPI 2.1.x source](https://www.open-mpi.org/software/ompi/v2.1/)
2. create a directory for MPI (e.g. software/mpi): `mkdir /software/mpi`
3. move the `openmpi-2.1.x.tar.gz` file to the mpi directory: `mv openmpi-2.1.x.tar.gz /software/mpi` 
4. move to the mpi directory: `cd /software/mpi`
5. extract the files from the tar file with `tar -xvf openmpi-2.1.x.tar.gz`
6. make a symbolic link to the new directory: `ln -s openmpi-2.1.x src`
7. create a build directory: `mkdir build`
8. move to the build directory (e.g. software/mpi/build): `cd mpi/build`
9. run `../src/configure --prefix=/path/to/install/mpi`
10. launch the build of MPI with `make -j n`, where n is the number of threads to use while building
11. run `make check`
12. install MPI with `make install`
13. set the environment variable for the `/path/to/install/package` by adding this line to the .bashrc file: `export PATH=/path/to/install/mpi/bin:$PATH`
14. set the environment variable for the library path by adding this line to the .bashrc file: `export LD_LIBRARY_PATH=/path/to/install/mpi/lib:$LD_LIBRARY_PATH`
15. make sure this variable is set by running `exec bash`

### Building HDF5 - optional
**Basic:**

1. run `sudo apt-get install hdf5-tools libhdf5-dev`
2. run `h5ls --version` and verify that the output is >= 1.8.11

**Advanced:**

1. download the [HDF5 1.8.13 source](https://www.hdfgroup.org/downloads/hdf5/source-code/)
2. create a directory for HDF5 (e.g. software/hdf5): `mkdir /software/hdf5`
3. move the `hdf5-1.8.13.tar.gz` file to the hdf5 directory: `mv hdf5-1.8.13.tar.gz /software/hdf5`
4. move to the hdf5 directory: `cd /software/hdf5`
5. extract the files from the tar file with `tar -xvf hdf5-1.8.13.tar.gz`
6. make a symbolic link to the new directory: `ln -s hdf5-1.8.13 src`
7. create a build directory: `mkdir build`
8. move to the build directory (e.g. software/hdf5/build): `cd /hdf5/build`
9. run `../src/configure --enable-optimized --enable-shared --enable-cxx --enable-hl --enable-build-mode=production --prefix=/path/to/install/hdf5`
10. launch the build of HDF5 with `make -j n`, where n is the number of threads to use while building
11. test the build with `make test`
12. install HDF5 with `make install`
13. set the environment variable for the `/path/to/install/package` by adding this line to the .bashrc file: `export PATH=/path/to/install/hdf5/bin:$PATH`
14. set the environment variable for the library path by adding this line to the .bashrc file: `export LD_LIBRARY_PATH=/path/to/install/hdf5/lib:$LD_LIBRARY_PATH`
15. make sure this variable is set by running `exec bash`

### Building Python and NumPy
1. run `sudo apt-get install python python-dev python-numpy`

### Building SWIG
**Basic:**

1. run `sudo apt-get install swig`
2. run `swig -version` and verify that the output is >= 4.0

**Advanced**

1. create a swig directory (e.g. software/swig): `mkdir /software/swig`
2. move to the swig directory: `cd /software/swig`
3. clone the repository: `git clone https://github.com/swig/swig.git`
4. make a symbolic link to the new directory: `ln -s swig src`
5. create a build directory: `mkdir build`
6. move to the build directory (e.g. software/swig/build): `cd /swig/build`
7. run `../src/configure --prefix=/path/to/install/swig`
8. launch the build of SWIG with `make -j n`, where n is the number of threads desired
9. install SWIG with `make install`
10. set the environment variable for the `/path/to/install/package` by adding this line to the .bashrc file: `export PATH=/path/to/install/swig/bin:$PATH`
11. make sure this variable is set by running `exec bash`

### Building Boost
**Basic:**

1. run `sudo apt-get install libboost-all-dev`

**Advanced:**

1. download the [Boost 1.72.0 source](http://sourceforge.net/projects/boost/files/boost/1.72.0/)
2. create a directory for Boost (e.g. software/boost): `mkdir /software/boost/`
3. move the `boost_1_72_0.tar.gz` file to the boost directory: `mv boost_1_72_0.tar.gz /software/boost`
4. move to the boost directory: `cd /software/boost`
5. extract the files from the tar file with `tar -xvf boost_1_72_0.tar.gz`
6. move to the boost_1_72_0 directory (e.g. software/boost/boost_1_72_0): `cd boost_1_72_0`
7. run `./bootstrap.sh --prefix=/path/to/install/boost`
8. if OpenMPI has been built, run `sed -i "$ a using mpi ;" project-config.jam`
9. run `./b2 -jn --prefix=/path/to/install/boost -s NO_BZIP2=1 link=shared runtime-link=shared install`, where n is the number of threads to use while building
10. set the environment variable for the `/path/to/install/package` by adding this line to the .bashrc file: `export LD_LIBRARY_PATH=/path/to/install/boost/lib:$LD_LIBRARY_PATH`
11. make sure this variable is set by running `exec bash`

### Building MOAB - optional
1. create a moab directory (e.g. software/moab): `mkdir /software/moab`
2. move to the moab directory: `cd /software/moab`
3. run `git clone https://bitbucket.org/aprobinson/moab.git`
4. move to the moab directory (e.g. software/moab/moab): `cd moab`
5. run `git checkout Version5.1.0`
6. configure MOAB with `autoreconf -fi`
7. move up a directory (e.g. software/moab): `cd ..`
8. make a symbolic link to the new directory: `ln -s moab src`
9. create a build directory: `mkdir build`
10. move to the build directory (e.g. software/moab/build): `cd build`
11. run `sudo apt-get install libeigen3-dev`
12. configure moab with either the basic or advanced options regarding HDF5
  * **Basic HDF5 Build:**
    * run `../src/configure --enable-optimize --enable-shared --enable-build-mode=production --with-hdf5 --prefix=/path/to/install/moab/`
  * **Advanced HDF5 Build:**
    * run `../src/configure --enable-optimize --enable-shared --enable-build-mode=production --with-hdf5=/path/to/install/hdf5 --prefix=/path/to/install/moab/`
13. launch the build of MOAB with `make -j n`, where n is the number of threads desired
14. run `make check`
15. install MOAB with `make install`
16. set the environment variable for the `/path/to/install/package` by adding this line to the .bashrc file: `export PATH=/path/to/install/moab/bin:$PATH`
17. set the environment variable for the library path by adding this line to the .bashrc file: `export LD_LIBRARY_PATH=/path/to/install/moab/lib:$LD_LIBRARY_PATH`
18. make sure this variable is set by running `exec bash`

### Building DagMC - optional
1. create a dagmc directory (e.g. software/dagmc): `mkdir /software/dagmc`
2. move to the dagmc directory: `cd /software/dagmc`
3. clone the repository: `git clone https://github.com/FRENSIE/DAGMC.git`
4. move to the DAGMC directory (e.g. software/dagmc/DAGMC)
5. run `git checkout develop`
6. move up a directory (e.g. software/dagmc): `cd ..`
7. make a symbolic link to the new directory: `ln -s DAGMC src`
8. create a build directory: `mkdir build`
9. move to the build directory (e.g. software/dagmc/build): `cd build`
10. if HDF5 was built from source, run `env HDF5_ROOT=/path/to/install/hdf5`
11. run `cmake ../src -DCMAKE_INSTALL_PREFIX=/path/to/install/dagmc -DCMAKE_BUILD_TYPE:STRING=Release -DMOAB_DIR=/path/to/install/moab`
12. launch the build of of DagMC `make -j n`, where n is the number of threads desired
13. install DagMC with `make install`
14. set the environment variable for the `/path/to/install/package` by adding this line to the .bashrc file: `export PATH=/path/to/install/dagmc/bin:$PATH`
15. set the environment variable for the library path by adding this line to the .bashrc file: `export LD_LIBRARY_PATH=/path/to/install/dagmc/lib:$LD_LIBRARY_PATH`
16. make sure this variable is set by running `exec bash`

### Building ROOT - optional
**Basic:**

1. download the appropriate [ROOT 6.04/02 binaries](https://root.cern.ch/content/release-60402)
2. move the binary file to the software directory (e.g. software)
4. run `tar -xvf root_v6.04.02*` - Note: This will create a directory called root.
5. add the following line to the .bashrc file: `export PATH=/path/to/install/root/bin:$PATH`
6. add the following line to the .bashrc file: `export LD_LIBRARY_PATH=/path/to/install/root/lib:$LD_LIBRARY_PATH`

If you are using g++ 5.3+ these precompiled binaries will no longer work
(using the root executable will result in an error). Use the advanced build
instructions below instead.

**Advanced:**

1. download the [ROOT 6.04/16 source](https://root.cern.ch/download/root_v6.04.16.source.tar.gz)
2. create a directory for ROOT (e.g. software/root): `mkdir /software/root`
3. move the `root_v6.04.16.source.tar.gz` file to the root directory: `mv root_v6.04.16.source.tar.gz /software/root`
4. move to the root directory: `cd /software/root`
5. extract the files from the tar file with `tar -xvf root_v6.04.16.source.tar.gz`
6. make a symbolic link to the new directory: `ln -s root_v6.04.16 src`
7. create a build directory: `mkdir build`
8. move to the build directory (e.g. software/root/build): `cd build`
9. copy the configuration script `FRENSIE/scripts/root.sh` into the build directory
10. change the variables in the script to reflect the desired system paths
11. run `sudo apt-get install libx11-dev libxpm-dev libxft-dev libxext-dev`
12. configure with `./root.sh`
13. launch the build of ROOT with `make -j n`, where n is the number of threads desired
14. install ROOT with `make install`
15. set the environment variable for the `/path/to/install/package` by adding this line to the .bashrc file: `export PATH=/path/to/install/root/bin:$PATH`
16. set the environment variable for the library path by adding this line to the .bashrc file: `export LD_LIBRARY_PATH=/path/to/install/root/lib:$LD_LIBRARY_PATH`
17. make sure this variable is set by running `exec bash`

## Building FRENSIE
At this point all of the dependent software libraries should have been built. If any errors were encountered do not try to proceed to building FRENSIE. If no errors were encountered, follow the instructions below.

1. move to the frensie working directory - not the repo itself (e.g. software/frensie): `mv /software/frensie`
2. create a build directory: `mkdir build`
3. move to the build directory (e.g. software/frensie/build): `cd build`
4. copy the configuration script `FRENSIE/scripts/frensie.sh` to the build directory
5. change the variables in the script to reflect the desired system paths (if
   the basic build instructions where use for a package the PACKAGE_PREFIX
   variable can be left blank in the script).
6. run `./frensie.sh` to configure FRENSIE
7. launch the build of FRENSIE with `make -j n`, where n is the number of threads desired
8. test the build with `make test`
9. create the frensie manual `make manual`. it can be accessed by entering the command `open index.html` when in the directory `/path-to-frensie/build/doc/manual`
10. install FRENSIE with `make install`
11. set the environment variable for the `/path/to/install/package` by adding this line to the .bashrc file: `export PATH=/path/to/install/frensie/bin:$PATH`
12. set the environment variable for the library path by adding this line to the .bashrc file: `export PYTHONPATH=/path/to/install/frensie/bin:$PYTHONPATH`
13. set the environment variable for the Python path by adding this line to the .bashrc file: `export PYTHONPATH=/path/to/install/frensie/lib/python2.7/site-packages:$PYTHONPATH`

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
