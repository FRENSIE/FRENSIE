FRENSIE_SETUP_PACKAGE(monte_carlo_event_population_control
                      MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
                      NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_event_core utility_mesh)
