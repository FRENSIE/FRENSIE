# Parse the ctest dashboard scripts
IF(${SETUP_DASHBOARD_CLIENT})
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/frensie-run-ci.sh.in ${CMAKE_BINARY_DIR}/frensie-run-ci.sh)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/frensie-run-nightly.sh.in ${CMAKE_BINARY_DIR}/frensie-run-nightly.sh)
ENDIF()

# Add certain scripts to the install target
INSTALL(PROGRAMS edump.py
  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)