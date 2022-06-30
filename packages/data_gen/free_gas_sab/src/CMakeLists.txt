INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../neutron/src)

FRENSIE_SETUP_PACKAGE(data_gen_free_gas_sab
  NON_MPI_LIBRARIES utility_integrator monte_carlo_core monte_carlo_collision_core monte_carlo_collision_neutron data_endl)