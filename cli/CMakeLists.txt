# Create the data processor
ADD_EXECUTABLE(process_data process_data.cpp)
TARGET_LINK_LIBRARIES(process_data ${PROJECT_NAME})

# Create the dagfacemc demo
ADD_EXECUTABLE(dagfacemc_demo dagfacemc_demo.cpp)
TARGET_LINK_LIBRARIES(dagfacemc_demo ${PROJECT_NAME})

# Create the random number generator timer
ADD_EXECUTABLE(rng_timer rng_timer.cpp)
TARGET_LINK_LIBRARIES(rng_timer ${PROJECT_NAME})

INSTALL(TARGETS process_data dagfacemc_demo rng_timer
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
