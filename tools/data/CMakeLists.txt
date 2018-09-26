CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/process_xsdir.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/process_xsdir.py)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/endl_to_native_endl.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/endl_to_native_endl.py)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/native_endl_to_native_epr.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/native_endl_to_native_epr.py)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/generate_native_epr.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/generate_native_epr.py)

INSTALL(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/process_xsdir.py
  ${CMAKE_CURRENT_BINARY_DIR}/endl_to_native_endl.py
  ${CMAKE_CURRENT_BINARY_DIR}/native_endl_to_native_epr.py
  ${CMAKE_CURRENT_BINARY_DIR}/generate_native_epr.py
  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  PERMISSIONS OWNER_READ    GROUP_READ    WORLD_READ
              OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE)
