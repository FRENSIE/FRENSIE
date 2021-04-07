FRENSIE_SETUP_PACKAGE(monte_carlo_event_weight_cutoff
                      MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
                      NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_event_core utility_prng)
