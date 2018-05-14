FRENSIE_SETUP_PACKAGE(monte_carlo_active_region_core
  MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
  NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_core utility_prng utility_dist)

