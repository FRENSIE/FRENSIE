FRENSIE_INITIALIZE_PACKAGE_TESTS(data_core)

FRENSIE_ADD_TEST_EXECUTABLE(SubshellTypeHelpers DEPENDS tstSubshellTypeHelpers.cpp)
FRENSIE_ADD_TEST(SubshellTypeHelpers)

FRENSIE_FINALIZE_PACKAGE_TESTS(data_core)

# ADD_EXECUTABLE(tstCrossSectionsXMLProperties
#   tstCrossSectionsXMLProperties.cpp)
# TARGET_LINK_LIBRARIES(tstCrossSectionsXMLProperties data_core)
# ADD_TEST(CrossSectionsXMLProperties_test tstCrossSectionsXMLProperties --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}")
# SET_PROPERTY(TEST CrossSectionsXMLProperties_test PROPERTY LABELS data_core)
