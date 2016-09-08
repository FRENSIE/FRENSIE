# Create the endltoxml exec
ADD_EXECUTABLE(endltoxml endltoxml.cpp)
TARGET_LINK_LIBRARIES(endltoxml data_gen_endl)

# Create the endl_cs_xml_modifier exec
ADD_EXECUTABLE(endl_cs_xml_modifier endl_cs_xml_modifier.cpp)
TARGET_LINK_LIBRARIES(endl_cs_xml_modifier data_gen_endl)

# Add programs and execs to install target
INSTALL(PROGRAMS endl_downloader.sh
  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
INSTALL(TARGETS endltoxml
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
INSTALL(TARGETS endl_cs_xml_modifier
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
