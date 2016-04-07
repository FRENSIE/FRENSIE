# Set up the utility package directory hierarchy
ADD_SUBDIRECTORY(units)
INCLUDE_DIRECTORIES(units/src)

ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(hdf5)
INCLUDE_DIRECTORIES(hdf5/src)

ADD_SUBDIRECTORY(prng)
INCLUDE_DIRECTORIES(prng/src)

ADD_SUBDIRECTORY(distribution)
INCLUDE_DIRECTORIES(distribution/src)

ADD_SUBDIRECTORY(integrator)
INCLUDE_DIRECTORIES(integrator/src)
