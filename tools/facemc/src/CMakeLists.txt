# Create the facemc exec
IF(FRENSIE_ENABLE_DAGMC OR FRENSIE_ENABLE_ROOT)
    
  ADD_EXECUTABLE(facemc facemcCore.cpp facemc.cpp)
  TARGET_LINK_LIBRARIES(facemc monte_carlo_manager)

  # Add exec to install target
  INSTALL(TARGETS facemc
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
ELSE()
  MESSAGE(WARNING "The facemc executable cannot be built without enabling the ")
  MESSAGE(WARNING "DagMC or the Root geometry handler!")
ENDIF()