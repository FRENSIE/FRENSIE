# Set up the packages directory hierarchy
ADD_SUBDIRECTORY(utility)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/utility/core/src utility/core/src utility/prng/src utility/hdf5/src utility/distribution/src)

ADD_SUBDIRECTORY(geometry)
INCLUDE_DIRECTORIES(geometry/core/src geometry/dagmc/src geometry/interface)

ADD_SUBDIRECTORY(data)
INCLUDE_DIRECTORIES(data/ace/src data/epdl/src data/endf/src data/decay/src)

ADD_SUBDIRECTORY(facemc)
INCLUDE_DIRECTORIES(facemc)

ADD_SUBDIRECTORY(transmutation)
INCLUDE_DIRECTORIES(transmutation/src)
