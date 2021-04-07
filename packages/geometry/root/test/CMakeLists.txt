FRENSIE_INITIALIZE_PACKAGE_TESTS(geometry_root)

SET(ROOT_GEOM_TEST_TARGET geometry_root_test_geom)

ADD_SUBDIRECTORY(test_files)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(RootModelProperties DEPENDS tstRootModelProperties.cpp)
FRENSIE_ADD_TEST(RootModelProperties)

FRENSIE_ADD_TEST_EXECUTABLE(RootModel
  DEPENDS tstRootModel.cpp
  TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET})
FRENSIE_ADD_TEST(RootModel
  EXTRA_ARGS --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root)

FRENSIE_ADD_TEST_EXECUTABLE(RootModelIArchive
  DEPENDS tstRootModelIArchive.cpp
  TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET})
FRENSIE_ADD_TEST(RootModelIArchiveFullPath
  TEST_EXEC_NAME_ROOT RootModelIArchive
  EXTRA_ARGS --test_archive_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_model_archive_full_path.xml)
FRENSIE_ADD_TEST(RootModelIArchiveRelativePath
  TEST_EXEC_NAME_ROOT RootModelIArchive
  EXTRA_ARGS
  --test_archive_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/basic_root_model_archive_relative_path.xml
  --reset_path=${CMAKE_CURRENT_BINARY_DIR}/test_files)
  

FRENSIE_ADD_TEST_EXECUTABLE(RootNavigator
  DEPENDS tstRootNavigator.cpp
  TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET})
FRENSIE_ADD_TEST(RootNavigator
  EXTRA_ARGS --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST_EXECUTABLE(SharedParallelRootNavigator
    DEPENDS tstSharedParallelRootNavigator.cpp
    TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET})
  FRENSIE_ADD_TEST(SharedParallelRootNavigator_2
    TEST_EXEC_NAME_ROOT SharedParallelRootNavigator
    OPENMP_TEST
    EXTRA_ARGS
    --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root
    --threads=2)

  FRENSIE_ADD_TEST(SharedParallelRootNavigator_4
    TEST_EXEC_NAME_ROOT SharedParallelRootNavigator
    OPENMP_TEST
    EXTRA_ARGS
    --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root
    --threads=4)
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(geometry_root)


