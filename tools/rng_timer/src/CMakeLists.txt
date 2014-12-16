# Create the random number generator timer
ADD_EXECUTABLE(rng_timer rng_timer.cpp)
TARGET_LINK_LIBRARIES(rng_timer utility_core utility_prng)

# Add exec to install target
INSTALL(TARGETS rng_timer
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)