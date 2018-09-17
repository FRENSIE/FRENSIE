FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_event_estimator)

SET(ROOT_GEOM_TEST_TARGET monte_carlo_event_estimator_test_root_geometry)

ADD_SUBDIRECTORY(test_files)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(Estimator DEPENDS tstEstimator.cpp)
FRENSIE_ADD_TEST(Estimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelEstimator_2
    TEST_EXEC_NAME_ROOT Estimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelEstimator_4
    TEST_EXEC_NAME_ROOT Estimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(EntityEstimator DEPENDS tstEntityEstimator.cpp)
FRENSIE_ADD_TEST(EntityEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelEntityEstimator_2
    TEST_EXEC_NAME_ROOT EntityEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelEntityEstimator_4
    TEST_EXEC_NAME_ROOT EntityEstimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(DistributedParallelEntityEstimator
    TEST_EXEC_NAME_ROOT EntityEstimator
    MPI_PROCS 2)
  FRENSIE_ADD_TEST(DistributedParallelEntityEstimator
    TEST_EXEC_NAME_ROOT EntityEstimator
    MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(StandardEntityEstimator DEPENDS tstStandardEntityEstimator.cpp)
FRENSIE_ADD_TEST(StandardEntityEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelStandardEntityEstimator_2
    TEST_EXEC_NAME_ROOT StandardEntityEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelStandardEntityEstimator_4
    TEST_EXEC_NAME_ROOT StandardEntityEstimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(DistributedParallelStandardEntityEstimator
    TEST_EXEC_NAME_ROOT StandardEntityEstimator
    MPI_PROCS 2)
  FRENSIE_ADD_TEST(DistributedParallelStandardEntityEstimator
    TEST_EXEC_NAME_ROOT StandardEntityEstimator
    MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(StandardSurfaceEstimator DEPENDS tstStandardSurfaceEstimator.cpp)
FRENSIE_ADD_TEST(StandardSurfaceEstimator)

FRENSIE_ADD_TEST_EXECUTABLE(StandardCellEstimator DEPENDS tstStandardCellEstimator.cpp)
FRENSIE_ADD_TEST(StandardCellEstimator)

FRENSIE_ADD_TEST_EXECUTABLE(SurfaceFluxEstimator DEPENDS tstSurfaceFluxEstimator.cpp)
FRENSIE_ADD_TEST(SurfaceFluxEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelSurfaceFluxEstimator_2
    TEST_EXEC_NAME_ROOT SurfaceFluxEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelSurfaceFluxEstimator_4
    TEST_EXEC_NAME_ROOT SurfaceFluxEstimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_DAGMC})
  FRENSIE_ADD_TEST_EXECUTABLE(SurfaceFluxEstimatorDagMC
    DEPENDS tstSurfaceFluxEstimatorDagMC.cpp
    LIB_DEPENDS geometry_dagmc)
  FRENSIE_ADD_TEST(SurfaceFluxEstimatorDagMC
    EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(SurfaceCurrentEstimator DEPENDS tstSurfaceCurrentEstimator.cpp)
FRENSIE_ADD_TEST(SurfaceCurrentEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelSurfaceCurrentEstimator_2
    TEST_EXEC_NAME_ROOT SurfaceCurrentEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelSurfaceCurrentEstimator_4
    TEST_EXEC_NAME_ROOT SurfaceCurrentEstimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CellPulseHeightEstimator DEPENDS tstCellPulseHeightEstimator.cpp)
FRENSIE_ADD_TEST(CellPulseHeightEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelCellPulseHeightEstimator_2
    TEST_EXEC_NAME_ROOT CellPulseHeightEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelCellPulseHeightEstimator_4
    TEST_EXEC_NAME_ROOT CellPulseHeightEstimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CellCollisionFluxEstimator DEPENDS tstCellCollisionFluxEstimator.cpp)
FRENSIE_ADD_TEST(CellCollisionFluxEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelCellCollisionFluxEstimator_2
    TEST_EXEC_NAME_ROOT CellCollisionFluxEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
  FRENSIE_ADD_TEST(SharedParallelCellCollisionFluxEstimator_4
    TEST_EXEC_NAME_ROOT CellCollisionFluxEstimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_DAGMC})
  FRENSIE_ADD_TEST_EXECUTABLE(CellCollisionFluxEstimatorDagMC
    DEPENDS tstCellCollisionFluxEstimatorDagMC.cpp
    LIB_DEPENDS geometry_dagmc)
  FRENSIE_ADD_TEST(CellCollisionFluxEstimatorDagMC
    EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m)
ENDIF()

IF(${FRENSIE_ENABLE_ROOT})
  FRENSIE_ADD_TEST_EXECUTABLE(CellCollisionFluxEstimatorRoot
    DEPENDS tstCellCollisionFluxEstimatorRoot.cpp
    TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET}
    LIB_DEPENDS geometry_root)
  FRENSIE_ADD_TEST(CellCollisionFluxEstimatorRoot
    EXTRA_ARGS --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CellTrackLengthFluxEstimator DEPENDS tstCellTrackLengthFluxEstimator.cpp)
FRENSIE_ADD_TEST(CellTrackLengthFluxEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelCellTrackLengthFluxEstimator_2
    TEST_EXEC_NAME_ROOT CellTrackLengthFluxEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
FRENSIE_ADD_TEST(SharedParallelCellTrackLengthFluxEstimator_4
    TEST_EXEC_NAME_ROOT CellTrackLengthFluxEstimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_DAGMC})
  FRENSIE_ADD_TEST_EXECUTABLE(CellTrackLengthFluxEstimatorDagMC
    DEPENDS tstCellTrackLengthFluxEstimatorDagMC.cpp
    LIB_DEPENDS geometry_dagmc)
  FRENSIE_ADD_TEST(CellTrackLengthFluxEstimatorDagMC
    EXTRA_ARGS --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.h5m)
ENDIF()

IF(${FRENSIE_ENABLE_ROOT})
  FRENSIE_ADD_TEST_EXECUTABLE(CellTrackLengthFluxEstimatorRoot
    DEPENDS tstCellTrackLengthFluxEstimatorRoot.cpp
    TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET}
    LIB_DEPENDS geometry_root)
  FRENSIE_ADD_TEST(CellTrackLengthFluxEstimatorRoot
    EXTRA_ARGS --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/basic_root_geometry.root)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(HexMeshTrackLengthFluxEstimator DEPENDS tstHexMeshTrackLengthFluxEstimator.cpp)
FRENSIE_ADD_TEST(HexMeshTrackLengthFluxEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  FRENSIE_ADD_TEST(SharedParallelHexMeshTrackLengthFluxEstimator_2
    TEST_EXEC_NAME_ROOT HexMeshTrackLengthFluxEstimator
    EXTRA_ARGS --threads=2
    OPENMP_TEST)
FRENSIE_ADD_TEST(SharedParallelHexMeshTrackLengthFluxEstimator_4
    TEST_EXEC_NAME_ROOT HexMeshTrackLengthFluxEstimator
    EXTRA_ARGS --threads=4
    OPENMP_TEST)
ENDIF()

IF(${FRENSIE_ENABLE_MOAB})
  FRENSIE_ADD_TEST_EXECUTABLE(TetMeshTrackLengthFluxEstimator DEPENDS tstTetMeshTrackLengthFluxEstimator.cpp)
  FRENSIE_ADD_TEST(TetMeshTrackLengthFluxEstimator
    EXTRA_ARGS --test_input_mesh_file_name=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk)

  IF(${FRENSIE_ENABLE_OPENMP})
    FRENSIE_ADD_TEST(SharedParallelTetMeshTrackLengthFluxEstimator_2
      TEST_EXEC_NAME_ROOT TetMeshTrackLengthFluxEstimator
      EXTRA_ARGS
        --test_input_mesh_file_name=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk
        --threads=2
      OPENMP_TEST)
    FRENSIE_ADD_TEST(SharedParallelTetMeshTrackLengthFluxEstimator_4
      TEST_EXEC_NAME_ROOT TetMeshTrackLengthFluxEstimator
      EXTRA_ARGS
        --test_input_mesh_file_name=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk
        --threads=4
        OPENMP_TEST)
  ENDIF()
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_event_estimator)
