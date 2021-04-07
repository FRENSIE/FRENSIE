FRENSIE_SETUP_PACKAGE(monte_carlo_core
  MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
  NON_MPI_LIBRARIES ${Boost_LIBRARIES} utility_core utility_archive geometry_core data_core)
