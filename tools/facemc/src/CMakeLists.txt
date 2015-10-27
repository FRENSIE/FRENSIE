# Create the facemc exec
IF(FRENSIE_ENABLE_DAGMC OR FRENSIE_ENABLE_ROOT)
    
  ADD_EXECUTABLE(facemc facemcCore.cpp facemc.cpp)
  TARGET_LINK_LIBRARIES(facemc monte_carlo_manager)

  # Add exec to install target
  INSTALL(TARGETS facemc
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

  IF(${FRENSIE_ENABLE_MPI})
    ADD_EXECUTABLE(facemc-mpi facemcCore.cpp facemcMPI.cpp)
    TARGET_LINK_LIBRARIES(facemc-mpi monte_carlo_manager)

    INSTALL(TARGETS facemc-mpi
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  ENDIF()
 
ELSE()
  MESSAGE(WARNING "The facemc executable cannot be built without enabling the DagMC or the Root geometry handler!")
ENDIF()