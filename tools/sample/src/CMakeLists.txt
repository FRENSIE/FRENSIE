# Create the incoherent scattering distribution sampling tool
ADD_EXECUTABLE(sample_isd samplePhotonDistributionCore.cpp sample_isd.cpp)
TARGET_LINK_LIBRARIES(sample_isd monte_carlo_collision_native)

# Add exec to install target
INSTALL(TARGETS sample_isd
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)