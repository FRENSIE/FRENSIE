# Set up the packages directory hierarchy
ADD_SUBDIRECTORY(utility)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/utility/core/src
utility/units/src utility/core/src utility/prng/src utility/hdf5/src utility/distribution/src utility/integrator/src)

ADD_SUBDIRECTORY(geometry)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/geometry geometry/core/src geometry/dagmc/src geometry/root/src geometry/interface)

ADD_SUBDIRECTORY(data)
INCLUDE_DIRECTORIES(data/ace/src data/epdl/src data/endf/src data/native/src)

ADD_SUBDIRECTORY(monte_carlo)
INCLUDE_DIRECTORIES(monte_carlo/core/src monte_carlo/collision/core/src monte_carlo/collision/native/src)

ADD_SUBDIRECTORY(data_gen)
INCLUDE_DIRECTORIES(data_gen/free_gas_sab/src)

