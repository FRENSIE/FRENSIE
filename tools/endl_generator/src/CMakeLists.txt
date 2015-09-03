# Create the endl_generator exec
ADD_EXECUTABLE(endl_generator endl_generator.cpp)
TARGET_LINK_LIBRARIES(endl_generator data_gen_electron_photon)

# Add exec to install target
INSTALL(TARGETS endl_generator
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
