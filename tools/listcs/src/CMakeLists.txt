# Create the listcs exec
ADD_EXECUTABLE(listcs listcs.cpp)
TARGET_LINK_LIBRARIES(listcs data_xsdir)

INSTALL(TARGETS listcs
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
