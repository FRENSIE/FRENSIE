# Set up the directory hierarchy
ADD_SUBDIRECTORY(facemc)

ADD_SUBDIRECTORY(rng_timer)

# Create the data processor
# ADD_EXECUTABLE(process_data process_data.cpp)
# TARGET_LINK_LIBRARIES(process_data )

# Create the free gas elastic scattering S(alpha,beta,E) table generator
ADD_EXECUTABLE(fges_sab_gen fges_sab_gen.cpp)
TARGET_LINK_LIBRARIES(fges_sab_gen monte_carlo_collision_native data_gen_free_gas_sab)
SET(CLI_TARGETS fges_sab_gen ${CLI_TARGETS})

# Create the angle dist sampler exec
ADD_EXECUTABLE(sample_scattering_distribution sample_scattering_distribution.cpp)
TARGET_LINK_LIBRARIES(sample_scattering_distribution monte_carlo_manager)
SET(CLI_TARGETS sample_scattering_distribution ${CLI_TARGETS})

INSTALL(TARGETS ${CLI_TARGETS}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
