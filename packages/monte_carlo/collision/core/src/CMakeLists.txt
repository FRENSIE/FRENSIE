FRENSIE_SETUP_PACKAGE(monte_carlo_collision_core
  MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
  NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_core data_ace data_endl data_native utility_prng utility_dist utility_grid)
