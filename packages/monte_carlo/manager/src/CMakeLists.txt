FRENSIE_SETUP_PACKAGE(monte_carlo_manager
  MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
  NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_core 
  monte_carlo_collision_kernel 
  monte_carlo_active_region_source 
  monte_carlo_event_forced_collisions 
  monte_carlo_event_population_control
  monte_carlo_event_weight_cutoff 
  monte_carlo_event_dispatcher)
