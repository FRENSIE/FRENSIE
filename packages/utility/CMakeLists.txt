# Set up the utility package directory hierarchy
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(units)
INCLUDE_DIRECTORIES(units/src)

ADD_SUBDIRECTORY(core)

ADD_SUBDIRECTORY(hdf5)
INCLUDE_DIRECTORIES(hdf5/src)

ADD_SUBDIRECTORY(prng)
INCLUDE_DIRECTORIES(prng/src)

ADD_SUBDIRECTORY(distribution)
INCLUDE_DIRECTORIES(distribution/src)
