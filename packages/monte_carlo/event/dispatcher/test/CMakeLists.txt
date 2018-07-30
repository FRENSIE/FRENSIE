FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_event_dispatcher)

SET(ROOT_GEOM_TEST_TARGET monte_carlo_event_dispatcher_test_root_geometry)

ADD_SUBDIRECTORY(test_files)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(ParticleSubtrackEndingGlobalEventDispatcher DEPENDS tstParticleSubtrackEndingGlobalEventDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleSubtrackEndingGlobalEventDispatcher
  EXTRA_ARGS --test_input_mesh_file_name=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk)

# Add_EXECUTABLE(tstParticleCollidingInCellEventLocalDispatcher
#   tstParticleCollidingInCellEventLocalDispatcher.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstParticleCollidingInCellEventLocalDispatcher monte_carlo_estimator_native)
# ADD_TEST(ParticleCollidingInCellEventLocalDispatcher_test tstParticleCollidingInCellEventLocalDispatcher)
# SET_PROPERTY(TEST ParticleCollidingInCellEventLocalDispatcher_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstParticleCrossingSurfaceEventLocalDispatcher
#   tstParticleCrossingSurfaceEventLocalDispatcher.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstParticleCrossingSurfaceEventLocalDispatcher monte_carlo_estimator_native)
# ADD_TEST(ParticleCrossingSurfaceEventLocalDispatcher_test tstParticleCrossingSurfaceEventLocalDispatcher)
# SET_PROPERTY(TEST ParticleCrossingSurfaceEventLocalDispatcher_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstParticleEnteringCellEventLocalDispatcher
#   tstParticleEnteringCellEventLocalDispatcher.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstParticleEnteringCellEventLocalDispatcher monte_carlo_estimator_native)
# ADD_TEST(ParticleEnteringCellEventLocalDispatcher_test tstParticleEnteringCellEventLocalDispatcher)
# SET_PROPERTY(TEST ParticleEnteringCellEventLocalDispatcher_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstParticleLeavingCellEventLocalDispatcher
#   tstParticleLeavingCellEventLocalDispatcher.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstParticleLeavingCellEventLocalDispatcher monte_carlo_estimator_native)
# ADD_TEST(ParticleLeavingCellEventLocalDispatcher_test tstParticleLeavingCellEventLocalDispatcher)
# SET_PROPERTY(TEST ParticleLeavingCellEventLocalDispatcher_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstParticleSubtrackEndingInCellEventLocalDispatcher
#   tstParticleSubtrackEndingInCellEventLocalDispatcher.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstParticleSubtrackEndingInCellEventLocalDispatcher monte_carlo_estimator_native)
# ADD_TEST(ParticleSubtrackEndingInCellEventLocalDispatcher_test tstParticleSubtrackEndingInCellEventLocalDispatcher)
# SET_PROPERTY(TEST ParticleSubtrackEndingInCellEventLocalDispatcher_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstParticleCollidingInCellEventDispatcher
#   tstParticleCollidingInCellEventDispatcher.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstParticleCollidingInCellEventDispatcher monte_carlo_estimator_native)
# ADD_TEST(ParticleCollidingInCellEventDispatcher_test tstParticleCollidingInCellEventDispatcher)
# SET_PROPERTY(TEST ParticleCollidingInCellEventDispatcher_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstParticleCrossingSurfaceEventDispatcher
#   tstParticleCrossingSurfaceEventDispatcher.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstParticleCrossingSurfaceEventDispatcher monte_carlo_estimator_native)
# ADD_TEST(ParticleCrossingSurfaceEventDispatcher_test tstParticleCrossingSurfaceEventDispatcher)
# SET_PROPERTY(TEST ParticleCrossingSurfaceEventDispatcher_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstParticleEnteringCellEventDispatcher
#   tstParticleEnteringCellEventDispatcher.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstParticleEnteringCellEventDispatcher monte_carlo_estimator_native)
# ADD_TEST(ParticleEnteringCellEventDispatcher_test tstParticleEnteringCellEventDispatcher)
# SET_PROPERTY(TEST ParticleEnteringCellEventDispatcher_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstParticleLeavingCellEventDispatcher
#   tstParticleLeavingCellEventDispatcher.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstParticleLeavingCellEventDispatcher monte_carlo_estimator_native)
# ADD_TEST(ParticleLeavingCellEventDispatcher_test tstParticleLeavingCellEventDispatcher)
# SET_PROPERTY(TEST ParticleLeavingCellEventDispatcher_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstParticleSubtrackEndingInCellEventDispatcher
#   tstParticleSubtrackEndingInCellEventDispatcher.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstParticleSubtrackEndingInCellEventDispatcher monte_carlo_estimator_native)
# ADD_TEST(ParticleSubtrackEndingInCellEventDispatcher_test tstParticleSubtrackEndingInCellEventDispatcher)
# SET_PROPERTY(TEST ParticleSubtrackEndingInCellEventDispatcher_test PROPERTY LABELS monte_carlo_estimator_native)

# ADD_EXECUTABLE(tstEventHandler
#   tstEventHandler.cpp)
# TARGET_LINK_LIBRARIES(tstEventHandler monte_carlo_estimator_native ${MOAB})
# ADD_TEST(EventHandler_test tstEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")
# SET_PROPERTY(TEST EventHandler_test PROPERTY LABELS monte_carlo_estimator_native)

# IF(${FRENSIE_ENABLE_OPENMP})
#   ADD_TEST(SharedParallelEventHandler_2_test
#     tstEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk" --threads=2)
#   ADD_TEST(SharedParallelEventHandler_4_test
#     tstEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk" --threads=4)
#   SET_PROPERTY(TEST SharedParallelEventHandler_2_test PROPERTY LABELS monte_carlo_estimator_native openmp no_threads)
#   SET_PROPERTY(TEST SharedParallelEventHandler_4_test PROPERTY LABELS monte_carlo_estimator_native openmp no_threads)
# ENDIF()

# IF(${FRENSIE_ENABLE_MPI})
#   Add_EXECUTABLE(tstDistributedEventHandler
#     tstDistributedEventHandler.cpp)
#   TARGET_LINK_LIBRARIES(tstDistributedEventHandler monte_carlo_estimator_native ${MOAB})
#   ADD_TEST(DistributedParallelEventHandler_1_test
#     ${MPIEXEC} -n 1 tstDistributedEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")
#   ADD_TEST(DistributedParallelEventHandler_2_test
#     ${MPIEXEC} -n 2 tstDistributedEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")
#   ADD_TEST(DistributedParallelEventHandler_4_test
#     ${MPIEXEC} -n 4 tstDistributedEventHandler --test_input_mesh_file_name="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk")
#   SET_PROPERTY(TEST DistributedParallelEventHandler_1_test PROPERTY LABELS monte_carlo_estimator_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelEventHandler_2_test PROPERTY LABELS monte_carlo_estimator_native mpi no_threads)
#   SET_PROPERTY(TEST DistributedParallelEventHandler_4_test PROPERTY LABELS monte_carlo_estimator_native mpi no_threads)
# ENDIF()

# IF(FRENSIE_ENABLE_DAGMC)
#   ADD_EXECUTABLE(tstEventHandlerFactory_DagMC
#     tstEventHandlerFactory_DagMC.cpp)
#   TARGET_LINK_LIBRARIES(tstEventHandlerFactory_DagMC monte_carlo_estimator_native)
#   ADD_TEST(EventHandlerFactory_DagMC_test tstEventHandlerFactory_DagMC --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_dagmc.xml" --test_resp_func_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_response_functions.xml" --test_observer_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_observers.xml")
#   SET_PROPERTY(TEST EventHandlerFactory_DagMC_test PROPERTY LABELS monte_carlo_estimator_native dagmc)
# ENDIF()

# IF(FRENSIE_ENABLE_ROOT)
#   ADD_EXECUTABLE(tstEventHandlerFactory_Root
#     tstEventHandlerFactory_Root.cpp)
#   TARGET_LINK_LIBRARIES(tstEventHandlerFactory_Root monte_carlo_estimator_native geometry_root)
#   ADD_TEST(EventHandlerFactoryRoot_test tstEventHandlerFactory_Root --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_root.xml" --test_resp_func_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_response_functions.xml" --test_observer_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_observers.xml")
#   SET_PROPERTY(TEST EventHandlerFactoryRoot_test PROPERTY LABELS monte_carlo_estimator_native root)
# ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_event_dispatcher)
