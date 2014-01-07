SET(SRC ${CMAKE_SOURCE_DIR}/src)

ADD_EXECUTABLE(tstAssertion 
  tstAssertion.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstContractException 
  tstContractException.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstENDLIB97FileHandler
  tstENDLIB97FileHandler.cpp
  ${SRC}/ENDLIB97FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstHDF5FileHandler
  tstHDF5FileHandler.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstDataProcessor
  tstDataProcessor.cpp
  ${SRC}/DataProcessor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataProcessorShellMap
  tstPhotonDataProcessorShellMap.cpp
  ${SRC}/DataProcessor.cpp
  ${SRC}/ENDLIB97FileHandler.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${SRC}/PhotonDataProcessor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataProcessor
  tstPhotonDataProcessor.cpp
  ${SRC}/DataProcessor.cpp
  ${SRC}/ENDLIB97FileHandler.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${SRC}/PhotonDataProcessor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstSearchAlgorithms
  tstSearchAlgorithms.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataBasic
  tstPhotonDataBasic.cpp
  ${SRC}/PhotonDataBasic.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataFluorescence
  tstPhotonDataFluorescence.cpp
  ${SRC}/PhotonDataFluorescence.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataDopplerBroadening
  tstPhotonDataDopplerBroadening.cpp
  ${SRC}/PhotonDataDopplerBroadening.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonData
  tstPhotonData.cpp
  ${SRC}/PhotonDataBasic.cpp
  ${SRC}/PhotonDataFluorescence.cpp
  ${SRC}/PhotonDataDopplerBroadening.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstMatrix
  tstMatrix.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstVector
  tstVector.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstVectorHelpers
  tstVectorHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstMatrixHelpers
  tstMatrixHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstLinearAlgebraAlgorithms
  tstLinearAlgebraAlgorithms.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstSurface
  tstSurface.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstSetOperationFunctor
  tstSetOperationFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstBooleanCellFunctor
  tstBooleanCellFunctor.cpp
  ${SRC}/BooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstCell
  tstCell.cpp
  ${SRC}/BooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstIntersectionPoint
  tstIntersectionPoint.cpp
  ${SRC}/BooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstIntersectionPointHelpers
  tstIntersectionPointHelpers.cpp
  ${SRC}/BooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPolygon
  tstPolygon.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstCellPolygonFactory
  tstCellPolygonFactory.cpp
  ${SRC}/BooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstCellFactory
  tstCellFactory.cpp
  ${SRC}/BooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstLinearCongruentialGenerator
  tstLinearCongruentialGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstRandomNumberGenerator
  tstRandomNumberGenerator.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstCellBoundingBox
  tstCellBoundingBox.cpp
  ${SRC}/BooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})

TARGET_LINK_LIBRARIES(tstAssertion ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstContractException ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstENDLIB97FileHandler ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstHDF5FileHandler ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstDataProcessor ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstPhotonDataProcessorShellMap ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonDataProcessor ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstSearchAlgorithms ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstPhotonDataBasic ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonDataFluorescence ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonDataDopplerBroadening ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonData ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstMatrix ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstVector ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstVectorHelpers ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstMatrixHelpers ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstLinearAlgebraAlgorithms ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstSurface ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstSetOperationFunctor ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstBooleanCellFunctor ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstCell ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstIntersectionPoint ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstIntersectionPointHelpers ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstPolygon ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstCellPolygonFactory ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstCellFactory ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstLinearCongruentialGenerator ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstRandomNumberGenerator ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstCellBoundingBox ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
IF(${FACEMC_ENABLE_MPI} AND (${CMAKE_BUILD_TYPE} MATCHES "RELEASE") )
  TARGET_LINK_LIBRARIES(tstRandomNumberGenerator ${SPRNG} ${MPI_CXX_LIBRARIES})
  TARGET_LINK_LIBRARIES(tstCellBoundingBox ${SPRNG} ${MPI_CXX_LIBRARIES})
ELSEIF(${FACEMC_ENABLE_MPI} AND (${CMAKE_BUILD_TYPE} MATCHES "DEBUG") )
  TARGET_LINK_LIBRARIES(tstRandomNumberGenerator ${MPI_CXX_LIBRARIES})
  TARGET_LINK_LIBRARIES(tstCellBoundingBox ${MPI_CXX_LIBRARIES})
ELSE()
  TARGET_LINK_LIBRARIES(tstRandomNumberGenerator ${SPRNG})
  TARGET_LINK_LIBRARIES(tstCellBoundingBox ${SPRNG})
ENDIF()  

ADD_TEST(Assertion_test tstAssertion)
ADD_TEST(ContractException_test tstContractException)
ADD_TEST(ENDLIB97FileHandler_test tstENDLIB97FileHandler)
ADD_TEST(HDF5FileHandler_test tstHDF5FileHandler)
ADD_TEST(DataProcessor_test tstDataProcessor)
ADD_TEST(PhotonDataProcessorShellMap_test tstPhotonDataProcessorShellMap)
ADD_TEST(PhotonDataProcessor_test tstPhotonDataProcessor)
ADD_TEST(SearchAlgorithms_test tstSearchAlgorithms)
ADD_TEST(PhotonDataBasic_test tstPhotonDataBasic)
ADD_TEST(PhotonDataFluorescence_test tstPhotonDataFluorescence)
ADD_TEST(PhotonDataDopplerBroadening_test tstPhotonDataDopplerBroadening)
ADD_TEST(PhotonData_test tstPhotonData)
ADD_TEST(Matrix_test tstMatrix)
ADD_TEST(Vector_test tstVector)
ADD_TEST(VectorHelpers_test tstVectorHelpers)
ADD_TEST(MatrixHelpers_test tstMatrixHelpers)
ADD_TEST(LinearAlgebraAlgorithms_test tstLinearAlgebraAlgorithms)
ADD_TEST(Surface_test tstSurface)
ADD_TEST(SetOperationFunctor_test tstSetOperationFunctor)
ADD_TEST(BooleanCellFunctor_test tstBooleanCellFunctor)
ADD_TEST(Cell_test tstCell)
ADD_TEST(IntersectionPoint_test tstIntersectionPoint)
ADD_TEST(IntersectionPointHelpers_test tstIntersectionPointHelpers)
ADD_TEST(Polygon_test tstPolygon)
ADD_TEST(CellPolygonFactory_test tstCellPolygonFactory)
ADD_TEST(CellFactory_test tstCellFactory)
ADD_TEST(LinearCongruentialGenerator_test tstLinearCongruentialGenerator)
ADD_TEST(RandomNumberGenerator_test tstRandomNumberGenerator)
IF(${FACEMC_ENABLE_MPI})
  ADD_TEST(ParallelRandomNumberGenerator_test 
    mpiexec -n 2 tstRandomNumberGenerator)
ENDIF()
ADD_TEST(CellBoundingBox_test tstCellBoundingBox)

# Install test files for the EPDL97DataProcessor_test
FILE(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test_files/*.txt)
MESSAGE("TEST_FILES = ${TEST_FILES}")
INSTALL(FILES ${TEST_FILES}
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)