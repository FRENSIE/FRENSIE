# Create the epr_generator exec
ADD_EXECUTABLE(epr_generator epr_generator.cpp)
TARGET_LINK_LIBRARIES(epr_generator data_gen_electron_photon)

# Add exec to install target
INSTALL(TARGETS epr_generator
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
