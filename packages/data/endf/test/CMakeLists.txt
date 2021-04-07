FRENSIE_INITIALIZE_PACKAGE_TESTS(data_endf)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(EndfFissionYieldsHelpers DEPENDS tstEndfFissionYieldsHelpers.cpp)
FRENSIE_ADD_TEST(EndfFissionYieldsHelpers
  EXTRA_ARGS --test_endf_file=${GLOBAL_ENDF_TEST_DATA_SOURCE_DIR}/U_235.txt)

FRENSIE_ADD_TEST_EXECUTABLE(EndfFissionYieldsFileHandler DEPENDS tstEndfFissionYieldsFileHandler.cpp)
FRENSIE_ADD_TEST(EndfFissionYieldsFileHandler
  EXTRA_ARGS
  --test_endf_file=${GLOBAL_ENDF_TEST_DATA_SOURCE_DIR}/U_235.txt
  --zaid_name=92235)

FRENSIE_FINALIZE_PACKAGE_TESTS(data_endf)
