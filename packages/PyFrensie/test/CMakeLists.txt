# Configure the test files
ADD_SUBDIRECTORY(test_files)

# Configure the PyTrilinos utilities (used for setting up unit files)
CONFIGURE_FILE(${PYTRILINOS_UTIL_DIR_PATH}/CMakeCacheVariables.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/CMakeCacheVariables.py)

CONFIGURE_FILE(${PYTRILINOS_UTIL_DIR_PATH}/MakefileVariables.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/MakefileVariables.py)

CONFIGURE_FILE(${PYTRILINOS_UTIL_DIR_PATH}/copyWithCMakeSubstitutions.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/copyWithCMakeSubstitutions.py)

# Include the PyFrensieMakeTest macro
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/PyFrensieMakeTest.cmake)

# Add the testHelpers module to the unit test directory
ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/testutil.py
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/copyWithCMakeSubstitutions.py
          ${CMAKE_CURRENT_SOURCE_DIR}/testingHelpers.py.in
	  ${CMAKE_CURRENT_BINARY_DIR}/testingHelpers.py
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/testingHelpers.py.in)

ADD_CUSTOM_TARGET(testingHelpers ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/testutil.py)

# Add the Utility.Distribution unit tests
PyFrensie_MAKE_TEST(tstUtility.Distribution.OneDDistribution)
ADD_TEST(PyFrensie.Utility.Distribution.OneDDistribution_test ${PYTHON_EXECUTABLE} tstUtility.Distribution.OneDDistribution.py)

# Add the Utility.Prng unit tests
PyFrensie_MAKE_TEST(tstUtility.Prng)
ADD_TEST(PyFrensie.Utility.Prng_test ${PYTHON_EXECUTABLE} tstUtility.Prng.py)

# Add the Data.ACE.ACEFileHandler unit tests
PyFrensie_MAKE_TEST(tstData.ACE.ACEFileHandler)
ADD_TEST(PyFrensie.Data.ACE.ACEFileHandler_test ${PYTHON_EXECUTABLE} tstData.ACE.ACEFileHandler.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt --tablename=1001.70c)

# Add the Data.ACE.XSSNeutronDataExtractor unit tests
PyFrensie_MAKE_TEST(tstData.ACE.XSSNeutronDataExtractor)
ADD_TEST(PyFrensie.Data.ACE.XSSNeutronDataExtractor_H1_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSNeutronDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt --tablename=1001.70c)
ADD_TEST(PyFrensie.Data.ACE.XSSNeutronDataExtractor_U238_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSNeutronDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_u238_ace_file.txt --tablename=92238.70c)

# Add the Data.ACE.XSSEPRDataExtractor unit tests
PyFrensie_MAKE_TEST(tstData.ACE.XSSEPRDataExtractor)
ADD_TEST(PyFrensie.Data.ACE.XSSEPRDataExtractor_B_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSEPRDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_b_epr_ace_file.txt --tablename=5000.12p)
ADD_TEST(PyFrensie.Data.ACE.XSSEPRDataExtractor_Pb_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSEPRDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt --tablename=82000.12p)

# Add the Geometry.Ray unit tests
PyFrensie_MAKE_TEST(tstGeometry.Ray)
ADD_TEST(PyFrensie.Geometry.Ray_test ${PYTHON_EXECUTABLE} tstGeometry.Ray.py)

# Add the Geometry.DagMC.DagMC unit tests
IF(FRENSIE_ENABLE_DAGMC)
  PyFrensie_MAKE_TEST(tstGeometry.DagMC.DagMC)
  ADD_TEST(PyFrensie.Geometry.DagMC.DagMC_test ${PYTHON_EXECUTABLE} tstGeometry.DagMC.DagMC.py --cadfile=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat)

  # Add the Geometry.DagMC.initializeDagMC unit tests
  PyFrensie_MAKE_TEST(tstGeometry.DagMC.initializeDagMC)
  ADD_TEST(PyFrensie.Geometry.DagMC.initializeDagMC_test ${PYTHON_EXECUTABLE} tstGeometry.DagMC.initializeDagMC.py --xmlfile=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml)
ENDIF(FRENSIE_ENABLE_DAGMC)

# Add the Geometry.ROOT.Root unit tests
IF(FRENSIE_ENABLE_ROOT)
  PyFrensie_MAKE_TEST(tstGeometry.ROOT.Root)
  ADD_TEST(PyFrensie.Geometry.ROOT.Root_test ${PYTHON_EXECUTABLE} tstGeometry.ROOT.Root.py --rootfile=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)

  # Add the Geometry.ROOT.initializeRoot unit tests
  PyFrensie_MAKE_TEST(tstGeometry.ROOT.initializeRoot)
  ADD_TEST(PyFrensie.Geometry.ROOT.initializeRoot_test ${PYTHON_EXECUTABLE} tstGeometry.ROOT.initializeRoot.py --xmlfile=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.xml)
ENDIF(FRENSIE_ENABLE_ROOT)

# Add the MonteCarlo.Collision.PhotonKinematics unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.PhotonKinematics)
ADD_TEST(PyFrensie.MonteCarlo.Collision.PhotonKinematics_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.PhotonKinematics.py)
