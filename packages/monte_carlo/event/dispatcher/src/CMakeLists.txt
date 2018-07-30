FRENSIE_SETUP_PACKAGE(monte_carlo_event_dispatcher
                      MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
                      NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_event_estimator monte_carlo_event_particle_tracker monte_carlo_event_core)
