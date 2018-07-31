FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_event_dispatcher)

SET(ROOT_GEOM_TEST_TARGET monte_carlo_event_dispatcher_test_root_geometry)

ADD_SUBDIRECTORY(test_files)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(ParticleCollidingInCellEventLocalDispatcher DEPENDS
  tstParticleCollidingInCellEventLocalDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleCollidingInCellEventLocalDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleCollidingInCellEventDispatcher DEPENDS tstParticleCollidingInCellEventDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleCollidingInCellEventDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleCrossingSurfaceEventLocalDispatcher DEPENDS tstParticleCrossingSurfaceEventLocalDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleCrossingSurfaceEventLocalDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleCrossingSurfaceEventDispatcher DEPENDS tstParticleCrossingSurfaceEventDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleCrossingSurfaceEventDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleEnteringCellEventLocalDispatcher DEPENDS tstParticleEnteringCellEventLocalDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleEnteringCellEventLocalDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleEnteringCellEventDispatcher DEPENDS tstParticleEnteringCellEventDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleEnteringCellEventDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleLeavingCellEventLocalDispatcher DEPENDS tstParticleLeavingCellEventLocalDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleLeavingCellEventLocalDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleLeavingCellEventDispatcher DEPENDS tstParticleLeavingCellEventDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleLeavingCellEventDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleSubtrackEndingInCellEventLocalDispatcher DEPENDS tstParticleSubtrackEndingInCellEventLocalDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleSubtrackEndingInCellEventLocalDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleSubtrackEndingInCellEventDispatcher DEPENDS tstParticleSubtrackEndingInCellEventDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleSubtrackEndingInCellEventDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleSubtrackEndingGlobalEventDispatcher DEPENDS tstParticleSubtrackEndingGlobalEventDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleSubtrackEndingGlobalEventDispatcher)

FRENSIE_ADD_TEST_EXECUTABLE(ParticleGoneGlobalEventDispatcher DEPENDS tstParticleGoneGlobalEventDispatcher.cpp)
FRENSIE_ADD_TEST(ParticleGoneGlobalEventDispatcher)

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
