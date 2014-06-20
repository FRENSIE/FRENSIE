# Create the data processor
# ADD_EXECUTABLE(process_data process_data.cpp)
# TARGET_LINK_LIBRARIES(process_data )

# Create the random number generator timer
ADD_EXECUTABLE(rng_timer rng_timer.cpp)
TARGET_LINK_LIBRARIES(rng_timer utility_core utility_prng)

# Create the facemc exec
ADD_EXECUTABLE(facemc facemc.cpp)
TARGET_LINK_LIBRARIES(facemc facemc_manager)

INSTALL(TARGETS rng_timer facemc
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
