ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstDagMCProperties
  tstDagMCProperties.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDagMCProperties geometry_core geometry_dagmc)
ADD_TEST(DagMCProperties_test tstDagMCProperties)

ADD_EXECUTABLE(tstDagMCHelpers
  tstDagMCHelpers.cpp)
TARGET_LINK_LIBRARIES(tstDagMCHelpers geometry_core geometry_dagmc)
ADD_TEST(DagMCHelpers_test tstDagMCHelpers --test_sat_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat")

ADD_EXECUTABLE(tstDagMCInstanceFactoryBasic
  tstDagMCInstanceFactoryBasic.cpp)
TARGET_LINK_LIBRARIES(tstDagMCInstanceFactoryBasic geometry_core geometry_dagmc)
ADD_TEST(DagMCInstanceFactoryBasic_test tstDagMCInstanceFactoryBasic --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_basic.xml")

ADD_EXECUTABLE(tstDagMCInstanceFactoryAdvanced
  tstDagMCInstanceFactoryAdvanced.cpp)
TARGET_LINK_LIBRARIES(tstDagMCInstanceFactoryAdvanced geometry_core geometry_dagmc)
ADD_TEST(DagMCInstanceFactoryAdvanced_test tstDagMCInstanceFactoryAdvanced --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")

ADD_EXECUTABLE(tstGeometryModuleInterface_DagMC
  tstModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstGeometryModuleInterface_DagMC geometry_core geometry_dagmc ${MPI_CXX_LIBRARIES})
ADD_TEST(GeometryModuleInterface_DagMC_test tstGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelGeometryModuleInterface_DagMC_2_test
    tstGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml" --threads=2)
  ADD_TEST(SharedParallelGeometryModuleInterface_DagMC_4_test
    tstGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml" --threads=4)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  ADD_TEST(DistributedParallelGeometryModuleInterface_DagMC_2_test 
    ${MPIEXEC} -n 2 tstGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")
  ADD_TEST(DistributedParallelGeometryModuleInterface_DagMC_4_test
    ${MPIEXEC} -n 4 tstGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml")
ENDIF()

IF(${FRENSIE_ENABLE_OPENMP} AND ${FRENSIE_ENABLE_MPI})
  ADD_TEST(HybridParallelGeometryModuleInterface_DagMC_2_2_test
    ${MPIEXEC} -n 2 tstGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml" --threads=2)
  ADD_TEST(HybridParallelGeometryModuleInterface_DagMC_4_4_test
    ${MPIEXEC} -n 4 tstGeometryModuleInterface_DagMC --test_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_advanced.xml" --threads=4)
ENDIF()
