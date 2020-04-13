#!/bin/bash

EXTRA_ARGS=$@
ROOT_SRC=
ROOT_INSTALL=

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$ROOT_INSTALL \
    -D CMAKE_BUILD_TYPE:STRING=RELEASE \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D alien:BOOL=OFF \
    -D asimage:BOOL=OFF \
    -D astiff:BOOL=OFF \
    -D bonjour:BOOL=OFF \
    -D builtin_afterimage:BOOL=OFF \
    -D buildin_fftw3:BOOL=OFF \
    -D builtin_glew:BOOL=OFF \
    -D buildin_llvm:BOOL=OFF \
    -D cxx14:BOOL=ON \
    -D castor:BOOL=OFF \
    -D chirp:BOOL=OFF \
    -D dcache:BOOL=OFF \
    -D fftw3:BOOL=OFF \
    -D fitsio:BOOL=OFF \
    -D genvector:BOOL=OFF \
    -D gfal:BOOL=OFF \
    -D glite:BOOL=OFF \
    -D gviz:BOOL=OFF \
    -D krb5:BOOL=OFF \
    -D ldap:BOOL=OFF \
    -D mathmore:BOOL=OFF \
    -D monalisa:BOOL=OFF \
    -D mysql:BOOL=OFF \
    -D odbc:BOOL=OFF \
    -D opengl:BOOL=OFF \
    -D oracle:BOOL=OFF \
    -D pgsql:BOOL=OFF \
    -D pythia6:BOOL=OFF \
    -D pythia8:BOOL=OFF \
    -D rfio:BOOL=OFF \
    -D sapdb:BOOL=OFF \
    -D sadowpw:BOOL=OFF \
    -D sqlite:BOOL=OFF \
    -D srp:BOOL=OFF \
    -D ssl:BOOL=OFF \
    -D tmva:BOOL=OFF \
    -D vdt:BOOL=OFF \
    -D xft:BOOL=OFF \
    -D xrootd:BOOL=OFF \
    $EXTRA_ARGS \
    $ROOT_SRC

