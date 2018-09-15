FRENSIE_INITIALIZE_PACKAGE_TESTS(geometry_dagmc)

ADD_SUBDIRECTORY(test_files)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(DagMCRay DEPENDS tstDagMCRay.cpp)
FRENSIE_ADD_TEST(DagMCRay)

FRENSIE_ADD_TEST_EXECUTABLE(StandardDagMCCellHandler DEPENDS tstStandardDagMCCellHandler.cpp)
FRENSIE_ADD_TEST(StandardDagMCCellHandler
  EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m)

FRENSIE_ADD_TEST_EXECUTABLE(FastDagMCCellHandler DEPENDS tstFastDagMCCellHandler.cpp)
FRENSIE_ADD_TEST(FastDagMCCellHandler
  EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m)

FRENSIE_ADD_TEST_EXECUTABLE(StandardDagMCSurfaceHandler DEPENDS tstStandardDagMCSurfaceHandler.cpp)
FRENSIE_ADD_TEST(StandardDagMCSurfaceHandler
  EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m)

FRENSIE_ADD_TEST_EXECUTABLE(FastDagMCSurfaceHandler DEPENDS tstFastDagMCSurfaceHandler.cpp)
FRENSIE_ADD_TEST(FastDagMCSurfaceHandler
  EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m)

FRENSIE_ADD_TEST_EXECUTABLE(DagMCModelProperties DEPENDS tstDagMCModelProperties.cpp)
FRENSIE_ADD_TEST(DagMCModelProperties)

FRENSIE_ADD_TEST_EXECUTABLE(DagMCModel DEPENDS tstDagMCModel.cpp)
FRENSIE_ADD_TEST(DagMCModel
  EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m)

FRENSIE_ADD_TEST_EXECUTABLE(DagMCNavigator DEPENDS tstDagMCNavigator.cpp)
FRENSIE_ADD_TEST(DagMCNavigator
  EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST_EXECUTABLE(SharedParallelDagMCNavigator DEPENDS tstSharedParallelDagMCNavigator.cpp)
  FRENSIE_ADD_TEST(SharedParallelDagMCNavigator_2
    TEST_EXEC_NAME_ROOT SharedParallelDagMCNavigator
    EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelDagMCNavigator_4
    TEST_EXEC_NAME_ROOT SharedParallelDagMCNavigator
    EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m --threads=4
    OPENMP_TEST)
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(geometry_dagmc)
