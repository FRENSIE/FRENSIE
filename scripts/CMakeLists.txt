# Parse the ctest dashboard scripts
IF(FRENSIE_ENABLE_DASHBOARD_CLIENT)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/frensie-run-ci.sh.in ${CMAKE_BINARY_DIR}/frensie-run-ci.sh)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/frensie-run-nightly.sh.in ${CMAKE_BINARY_DIR}/frensie-run-nightly.sh)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/frensie-run-nightly-cov.sh.in ${CMAKE_BINARY_DIR}/frensie-run-nightly-cov.sh)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/frensie-run-nightly-memcheck.sh.in ${CMAKE_BINARY_DIR}/frensie-run-nightly-memcheck.sh)
ENDIF()
