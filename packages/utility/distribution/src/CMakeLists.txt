FRENSIE_SETUP_PACKAGE(utility_dist
  NON_MPI_LIBRARIES utility_core utility_archive utility_prng ${Boost_LIBRARIES}
  SET_VERBOSE ${CMAKE_VERBOSE_CONFIGURE})
