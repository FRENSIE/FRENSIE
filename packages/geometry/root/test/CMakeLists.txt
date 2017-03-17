ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstRootModelProperties
  tstRootModelProperties.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRootModelProperties geometry_root)
ADD_TEST(RootModelProperties_test tstRootModelProperties)
SET_PROPERTY(TEST RootModelProperties_test PROPERTY LABELS geometry_root root)

ADD_EXECUTABLE(tstRootModelPropertiesFactory
  tstRootModelPropertiesFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRootModelPropertiesFactory geometry_root)
ADD_TEST(RootModelPropertiesFactory_test tstRootModelPropertiesFactory --test_basic_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml" --test_advanced_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")
SET_PROPERTY(TEST RootModelPropertiesFactory_test PROPERTY LABELS geometry_root root)

ADD_EXECUTABLE(tstRootModel
  tstRootModel.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRootModel geometry_root)
ADD_TEST(RootModel_test tstRootModel --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml")
SET_PROPERTY(TEST RootModel_test PROPERTY LABELS geometry_root root)

ADD_EXECUTABLE(tstRootNavigator
  tstRootNavigator.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstRootNavigator geometry_root)
ADD_TEST(RootNavigator_test tstRootNavigator --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml")
SET_PROPERTY(TEST RootNavigator_test PROPERTY LABELS geometry_root root)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_EXECUTABLE(tstSharedParallelRootNavigator
    tstSharedParallelRootNavigator.cpp
    ${FRENSIE_STD_UNIT_TEST_MAIN})
  TARGET_LINK_LIBRARIES(tstSharedParallelRootNavigator geometry_root)
  ADD_TEST(SharedParallelRootNavigator_2_test tstSharedParallelRootNavigator --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml" --threads=2)
  ADD_TEST(SharedParallelRootNavigator_4_test tstSharedParallelRootNavigator --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml" --threads=4)
  SET_PROPERTY(TEST SharedParallelRootNavigator_2_test PROPERTY LABELS geometry_root root)
  SET_PROPERTY(TEST SharedParallelRootNavigator_4_test PROPERTY LABELS geometry_root root)
ENDIF()


