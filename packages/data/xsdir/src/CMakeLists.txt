# Find all headers and sources (no updates to this file necessary!)
FRENSIE_SETUP_PACKAGE(data_xsdir
  MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
  NON_MPI_LIBRARIES ${Boost_LIBRARIES} utility_core data_core data_ace data_database
  SET_VERBOSE ${CMAKE_VERBOSE_CONFIGURE})
