# Set the global test data file path
ADD_SUBDIRECTORY(test_files)

SET(GLOBAL_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files)
SET(GLOBAL_TEST_DATA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_files)

SET(GLOBAL_ACE_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/ace)
SET(GLOBAL_ENDF_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/endf)
SET(GLOBAL_ENDL_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/endl)
SET(GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/native)
SET(GLOBAL_DAGMC_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/dagmc)
SET(GLOBAL_DAGMC_TEST_DATA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_files/dagmc)
SET(GLOBAL_ROOT_TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_files/root)
SET(GLOBAL_ROOT_TEST_DATA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_files/root)

# Set up the packages directory hierarchy
ADD_SUBDIRECTORY(utility)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/utility/core/src
utility/units/src utility/core/src utility/prng/src utility/hdf5/src utility/interpolation/src utility/distribution/src utility/integrator/src utility/grid/src)

ADD_SUBDIRECTORY(geometry)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/geometry geometry/core/src geometry/dagmc/src geometry/root/src geometry/interface)

ADD_SUBDIRECTORY(data)
INCLUDE_DIRECTORIES(data/core/src data/ace/src data/endf/src data/endl/src data/native/src)

ADD_SUBDIRECTORY(monte_carlo)
INCLUDE_DIRECTORIES(monte_carlo/core/src monte_carlo/collision/core/src monte_carlo/collision/native/src)

ADD_SUBDIRECTORY(data_gen)
INCLUDE_DIRECTORIES(data_gen/free_gas_sab/src data_gen/endl/src data_gen/electron_photon/src)

IF(FRENSIE_ENABLE_PYTHON)
  ADD_SUBDIRECTORY(PyFrensie)
ENDIF()

