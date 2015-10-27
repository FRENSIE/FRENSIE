# Create the acequery exec
ADD_EXECUTABLE(acequery acequery.cpp)
TARGET_LINK_LIBRARIES(acequery monte_carlo_collision_native)

INSTALL(TARGETS acequery
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)