INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../neutron/src)

FRENSIE_SETUP_PACKAGE(monte_carlo_collision_photon
  MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
  NON_MPI_LIBRARIES ${Boost_LIBRARIES} monte_carlo_collision_core monte_carlo_collision_neutron data_ace data_endl data_native data_database utility_integrator)
