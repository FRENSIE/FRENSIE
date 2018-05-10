FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_collision_kernel)

FRENSIE_ADD_TEST_EXECUTABLE(FilledGeometryModel
  DEPENDS tstFilledGeometryModel.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(FilledGeometryModel
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

IF(FRENSIE_ENABLE_DAGMC)

ELSEIF(FRENSIE_ENABLE_ROOT)

ENDIF()

ADD_EXECUTABLE(tstPhotonCollisionHandler
  tstPhotonCollisionHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhotonCollisionHandler monte_carlo_collision_native)
ADD_TEST(PhotonCollisionHandler_test tstPhotonCollisionHandler --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}/")
SET_PROPERTY(TEST PhotonCollisionHandler_test PROPERTY LABELS photon)

ADD_EXECUTABLE(tstAdjointPhotonCollisionHandler
  tstAdjointPhotonCollisionHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAdjointPhotonCollisionHandler monte_carlo_collision_native)
ADD_TEST(AdjointPhotonCollisionHandler_test tstAdjointPhotonCollisionHandler --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}")
SET_PROPERTY(TEST AdjointPhotonCollisionHandler_test PROPERTY LABELS photon adjoint native)

ADD_EXECUTABLE(tstElectronCollisionHandler
  tstElectronCollisionHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectronCollisionHandler monte_carlo_collision_native)
ADD_TEST(ElectronCollisionHandler_test tstElectronCollisionHandler --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}/")
SET_PROPERTY(TEST ElectronCollisionHandler_test PROPERTY LABELS electron)

ADD_EXECUTABLE(tstPositronCollisionHandler
  tstPositronCollisionHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronCollisionHandler monte_carlo_collision_native)
ADD_TEST(PositronCollisionHandler_test tstPositronCollisionHandler --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}/")
SET_PROPERTY(TEST PositronCollisionHandler_test PROPERTY LABELS positron)

ADD_EXECUTABLE(tstAdjointElectronCollisionHandler
  tstAdjointElectronCollisionHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAdjointElectronCollisionHandler monte_carlo_collision_native)
ADD_TEST(AdjointElectronCollisionHandler_test tstAdjointElectronCollisionHandler --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}")
SET_PROPERTY(TEST AdjointElectronCollisionHandler_test PROPERTY LABELS electron adjoint native)

ADD_EXECUTABLE(tstNeutronCollisionHandler
  tstNeutronCollisionHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstNeutronCollisionHandler monte_carlo_collision_native)
ADD_TEST(NeutronCollisionHandler_test tstNeutronCollisionHandler --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}")
SET_PROPERTY(TEST NeutronCollisionHandler_test PROPERTY LABELS neutron)

ADD_EXECUTABLE(tstCollisionHandler
  tstCollisionHandler.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstCollisionHandler monte_carlo_collision_native)
ADD_TEST(CollisionHandler_test tstCollisionHandler --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}")
SET_PROPERTY(TEST CollisionHandler_test PROPERTY LABELS handler)

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstCollisionHandlerFactory_DagMC
    tstCollisionHandlerFactory_DagMC.cpp
    ${FRENSIE_STD_UNIT_TEST_MAIN})
  TARGET_LINK_LIBRARIES(tstCollisionHandlerFactory_DagMC monte_carlo_collision_native)
  ADD_TEST(CollisionHandlerFactory_DagMC_test tstCollisionHandlerFactory_DagMC --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}" --test_forward_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material_forward.xml" --test_adjoint_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material_adjoint.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
  SET_PROPERTY(TEST CollisionHandlerFactory_DagMC_test PROPERTY LABELS dagmc)
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  ADD_EXECUTABLE(tstCollisionHandlerFactory_Root
    tstCollisionHandlerFactory_Root.cpp
    ${FRENSIE_STD_UNIT_TEST_MAIN})
  TARGET_LINK_LIBRARIES(tstCollisionHandlerFactory_Root monte_carlo_collision_native)
  ADD_TEST(CollisionHandlerFactory_Root_test tstCollisionHandlerFactory_Root --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}" --test_forward_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material_forward.xml" --test_adjoint_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material_adjoint.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_root.xml")
  SET_PROPERTY(TEST CollisionHandlerFactory_Root_test PROPERTY LABELS root)
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstCollisionModuleInterface_Native_DagMC
    tstModuleInterface_DagMC.cpp
    ${FRENSIE_STD_UNIT_TEST_MAIN})
  TARGET_LINK_LIBRARIES(tstCollisionModuleInterface_Native_DagMC monte_carlo_collision_native)
  ADD_TEST(CollisionModuleInterface_Native_DagMC_test tstCollisionModuleInterface_Native_DagMC --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material_forward.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
  SET_PROPERTY(TEST CollisionModuleInterface_Native_DagMC_test PROPERTY LABELS dagmc native)
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_collision_kernel)
