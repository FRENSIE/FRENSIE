# Create the facemc exec
IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(facemc facemc.cpp)
  TARGET_LINK_LIBRARIES(facemc monte_carlo_manager)

  # Add exec to install target
  INSTALL(TARGETS facemc
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
ENDIF()