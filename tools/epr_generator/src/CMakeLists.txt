# Create the epr_generator exec
ADD_EXECUTABLE(epr_generator epr_generator.cpp)
TARGET_LINK_LIBRARIES(epr_generator data_gen_electron_photon)

# Create the aepr_generator exec
ADD_EXECUTABLE(aepr_generator aepr_generator.cpp)
TARGET_LINK_LIBRARIES(aepr_generator data_gen_electron_photon)

# Add exec to install target
INSTALL(TARGETS epr_generator aepr_generator
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
