# # Set up the directory hierarchy
# INCLUDE_DIRECTORIES(
# "${CMAKE_SOURCE_DIR}/packages/utility/core/src"
# "${CMAKE_SOURCE_DIR}/packages/utility/prng/src"
# "${CMAKE_SOURCE_DIR}/packages/utility/hdf5/src"
# "${CMAKE_SOURCE_DIR}/packages/utility/interpolation/src"
# "${CMAKE_SOURCE_DIR}/packages/utility/distribution/src"
# "${CMAKE_SOURCE_DIR}/packages/utility/grid/src"
# "${CMAKE_SOURCE_DIR}/packages/utility/integrator/src"
# "${CMAKE_SOURCE_DIR}/packages/data/endf/src"
# "${CMAKE_SOURCE_DIR}/packages/geometry/core/src"
# "${CMAKE_SOURCE_DIR}/packages/geometry/dagmc/src"
# "${CMAKE_SOURCE_DIR}/packages/geometry/root/src"
# "${CMAKE_SOURCE_DIR}/packages/geometry/interface"
# "${CMAKE_SOURCE_DIR}/packages/data/core/src"
# "${CMAKE_SOURCE_DIR}/packages/data/xsdir/src"
# "${CMAKE_SOURCE_DIR}/packages/data/ace/src"
# "${CMAKE_SOURCE_DIR}/packages/data/native/src"
# "${CMAKE_SOURCE_DIR}/packages/data/endl/src"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/core/src"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/source/core/src"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/source/interface"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/source/native/src"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/event/core/src"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/event/interface"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/event/native/src"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/collision/core/src"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/collision/interface"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/collision/native/src"
# "${CMAKE_SOURCE_DIR}/packages/monte_carlo/manager/src"
# "${CMAKE_SOURCE_DIR}/packages/data_gen/free_gas_sab/src"
# "${CMAKE_SOURCE_DIR}/packages/data_gen/electron_photon/src"
# "${CMAKE_SOURCE_DIR}/packages/data_gen/endl/src")

# ADD_SUBDIRECTORY(rng_timer)

# ADD_SUBDIRECTORY(xsdirtoxml)

# ADD_SUBDIRECTORY(listcs)

# ADD_SUBDIRECTORY(acequery)

# ADD_SUBDIRECTORY(facemc)

# ADD_SUBDIRECTORY(epr_generator)

# ADD_SUBDIRECTORY(endl_generator)

# ADD_SUBDIRECTORY(moment_preserving_generator)

# ADD_SUBDIRECTORY(sample)

ADD_SUBDIRECTORY(data_gen)
