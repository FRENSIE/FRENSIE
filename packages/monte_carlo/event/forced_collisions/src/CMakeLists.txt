FRENSIE_SETUP_PACKAGE(monte_carlo_event_forced_collisions
                      MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
                      NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_event_core monte_carlo_collision_kernel utility_prng)
