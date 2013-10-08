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
ADD_EXECUTABLE(tstBinarySearch
  tstBinarySearch.cpp
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
ADD_EXECUTABLE(tstThreeSpaceTraitsAndPolicy
  tstThreeSpaceTraitsAndPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstLinearAlgebraPolicy
  tstLinearAlgebraPolicy.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstSurface
  tstSurface.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPolygon
  tstPolygon.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstSetOperationFunctor
  tstSetOperationFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstBooleanCellFunctor
  tstBooleanCellFunctor.cpp
  ${SRC}/BooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
# ADD_EXECUTABLE(tstCell
#   tstCell.cpp
#   ${SRC}/Cell.cpp
#   ${SRC}/BooleanCellFunctor.cpp
#   ${SRC}/LinearAlgebraAlgorithms.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# ADD_EXECUTABLE(tstConvexPolyhedralCell
#   tstConvexPolyhedralCell.cpp
#   ${SRC}/Cell.cpp
#   ${SRC}/BooleanCellFunctor.cpp
#   ${SRC}/Surface.cpp
#   ${SRC}/LinearAlgebraAlgorithms.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# ADD_EXECUTABLE(tstConcavePolyhedralCell
#   tstConcavePolyhedralCell.cpp
#   ${SRC}/Cell.cpp
#   ${SRC}/BooleanCellFunctor.cpp
#   ${SRC}/Surface.cpp
#   ${SRC}/LinearAlgebraAlgorithms.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# ADD_EXECUTABLE(tstCompoundConvexPolyhedralCell
#   tstCompoundConvexPolyhedralCell.cpp
#   ${SRC}/Cell.cpp
#   ${SRC}/BooleanCellFunctor.cpp
#   ${SRC}/Surface.cpp
#   ${SRC}/LinearAlgebraAlgorithms.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})
# ADD_EXECUTABLE(tstDisjointConvexPolyhedralCell
#   tstDisjointConvexPolyhedralCell.cpp
#   ${SRC}/Cell.cpp
#   ${SRC}/BooleanCellFunctor.cpp
#   ${SRC}/Surface.cpp
#   ${SRC}/LinearAlgebraAlgorithms.cpp
#   ${TEUCHOS_STD_UNIT_TEST_MAIN})

TARGET_LINK_LIBRARIES(tstAssertion ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstContractException ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstENDLIB97FileHandler ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstHDF5FileHandler ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstDataProcessor ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstPhotonDataProcessorShellMap ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonDataProcessor ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstBinarySearch ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstPhotonDataBasic ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonDataFluorescence ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonDataDopplerBroadening ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonData ${TEUCHOS_CORE} ${HDF5})
TARGET_LINK_LIBRARIES(tstThreeSpaceTraitsAndPolicy ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstLinearAlgebraPolicy ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstSurface ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstPolygon ${TEUCHOS_CORE} ${TEUCHOS_NUMERICS} ${BLAS} ${LAPACK})
TARGET_LINK_LIBRARIES(tstSetOperationFunctor ${TEUCHOS_CORE})
TARGET_LINK_LIBRARIES(tstBooleanCellFunctor ${TEUCHOS_CORE})
# TARGET_LINK_LIBRARIES(tstCell ${TEUCHOS})
# TARGET_LINK_LIBRARIES(tstConvexPolyhedralCell ${TEUCHOS})
# TARGET_LINK_LIBRARIES(tstConcavePolyhedralCell ${TEUCHOS})
# TARGET_LINK_LIBRARIES(tstCompoundConvexPolyhedralCell ${TEUCHOS})
# TARGET_LINK_LIBRARIES(tstDisjointConvexPolyhedralCell ${TEUCHOS})

ADD_TEST(Assertion_test tstAssertion)
ADD_TEST(ContractException_test tstContractException)
ADD_TEST(ENDLIB97FileHandler_test tstENDLIB97FileHandler)
ADD_TEST(HDF5FileHandler_test tstHDF5FileHandler)
ADD_TEST(DataProcessor_test tstDataProcessor)
ADD_TEST(PhotonDataProcessorShellMap_test tstPhotonDataProcessorShellMap)
ADD_TEST(PhotonDataProcessor_test tstPhotonDataProcessor)
ADD_TEST(BinarySearch_test tstBinarySearch)
ADD_TEST(PhotonDataBasic_test tstPhotonDataBasic)
ADD_TEST(PhotonDataFluorescence_test tstPhotonDataFluorescence)
ADD_TEST(PhotonDataDopplerBroadening_test tstPhotonDataDopplerBroadening)
ADD_TEST(PhotonData_test tstPhotonData)
ADD_TEST(ThreeSpaceTraitsAndPolicy_test tstThreeSpaceTraitsAndPolicy)
ADD_TEST(LinearAlgebraPolicy_test tstLinearAlgebraPolicy)
ADD_TEST(Surface_test tstSurface)
ADD_TEST(Polygon_test tstPolygon)
ADD_TEST(SetOperationFunctor_test tstSetOperationFunctor)
ADD_TEST(BooleanCellFunctor_test tstBooleanCellFunctor)
# ADD_TEST(Cell_test tstCell)
# ADD_TEST(ConvexPolyhedralCell_test tstConvexPolyhedralCell)
# ADD_TEST(ConcavePolyhedralCell_test tstConcavePolyhedralCell)
# ADD_TEST(CompoundConvexPolyhedralCell tstCompoundConvexPolyhedralCell)
# ADD_TEST(DisjointConvexPolyhedralCell tstDisjointConvexPolyhedralCell)

# Install test files for the EPDL97DataProcessor_test
FILE(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test_files/*.txt)
MESSAGE("TEST_FILES = ${TEST_FILES}")
INSTALL(FILES ${TEST_FILES}
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)