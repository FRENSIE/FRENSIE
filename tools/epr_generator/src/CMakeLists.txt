# Create the epr_generator exec
ADD_EXECUTABLE(epr_generator epr_generator.cpp)
TARGET_LINK_LIBRARIES(epr_generator data_gen_electron_photon)

# Create the moment_preserving_test_output exec
ADD_EXECUTABLE(moment_preserving_test_output MomentPreservingElectronDataOutput.cpp)
TARGET_LINK_LIBRARIES(moment_preserving_test_output data_gen_electron_photon)

# Add exec to install target
INSTALL(TARGETS epr_generator
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

INSTALL(TARGETS moment_preserving_test_output
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
