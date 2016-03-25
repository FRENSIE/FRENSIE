function build {
    make $1 2>&1 | tee logs/$1_build.log
}

build cmake
source ../src/scripts/source_deps.sh
build lapack  
build mpi
build trilinos
build boost
build doxygen
build odepack
build moab
ls install
