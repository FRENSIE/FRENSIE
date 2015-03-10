# Create the xsdirtoxml exec
ADD_EXECUTABLE(xsdirtoxml xsdirtoxml.cpp)
TARGET_LINK_LIBRARIES(xsdirtoxml monte_carlo_collision_native)

INSTALL(TARGETS xsdirtoxml
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)