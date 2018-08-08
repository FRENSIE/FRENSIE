FRENSIE_SETUP_PACKAGE(monte_carlo_event_estimator
                      MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
                      NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_event_core monte_carlo_active_region_response geometry_core utility_mpi utility_stats utility_mesh)
