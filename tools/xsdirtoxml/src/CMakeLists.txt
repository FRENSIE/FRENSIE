# Create the xsdirtoxml exec
ADD_EXECUTABLE(xsdirtoxml xsdirtoxml.cpp)
TARGET_LINK_LIBRARIES(xsdirtoxml data_xsdir)

INSTALL(TARGETS xsdirtoxml
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
