ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstResponseFunction
  tstResponseFunction.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstResponseFunction monte_carlo_estimator_native)
ADD_TEST(ResponseFunction_test tstResponseFunction)

ADD_EXECUTABLE(tstEnergySpaceResponseFunction
  tstEnergySpaceResponseFunction.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstEnergySpaceResponseFunction monte_carlo_estimator_native)
ADD_TEST(EnergySpaceResponseFunction_test tstEnergySpaceResponseFunction)

ADD_EXECUTABLE(tstPhaseSpaceResponseFunction
  tstPhaseSpaceResponseFunction.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhaseSpaceResponseFunction monte_carlo_estimator_native)
ADD_TEST(PhaseSpaceResponseFunction_test tstPhaseSpaceResponseFunction)

ADD_EXECUTABLE(tstParticleHistoryObserverHDF5FileHandler
  tstParticleHistoryObserverHDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleHistoryObserverHDF5FileHandler monte_carlo_estimator_native)
ADD_TEST(ParticleHistoryObserverHDF5FileHandler_test tstParticleHistoryObserverHDF5FileHandler)

ADD_EXECUTABLE(tstEstimatorHDF5FileHandler
  tstEstimatorHDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstEstimatorHDF5FileHandler monte_carlo_estimator_native)
ADD_TEST(EstimatorHDF5FileHandler_test tstEstimatorHDF5FileHandler)

ADD_EXECUTABLE(tstGeneralEstimatorDimensionDiscretization
  tstGeneralEstimatorDimensionDiscretization.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstGeneralEstimatorDimensionDiscretization monte_carlo_estimator_native)
ADD_TEST(GeneralEstimatorDimensionDiscretization_test tstGeneralEstimatorDimensionDiscretization)

ADD_EXECUTABLE(tstEstimator tstEstimator.cpp)
TARGET_LINK_LIBRARIES(tstEstimator monte_carlo_estimator_native)
ADD_TEST(Estimator_test tstEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelEstimator_2_test tstEstimator --threads=2)
  ADD_TEST(SharedParallelEstimator_4_test tstEstimator --threads=4)
ENDIF()

Add_EXECUTABLE(tstEntityEstimator tstEntityEstimator.cpp)
TARGET_LINK_LIBRARIES(tstEntityEstimator monte_carlo_estimator_native)
ADD_TEST(EntityEstimator_test tstEntityEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelEntityEstimator_2_test tstEntityEstimator --threads=2)
  ADD_TEST(SharedParallelEntityEstimator_4_test tstEntityEstimator --threads=4)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  Add_EXECUTABLE(tstDistributedEntityEstimator 
    tstDistributedEntityEstimator.cpp)
  TARGET_LINK_LIBRARIES(tstDistributedEntityEstimator monte_carlo_estimator_native)
  ADD_TEST(DistributedParallelEntityEstimator_1_test 
    ${MPIEXEC} -n 2 tstDistributedEntityEstimator)
  ADD_TEST(DistributedParallelEntityEstimator_2_test 
    ${MPIEXEC} -n 2 tstDistributedEntityEstimator)
  ADD_TEST(DistributedParallelEntityEstimator_4_test 
    ${MPIEXEC} -n 2 tstDistributedEntityEstimator)
ENDIF()

Add_EXECUTABLE(tstStandardEntityEstimator tstStandardEntityEstimator.cpp)
TARGET_LINK_LIBRARIES(tstStandardEntityEstimator monte_carlo_estimator_native)
ADD_TEST(StandardEntityEstimator_test tstStandardEntityEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelStandardEntityEstimator_2_test 
    tstStandardEntityEstimator --threads=2)
  ADD_TEST(SharedParallelStandardEntityEstimator_4_test 
    tstStandardEntityEstimator --threads=4)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  Add_EXECUTABLE(tstDistributedStandardEntityEstimator 
    tstDistributedStandardEntityEstimator.cpp)
  TARGET_LINK_LIBRARIES(tstDistributedStandardEntityEstimator monte_carlo_estimator_native)
  ADD_TEST(DistributedParallelStandardEntityEstimator_1_test 
    ${MPIEXEC} -n 2 tstDistributedStandardEntityEstimator)
  ADD_TEST(DistributedParallelStandardEntityEstimator_2_test 
    ${MPIEXEC} -n 2 tstDistributedStandardEntityEstimator)
  ADD_TEST(DistributedParallelStandardEntityEstimator_4_test 
    ${MPIEXEC} -n 4 tstDistributedStandardEntityEstimator)
ENDIF()

Add_EXECUTABLE(tstStandardSurfaceEstimator
  tstStandardSurfaceEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardSurfaceEstimator monte_carlo_estimator_native)
ADD_TEST(StandardSurfaceEstimator_test tstStandardSurfaceEstimator)

Add_EXECUTABLE(tstSurfaceFluxEstimator tstSurfaceFluxEstimator.cpp)
TARGET_LINK_LIBRARIES(tstSurfaceFluxEstimator monte_carlo_estimator_native)
ADD_TEST(SurfaceFluxEstimator_test tstSurfaceFluxEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelSurfaceFluxEstimator_2_test tstSurfaceFluxEstimator --threads=2)
  ADD_TEST(SharedParallelSurfaceFluxEstimator_4_test tstSurfaceFluxEstimator --threads=4)
ENDIF()

Add_EXECUTABLE(tstSurfaceCurrentEstimator tstSurfaceCurrentEstimator.cpp)
TARGET_LINK_LIBRARIES(tstSurfaceCurrentEstimator monte_carlo_estimator_native)
ADD_TEST(SurfaceCurrentEstimator_test tstSurfaceCurrentEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelSurfaceCurrentEstimator_2_test tstSurfaceCurrentEstimator --threads=2)
  ADD_TEST(SharedParallelSurfaceCurrentEstimator_4_test tstSurfaceCurrentEstimator --threads=4)
ENDIF()

Add_EXECUTABLE(tstCellPulseHeightEstimator tstCellPulseHeightEstimator.cpp)
TARGET_LINK_LIBRARIES(tstCellPulseHeightEstimator monte_carlo_estimator_native)
ADD_TEST(CellPulseHeightEstimator_test tstCellPulseHeightEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelCellPulseHeightEstimator_2_test 
    tstCellPulseHeightEstimator --threads=2)
  ADD_TEST(SharedParallelCellPulseHeightEstimator_4_test 
    tstCellPulseHeightEstimator --threads=4)
ENDIF()

Add_EXECUTABLE(tstStandardCellEstimator
  tstStandardCellEstimator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstStandardCellEstimator monte_carlo_estimator_native)
ADD_TEST(StandardCellEstimator_test tstStandardCellEstimator)

Add_EXECUTABLE(tstCellCollisionFluxEstimator
  tstCellCollisionFluxEstimator.cpp)
TARGET_LINK_LIBRARIES(tstCellCollisionFluxEstimator monte_carlo_estimator_native)
ADD_TEST(CellCollisionFluxEstimator_test tstCellCollisionFluxEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelCellCollisionFluxEstimator_2_test 
    tstCellCollisionFluxEstimator --threads=2)
  ADD_TEST(SharedParallelCellCollisionFluxEstimator_4_test 
    tstCellCollisionFluxEstimator --threads=4)
ENDIF()

Add_EXECUTABLE(tstCellTrackLengthFluxEstimator 
  tstCellTrackLengthFluxEstimator.cpp)
TARGET_LINK_LIBRARIES(tstCellTrackLengthFluxEstimator monte_carlo_estimator_native)
ADD_TEST(CellTrackLengthFluxEstimator_test tstCellTrackLengthFluxEstimator)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelCellTrackLengthFluxEstimator_2_test 
    tstCellTrackLengthFluxEstimator --threads=2)
  ADD_TEST(SharedParallelCellTrackLengthFluxEstimator_4_test 
    tstCellTrackLengthFluxEstimator --threads=4)
ENDIF()

Add_EXECUTABLE(tstTetMeshTrackLengthFluxEstimator
  tstTetMeshTrackLengthFluxEstimator.cpp)
TARGET_LINK_LIBRARIES(tstTetMeshTrackLengthFluxEstimator monte_carlo_estimator_native ${MOAB})
ADD_TEST(TetMeshTrackLengthFluxEstimator_test tstTetMeshTrackLengthFluxEstimator --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")

Add_EXECUTABLE(tstParticleSubtrackEndingGlobalEventDispatcher
  tstParticleSubtrackEndingGlobalEventDispatcher.cpp)
TARGET_LINK_LIBRARIES(tstParticleSubtrackEndingGlobalEventDispatcher monte_carlo_estimator_native ${MOAB})
ADD_TEST(ParticleSubtrackEndingGlobalEventDispatcher_test tstParticleSubtrackEndingGlobalEventDispatcher --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")

Add_EXECUTABLE(tstParticleCollidingInCellEventDispatcher
  tstParticleCollidingInCellEventDispatcher.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleCollidingInCellEventDispatcher monte_carlo_estimator_native)
ADD_TEST(ParticleCollidingInCellEventDispatcher_test tstParticleCollidingInCellEventDispatcher)

ADD_EXECUTABLE(tstParticleCrossingSurfaceEventDispatcher
  tstParticleCrossingSurfaceEventDispatcher.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleCrossingSurfaceEventDispatcher monte_carlo_estimator_native)
ADD_TEST(ParticleCrossingSurfaceEventDispatcher_test tstParticleCrossingSurfaceEventDispatcher)

ADD_EXECUTABLE(tstParticleEnteringCellEventDispatcher
  tstParticleEnteringCellEventDispatcher.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleEnteringCellEventDispatcher monte_carlo_estimator_native)
ADD_TEST(ParticleEnteringCellEventDispatcher_test tstParticleEnteringCellEventDispatcher)

ADD_EXECUTABLE(tstParticleLeavingCellEventDispatcher
  tstParticleLeavingCellEventDispatcher.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleLeavingCellEventDispatcher monte_carlo_estimator_native)
ADD_TEST(ParticleLeavingCellEventDispatcher_test tstParticleLeavingCellEventDispatcher)

ADD_EXECUTABLE(tstParticleSubtrackEndingInCellEventDispatcher
  tstParticleSubtrackEndingInCellEventDispatcher.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleSubtrackEndingInCellEventDispatcher monte_carlo_estimator_native)
ADD_TEST(ParticleSubtrackEndingInCellEventDispatcher_test tstParticleSubtrackEndingInCellEventDispatcher)

ADD_EXECUTABLE(tstParticleCollidingInCellEventDispatcherDB
  tstParticleCollidingInCellEventDispatcherDB.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleCollidingInCellEventDispatcherDB monte_carlo_estimator_native)
ADD_TEST(ParticleCollidingInCellEventDispatcherDB_test tstParticleCollidingInCellEventDispatcherDB)

ADD_EXECUTABLE(tstParticleCrossingSurfaceEventDispatcherDB
  tstParticleCrossingSurfaceEventDispatcherDB.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleCrossingSurfaceEventDispatcherDB monte_carlo_estimator_native)
ADD_TEST(ParticleCrossingSurfaceEventDispatcherDB_test tstParticleCrossingSurfaceEventDispatcherDB)

ADD_EXECUTABLE(tstParticleEnteringCellEventDispatcherDB
  tstParticleEnteringCellEventDispatcherDB.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleEnteringCellEventDispatcherDB monte_carlo_estimator_native)
ADD_TEST(ParticleEnteringCellEventDispatcherDB_test tstParticleEnteringCellEventDispatcherDB)

ADD_EXECUTABLE(tstParticleLeavingCellEventDispatcherDB
  tstParticleLeavingCellEventDispatcherDB.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleLeavingCellEventDispatcherDB monte_carlo_estimator_native)
ADD_TEST(ParticleLeavingCellEventDispatcherDB_test tstParticleLeavingCellEventDispatcherDB)

ADD_EXECUTABLE(tstParticleSubtrackEndingInCellEventDispatcherDB
  tstParticleSubtrackEndingInCellEventDispatcherDB.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleSubtrackEndingInCellEventDispatcherDB monte_carlo_estimator_native)
ADD_TEST(ParticleSubtrackEndingInCellEventDispatcherDB_test tstParticleSubtrackEndingInCellEventDispatcherDB)

ADD_EXECUTABLE(tstObserverRegistrationHelpers
  tstObserverRegistrationHelpers.cpp)
TARGET_LINK_LIBRARIES(tstObserverRegistrationHelpers monte_carlo_estimator_native ${MOAB})
ADD_TEST(ObserverRegistrationHelpers_test tstObserverRegistrationHelpers --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")

ADD_EXECUTABLE(tstEventHandler
  tstEventHandler.cpp)
TARGET_LINK_LIBRARIES(tstEventHandler monte_carlo_estimator_native ${MOAB})
ADD_TEST(EventHandler_test tstEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(EventHandler_2_test 
    tstEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk" --threads=2)
  ADD_TEST(EventHandler_4_test 
    tstEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk" --threads=4)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  Add_EXECUTABLE(tstDistributedEventHandler 
    tstDistributedEventHandler.cpp)
  TARGET_LINK_LIBRARIES(tstDistributedEventHandler monte_carlo_estimator_native ${MOAB})
  ADD_TEST(DistributedParallelEventHandler_1_test 
    ${MPIEXEC} -n 1 tstDistributedEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")
  ADD_TEST(DistributedParallelEventHandler_2_test 
    ${MPIEXEC} -n 2 tstDistributedEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")
  ADD_TEST(DistributedParallelEventHandler_4_test 
    ${MPIEXEC} -n 4 tstDistributedEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")
ENDIF()

ADD_EXECUTABLE(tstEventModuleInterface_Native
  tstModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstEventModuleInterface_Native monte_carlo_estimator_native ${MOAB})
ADD_TEST(EventModuleInterface_Native_test tstventModuleInterface_Native --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")

ADD_EXECUTABLE(tstResponseFunctionFactory
  tstResponseFunctionFactory.cpp)
TARGET_LINK_LIBRARIES(tstResponseFunctionFactory monte_carlo_estimator_native)
ADD_TEST(ResponseFunctionFactory_test tstResponseFunctionFactory --test_resp_func_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_response_functions.xml")

IF(FRENSIE_ENABLE_DAGMC)
ADD_EXECUTABLE(tstEventHandlerFactory_DagMC
  tstEventHandlerFactory_DagMC.cpp)
TARGET_LINK_LIBRARIES(tstEventHandlerFactory_DagMC monte_carlo_estimator_native)
ADD_TEST(EventHandlerFactory_DagMC_test tstEventHandlerFactory_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_dagmc.xml" --test_resp_func_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_response_functions.xml" --test_observer_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_observers_dagmc.xml")
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
ADD_EXECUTABLE(tstEventHandlerFactory_Root
  tstEventHandlerFactory_Root.cpp)
TARGET_LINK_LIBRARIES(tstEventHandlerFactory_Root monte_carlo_estimator_native geometry_root)
ADD_TEST(EventHandlerFactoryRoot_test tstEventHandlerFactory_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_root.xml" --test_resp_func_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_response_functions.xml" --test_observer_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_observers_root.xml")
ENDIF()
