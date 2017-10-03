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
SET_PROPERTY(TEST PyFrensie.Utility.Distribution.OneDDistribution_test PROPERTY LABELS pyfrensie)

# Add the Utility.Prng unit tests
PyFrensie_MAKE_TEST(tstUtility.Prng)
ADD_TEST(PyFrensie.Utility.Prng_test ${PYTHON_EXECUTABLE} tstUtility.Prng.py)
SET_PROPERTY(TEST PyFrensie.Utility.Prng_test PROPERTY LABELS pyfrensie)

# Add the Data.ACE.ACEFileHandler unit tests
PyFrensie_MAKE_TEST(tstData.ACE.ACEFileHandler)
ADD_TEST(PyFrensie.Data.ACE.ACEFileHandler_test ${PYTHON_EXECUTABLE} tstData.ACE.ACEFileHandler.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt --tablename=1001.70c)
SET_PROPERTY(TEST PyFrensie.Data.ACE.ACEFileHandler_test PROPERTY LABELS pyfrensie ace)

# Add the Data.ACE.XSSNeutronDataExtractor unit tests
PyFrensie_MAKE_TEST(tstData.ACE.XSSNeutronDataExtractor)
ADD_TEST(PyFrensie.Data.ACE.XSSNeutronDataExtractor_H1_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSNeutronDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt --tablename=1001.70c)
SET_PROPERTY(TEST PyFrensie.Data.ACE.XSSNeutronDataExtractor_H1_test PROPERTY LABELS pyfrensie ace neutron)
ADD_TEST(PyFrensie.Data.ACE.XSSNeutronDataExtractor_U238_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSNeutronDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_u238_ace_file.txt --tablename=92238.70c)
SET_PROPERTY(TEST PyFrensie.Data.ACE.XSSNeutronDataExtractor_U238_test PROPERTY LABELS pyfrensie ace neutron)

# Add the Data.ACE.XSSEPRDataExtractor unit tests
PyFrensie_MAKE_TEST(tstData.ACE.XSSEPRDataExtractor)
ADD_TEST(PyFrensie.Data.ACE.XSSEPRDataExtractor_B_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSEPRDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_b_epr_ace_file.txt --tablename=5000.12p)
SET_PROPERTY(TEST PyFrensie.Data.ACE.XSSEPRDataExtractor_B_test PROPERTY LABELS pyfrensie ace electron photon neutron)
ADD_TEST(PyFrensie.Data.ACE.XSSEPRDataExtractor_Pb_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSEPRDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt --tablename=82000.12p)
SET_PROPERTY(TEST PyFrensie.Data.ACE.XSSEPRDataExtractor_Pb_test PROPERTY LABELS pyfrensie ace electron photon neutron)
ADD_TEST(PyFrensie.Data.ACE.XSSEPRDataExtractor_epr14_Pb_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSEPRDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt --tablename=82000.14p)
SET_PROPERTY(TEST PyFrensie.Data.ACE.XSSEPRDataExtractor_epr14_Pb_test PROPERTY LABELS pyfrensie ace14 electron photon neutron)

# Add the Geometry.Ray unit tests
PyFrensie_MAKE_TEST(tstGeometry.Ray)
ADD_TEST(PyFrensie.Geometry.Ray_test ${PYTHON_EXECUTABLE} tstGeometry.Ray.py)
SET_PROPERTY(TEST PyFrensie.Geometry.Ray_test PROPERTY LABELS pyfrensie)

# Add the Geometry.DagMC.DagMC unit tests
IF(FRENSIE_ENABLE_DAGMC)
  PyFrensie_MAKE_TEST(tstGeometry.DagMC.DagMC)
  ADD_TEST(PyFrensie.Geometry.DagMC.DagMC_test ${PYTHON_EXECUTABLE} tstGeometry.DagMC.DagMC.py --cadfile=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_geom.sat)
  SET_PROPERTY(TEST PyFrensie.Geometry.DagMC.DagMC_test PROPERTY LABELS pyfrensie dagmc)

  # Add the Geometry.DagMC.initializeDagMC unit tests
  PyFrensie_MAKE_TEST(tstGeometry.DagMC.initializeDagMC)
  ADD_TEST(PyFrensie.Geometry.DagMC.initializeDagMC_test ${PYTHON_EXECUTABLE} tstGeometry.DagMC.initializeDagMC.py --xmlfile=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml)
  SET_PROPERTY(TEST PyFrensie.Geometry.DagMC.initializeDagMC_test PROPERTY LABELS pyfrensie dagmc)
ENDIF(FRENSIE_ENABLE_DAGMC)

# Add the Geometry.ROOT.Root unit tests
IF(FRENSIE_ENABLE_ROOT)
  PyFrensie_MAKE_TEST(tstGeometry.ROOT.Root)
  ADD_TEST(PyFrensie.Geometry.ROOT.Root_test ${PYTHON_EXECUTABLE} tstGeometry.ROOT.Root.py --rootfile=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)
  SET_PROPERTY(TEST PyFrensie.Geometry.ROOT.Root_test PROPERTY LABELS pyfrensie root)

  # Add the Geometry.ROOT.initializeRoot unit tests
  PyFrensie_MAKE_TEST(tstGeometry.ROOT.initializeRoot)
  ADD_TEST(PyFrensie.Geometry.ROOT.initializeRoot_test ${PYTHON_EXECUTABLE} tstGeometry.ROOT.initializeRoot.py --xmlfile=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.xml)
  SET_PROPERTY(TEST PyFrensie.Geometry.ROOT.initializeRoot_test PROPERTY LABELS pyfrensie root)
ENDIF(FRENSIE_ENABLE_ROOT)

# Add the MonteCarlo.Collision.PhotonKinematics unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.PhotonKinematics)
ADD_TEST(PyFrensie.MonteCarlo.Collision.PhotonKinematics_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.PhotonKinematics.py)

# Add the MonteCarlo.Collision.ElectronScatteringNativeDistribution unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.ElectronScatteringNativeDistribution)
ADD_TEST(PyFrensie.MonteCarlo.Collision.ElectronScatteringNativeDistribution_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.ElectronScatteringNativeDistribution.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)
SET_PROPERTY(TEST PyFrensie.MonteCarlo.Collision.ElectronScatteringNativeDistribution_test PROPERTY LABELS pyfrensie electron )

# Add the MonteCarlo.Collision.ElectronScatteringACEDistribution unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.ElectronScatteringACEDistribution)
ADD_TEST(PyFrensie.MonteCarlo.Collision.ElectronScatteringACEDistribution_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.ElectronScatteringACEDistribution.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h_epr14_ace_file.txt --tablename=1000.14p)
SET_PROPERTY(TEST PyFrensie.MonteCarlo.Collision.ElectronScatteringACEDistribution_test PROPERTY LABELS pyfrensie electron )

# Add the MonteCarlo.Collision.AdjointElectronScatteringDistribution unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.AdjointElectronScatteringDistribution)
ADD_TEST(PyFrensie.MonteCarlo.Collision.AdjointElectronScatteringDistribution_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.AdjointElectronScatteringDistribution.py --adjointfile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)
SET_PROPERTY(TEST PyFrensie.MonteCarlo.Collision.AdjointElectronScatteringDistribution_test PROPERTY LABELS pyfrensie electron adjoint)

# Add the MonteCarlo.Collision.ElectroatomicReaction unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.ElectroatomicReaction)
ADD_TEST(PyFrensie.MonteCarlo.Collision.ElectroatomicReaction_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.ElectroatomicReaction.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml )
SET_PROPERTY(TEST PyFrensie.MonteCarlo.Collision.ElectroatomicReaction_test PROPERTY LABELS pyfrensie electron )

# Add the adjoint MonteCarlo.Collision.ElectroatomicReaction unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.AdjointElectroatomicReaction)
ADD_TEST(PyFrensie.MonteCarlo.Collision.AdjointElectroatomicReaction_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.AdjointElectroatomicReaction.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml )
SET_PROPERTY(TEST PyFrensie.MonteCarlo.Collision.AdjointElectroatomicReaction_test PROPERTY LABELS pyfrensie electron )


