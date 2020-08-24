FRENSIE_SETUP_PACKAGE(monte_carlo_collision_electron
  MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
  NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_collision_core data_ace data_endl data_native data_database utility_integrator)

  
