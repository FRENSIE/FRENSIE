# Create the facemc exec
IF(FRENSIE_ENABLE_DAGMC OR FRENSIE_ENABLE_ROOT)

  # Create the facemc core library
  ADD_LIBRARY(facemc_core facemcCore.cpp)
  TARGET_LINK_LIBRARIES(facemc_core monte_carlo_manager)

    
  ADD_EXECUTABLE(facemc facemc.cpp)
  TARGET_LINK_LIBRARIES(facemc facemc_core)

  # Add exec to install target
  INSTALL(TARGETS facemc
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

  IF(${FRENSIE_ENABLE_MPI})
    ADD_EXECUTABLE(facemc-mpi facemcMPI.cpp)
    TARGET_LINK_LIBRARIES(facemc-mpi facemc_core)

    INSTALL(TARGETS facemc-mpi
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  ENDIF()
 
ELSE()
  MESSAGE(WARNING "The facemc executable cannot be built without enabling the DagMC or the Root geometry handler!")
ENDIF()