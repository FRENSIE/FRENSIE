FRENSIE_INITIALIZE_PACKAGE_TESTS(geometry_root)

ADD_SUBDIRECTORY(test_files)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(RootModelProperties DEPENDS tstRootModelProperties.cpp)
FRENSIE_ADD_TEST(RootModelProperties)

FRENSIE_ADD_TEST_EXECUTABLE(RootModel DEPENDS tstRootModel.cpp)
FRENSIE_ADD_TEST(RootModel
  EXTRA_ARGS --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root)

FRENSIE_ADD_TEST_EXECUTABLE(RootModelIArchive DEPENDS tstRootModelIArchive.cpp)
FRENSIE_ADD_TEST(RootModelIArchive
  EXTRA_ARGS --test_archive_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_model_archive.xml)

FRENSIE_ADD_TEST_EXECUTABLE(RootNavigator DEPENDS tstRootNavigator.cpp)
FRENSIE_ADD_TEST(RootNavigator
  EXTRA_ARGS --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root)

# FRENSIE_ADD_TEST_EXECUTABLE(RootNavigatorIArchive DEPENDS tstRootNavigatorIArchive.cpp)
# FRENSIE_ADD_TEST(RootNavigatorIArchive
#   EXTRA_ARGS --test_archive_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_navigator_archive.xml)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST_EXECUTABLE(SharedParallelRootNavigator DEPENDS tstSharedParallelRootNavigator.cpp)
  FRENSIE_ADD_TEST(SharedParallelRootNavigator_2
    TEST_EXEC_NAME_ROOT SharedParallelRootNavigator
    EXTRA_ARGS --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelRootNavigator_4
    TEST_EXEC_NAME_ROOT SharedParallelRootNavigator
    EXTRA_ARGS --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root --threads=4
    OPENMP_TEST)
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(geometry_root)


