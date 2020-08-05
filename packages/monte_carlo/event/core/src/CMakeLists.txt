FRENSIE_SETUP_PACKAGE(monte_carlo_event_core
                      MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
                      NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_core utility_mpi utility_grid utility_direction_discretization)
