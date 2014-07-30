# Create the data processor
# ADD_EXECUTABLE(process_data process_data.cpp)
# TARGET_LINK_LIBRARIES(process_data )

# Create the random number generator timer
ADD_EXECUTABLE(rng_timer rng_timer.cpp)
TARGET_LINK_LIBRARIES(rng_timer utility_core utility_prng)

# Create the facemc exec
ADD_EXECUTABLE(facemc facemc.cpp)
TARGET_LINK_LIBRARIES(facemc facemc_manager)

# Create the angle dist sampler exec
ADD_EXECUTABLE(sample_scattering_distribution sample_scattering_distribution.cpp)
TARGET_LINK_LIBRARIES(sample_scattering_distribution facemc_manager)

# Create the decay regresssion suite
ADD_EXECUTABLE(decay_regression_suite decay_regression_suite.cpp)
TARGET_LINK_LIBRARIES(decay_regression_suite utility_core transmutation)

# Create a simple decay verification problem
ADD_EXECUTABLE(decay_verification_simple_problem decay_verification_simple_problem.cpp)
TARGET_LINK_LIBRARIES(decay_verification_simple_problem utility_core transmutation)

# Create a simple decay verification problem for boost
ADD_EXECUTABLE(decay_verification_simple_problem_boost
decay_verification_simple_problem_boost.cpp)
TARGET_LINK_LIBRARIES(decay_verification_simple_problem_boost utility_core transmutation)

# Create an intermediate decay verification problem
ADD_EXECUTABLE(decay_verification_intermediate_problem decay_verification_intermediate_problem.cpp)
TARGET_LINK_LIBRARIES(decay_verification_intermediate_problem utility_core transmutation)

# Create an advanced decay verification problem
ADD_EXECUTABLE(decay_verification_advanced_problem decay_verification_advanced_problem.cpp)
TARGET_LINK_LIBRARIES(decay_verification_advanced_problem utility_core transmutation)

# Create a simple decay verification problem
ADD_EXECUTABLE(fission_reaction_rate_verification_problem
fission_reaction_rate_verification_problem.cpp)
TARGET_LINK_LIBRARIES(fission_reaction_rate_verification_problem utility_core transmutation)

INSTALL(TARGETS rng_timer facemc sample_scattering_distribution
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
