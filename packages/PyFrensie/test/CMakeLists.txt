# Configure the test files
ADD_SUBDIRECTORY(test_files)

# Configure the PyTrilinos utilities (used for setting up unit files)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeCacheVariables.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/CMakeCacheVariables.py)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/MakefileVariables.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/MakefileVariables.py)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/copyWithCMakeSubstitutions.py.in
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

# Add the Utility.Prng unit tests
PyFrensie_MAKE_TEST(tstUtility.Prng)
ADD_TEST(PyFrensie.Utility.Prng_test ${PYTHON_EXECUTABLE} tstUtility.Prng.py)
SET_PROPERTY(TEST PyFrensie.Utility.Prng_test PROPERTY LABELS pyfrensie)

# Add the Utility.Distribution unit tests
PyFrensie_MAKE_TEST(tstUtility.Distribution.UnivariateDistribution)
ADD_TEST(PyFrensie.Utility.Distribution.UnivariateDistribution_test ${PYTHON_EXECUTABLE} tstUtility.Distribution.UnivariateDistribution.py)
SET_PROPERTY(TEST PyFrensie.Utility.Distribution.UnivariateDistribution_test PROPERTY LABELS pyfrensie)

PyFrensie_MAKE_TEST(tstUtility.Distribution.BivariateDistribution)
ADD_TEST(PyFrensie.Utility.Distribution.BivariateDistribution_test ${PYTHON_EXECUTABLE} tstUtility.Distribution.BivariateDistribution.py)
SET_PROPERTY(TEST PyFrensie.Utility.Distribution.BivariateDistribution_test PROPERTY LABELS pyfrensie)

PyFrensie_MAKE_TEST(tstUtility.Coordinate.CartesianCoordinate)
ADD_TEST(PyFrensie.Utility.Coordinate.CartesianCoordinate_test ${PYTHON_EXECUTABLE} tstUtility.Coordinate.CartesianCoordinate.py)
SET_PROPERTY(TEST PyFrensie.Utility.Coordinate.CartesianCoordinate_test PROPERTY LABELS pyfrensie)

PyFrensie_MAKE_TEST(tstUtility.Coordinate.SphericalCoordinate)
ADD_TEST(PyFrensie.Utility.Coordinate.SphericalCoordinate_test ${PYTHON_EXECUTABLE} tstUtility.Coordinate.SphericalCoordinate.py)
SET_PROPERTY(TEST PyFrensie.Utility.Coordinate.SphericalCoordinate_test PROPERTY LABELS pyfrensie)

PyFrensie_MAKE_TEST(tstUtility.Coordinate.CylindricalCoordinate)
ADD_TEST(PyFrensie.Utility.Coordinate.CylindricalCoordinate_test ${PYTHON_EXECUTABLE} tstUtility.Coordinate.CylindricalCoordinate.py)
SET_PROPERTY(TEST PyFrensie.Utility.Coordinate.CylindricalCoordinate_test PROPERTY LABELS pyfrensie)

# Add the Data.AtomProperties unit tests
PyFrensie_MAKE_TEST(tstData.AtomProperties)
ADD_TEST(PyFrensie.Data.AtomProperties_test ${PYTHON_EXECUTABLE} tstData.AtomProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.AtomProperties_test PROPERTY LABELS pyfrensie )

# Add the Data.NuclideProperties unit tests
PyFrensie_MAKE_TEST(tstData.NuclideProperties)
ADD_TEST(PyFrensie.Data.NuclideProperties_test ${PYTHON_EXECUTABLE} tstData.NuclideProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.NuclideProperties_test PROPERTY LABELS pyfrensie )

# Add the Data.ScatteringCenterPropertiesDatabaseImpl unit tests
PyFrensie_MAKE_TEST(tstData.ScatteringCenterPropertiesDatabaseImpl)
ADD_TEST(PyFrensie.Data.ScatteringCenterPropertiesDatabaseImpl_test ${PYTHON_EXECUTABLE} tstData.ScatteringCenterPropertiesDatabaseImpl.py)
SET_PROPERTY(TEST PyFrensie.Data.ScatteringCenterPropertiesDatabaseImpl_test PROPERTY LABELS pyfrensie )

# Add the Data.ScatteringCenterPropertiesDatabase unit tests
PyFrensie_MAKE_TEST(tstData.ScatteringCenterPropertiesDatabase)
ADD_TEST(PyFrensie.Data.ScatteringCenterPropertiesDatabase_test ${PYTHON_EXECUTABLE} tstData.ScatteringCenterPropertiesDatabase.py)
SET_PROPERTY(TEST PyFrensie.Data.ScatteringCenterPropertiesDatabase_test PROPERTY LABELS pyfrensie )

# Add the Data.ACE.ACEElectroatomicDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.ACE.ACEElectroatomicDataProperties)
ADD_TEST(PyFrensie.Data.ACE.ACEElectroatomicDataProperties_test ${PYTHON_EXECUTABLE} tstData.ACE.ACEElectroatomicDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.ACE.ACEElectroatomicDataProperties_test PROPERTY LABELS pyfrensie ace)

# Add the Data.ACE.ACEPhotoatomicDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.ACE.ACEPhotoatomicDataProperties)
ADD_TEST(PyFrensie.Data.ACE.ACEPhotoatomicDataProperties_test ${PYTHON_EXECUTABLE} tstData.ACE.ACEPhotoatomicDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.ACE.ACEPhotoatomicDataProperties_test PROPERTY LABELS pyfrensie ace)

# Add the Data.ACE.ACENuclearDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.ACE.ACENuclearDataProperties)
ADD_TEST(PyFrensie.Data.ACE.ACENuclearDataProperties_test ${PYTHON_EXECUTABLE} tstData.ACE.ACENuclearDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.ACE.ACENuclearDataProperties_test PROPERTY LABELS pyfrensie ace)

# Add the Data.ACE.ACEThermalNuclearDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.ACE.ACEThermalNuclearDataProperties)
ADD_TEST(PyFrensie.Data.ACE.ACEThermalNuclearDataProperties_test ${PYTHON_EXECUTABLE} tstData.ACE.ACEThermalNuclearDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.ACE.ACEThermalNuclearDataProperties_test PROPERTY LABELS pyfrensie ace)

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

# Add the Data.ACE.XSSElectronDataExtractor unit tests
PyFrensie_MAKE_TEST(tstData.ACE.XSSElectronDataExtractor)
ADD_TEST(PyFrensie.Data.ACE.XSSElectronDataExtractor_B_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSElectronDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_b_electron_ace_file.txt --tablename=5000.03e)
SET_PROPERTY(TEST PyFrensie.Data.ACE.XSSElectronDataExtractor_B_test PROPERTY LABELS pyfrensie ace electron)
ADD_TEST(PyFrensie.Data.ACE.XSSElectronDataExtractor_Pb_test ${PYTHON_EXECUTABLE} tstData.ACE.XSSElectronDataExtractor.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_electron_ace_file.txt --tablename=82000.03e)
SET_PROPERTY(TEST PyFrensie.Data.ACE.XSSElectronDataExtractor_Pb_test PROPERTY LABELS pyfrensie ace electron)

# Add the Data.ENDL.ENDLElectroatomicDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.ENDL.ENDLElectroatomicDataProperties)
ADD_TEST(PyFrensie.Data.ENDL.ENDLElectroatomicDataProperties_test ${PYTHON_EXECUTABLE} tstData.ENDL.ENDLElectroatomicDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.ENDL.ENDLElectroatomicDataProperties_test PROPERTY LABELS pyfrensie endl)

# Add the Data.ENDL.ENDLPhotoatomicDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.ENDL.ENDLPhotoatomicDataProperties)
ADD_TEST(PyFrensie.Data.ENDL.ENDLPhotoatomicDataProperties_test ${PYTHON_EXECUTABLE} tstData.ENDL.ENDLPhotoatomicDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.ENDL.ENDLPhotoatomicDataProperties_test PROPERTY LABELS pyfrensie endl)

# Add the Data.ENDL.ENDLDataContainer unit tests
PyFrensie_MAKE_TEST(tstData.ENDL.ENDLDataContainer)
ADD_TEST(PyFrensie.Data.ENDL.ENDLDataContainer_test ${PYTHON_EXECUTABLE} tstData.ENDL.ENDLDataContainer.py --endlfile=${GLOBAL_ENDL_TEST_DATA_SOURCE_DIR}/test_h_endl_native.xml)
SET_PROPERTY(TEST PyFrensie.Data.ENDL.ENDLDataContainer_test PROPERTY LABELS pyfrensie endl)

# Add the Data.Native.NativeEPRElectroatomicDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.Native.NativeEPRElectroatomicDataProperties)
ADD_TEST(PyFrensie.Data.Native.NativeEPRElectroatomicDataProperties_test ${PYTHON_EXECUTABLE} tstData.Native.NativeEPRElectroatomicDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.Native.NativeEPRElectroatomicDataProperties_test PROPERTY LABELS pyfrensie native electron )

# Add the Data.Native.NativeEPRPhotoatomicDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.Native.NativeEPRPhotoatomicDataProperties)
ADD_TEST(PyFrensie.Data.Native.NativeEPRPhotoatomicDataProperties_test ${PYTHON_EXECUTABLE} tstData.Native.NativeEPRPhotoatomicDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.Native.NativeEPRPhotoatomicDataProperties_test PROPERTY LABELS pyfrensie native photon)

# Add the Data.Native.NativeMomentPreservingElectroatomicDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.Native.NativeMomentPreservingElectroatomicDataProperties)
ADD_TEST(PyFrensie.Data.Native.NativeMomentPreservingElectroatomicDataProperties_test ${PYTHON_EXECUTABLE} tstData.Native.NativeMomentPreservingElectroatomicDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.Native.NativeMomentPreservingElectroatomicDataProperties_test PROPERTY LABELS pyfrensie native electron )

# Add the Data.Native.NativeEPRAdjointElectroatomicDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.Native.NativeEPRAdjointElectroatomicDataProperties)
ADD_TEST(PyFrensie.Data.Native.NativeEPRAdjointElectroatomicDataProperties_test ${PYTHON_EXECUTABLE} tstData.Native.NativeEPRAdjointElectroatomicDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.Native.NativeEPRAdjointElectroatomicDataProperties_test PROPERTY LABELS pyfrensie native electron adjoint)

# Add the Data.Native.NativeEPRAdjointPhotoatomicDataProperties unit tests
PyFrensie_MAKE_TEST(tstData.Native.NativeEPRAdjointPhotoatomicDataProperties)
ADD_TEST(PyFrensie.Data.Native.NativeEPRAdjointPhotoatomicDataProperties_test ${PYTHON_EXECUTABLE} tstData.Native.NativeEPRAdjointPhotoatomicDataProperties.py)
SET_PROPERTY(TEST PyFrensie.Data.Native.NativeEPRAdjointPhotoatomicDataProperties_test PROPERTY LABELS pyfrensie native photon adjoint)

# Add the Data.Native.ElectronPhotonRelaxationDataContainer unit tests
PyFrensie_MAKE_TEST(tstData.Native.ElectronPhotonRelaxationDataContainer)
ADD_TEST(PyFrensie.Data.Native.ElectronPhotonRelaxationDataContainer_test ${PYTHON_EXECUTABLE} tstData.Native.ElectronPhotonRelaxationDataContainer.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_6_native.xml)
SET_PROPERTY(TEST PyFrensie.Data.Native.ElectronPhotonRelaxationDataContainer_test PROPERTY LABELS pyfrensie native electron photon)

# Add the Data.Native.AdjointElectronPhotonRelaxationDataContainer unit tests
PyFrensie_MAKE_TEST(tstData.Native.AdjointElectronPhotonRelaxationDataContainer)
ADD_TEST(PyFrensie.Data.Native.AdjointElectronPhotonRelaxationDataContainer_test ${PYTHON_EXECUTABLE} tstData.Native.AdjointElectronPhotonRelaxationDataContainer.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_6_native.xml)
SET_PROPERTY(TEST PyFrensie.Data.Native.AdjointElectronPhotonRelaxationDataContainer_test PROPERTY LABELS pyfrensie native adjoint electron photon)

# Add the Geometry.Ray unit tests
PyFrensie_MAKE_TEST(tstGeometry.Ray)
ADD_TEST(PyFrensie.Geometry.Ray_test ${PYTHON_EXECUTABLE} tstGeometry.Ray.py)
SET_PROPERTY(TEST PyFrensie.Geometry.Ray_test PROPERTY LABELS pyfrensie)

# Add the Geometry.ModelProperties unit tests
IF(FRENSIE_ENABLE_DAGMC OR FRENSIE_ENABLE_ROOT)
  PyFrensie_MAKE_TEST(tstGeometry.ModelProperties)

  IF(FRENSIE_ENABLE_DAGMC)
    ADD_TEST(PyFrensie.Geometry.ModelProperties_DagMC_test ${PYTHON_EXECUTABLE} tstGeometry.ModelProperties.py --dagmc_sat_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.sat)
    SET_PROPERTY(TEST PyFrensie.Geometry.ModelProperties_DagMC_test PROPERTY LABELS pyfrensie dagmc)
  ENDIF()

  IF(FRENSIE_ENABLE_ROOT)
    ADD_TEST(PyFrensie.Geometry.ModelProperties_Root_test ${PYTHON_EXECUTABLE} tstGeometry.ModelProperties.py --root_file=${CMAKE_CURRENT_BINARY_DIR}}/test_files/test_root_geom.root)
    SET_PROPERTY(TEST PyFrensie.Geometry.ModelProperties_Root_test PROPERTY LABLES pyfrensie root)
  ENDIF()
ENDIF()

# Add the Geometry.Model unit tests
IF(FRENSIE_ENABLE_DAGMC OR FRENSIE_ENABLE_ROOT)
  PyFrensie_MAKE_TEST(tstGeometry.Model)

  IF(FRENSIE_ENABLE_DAGMC)
    ADD_TEST(PyFrensie.Geometry.Model_DagMC_test ${PYTHON_EXECUTABLE} tstGeometry.Model.py --dagmc_sat_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.sat)
    SET_PROPERTY(TEST PyFrensie.Geometry.Model_DagMC_test PROPERTY LABELS pyfrensie dagmc)
  ENDIF()

  IF(FRENSIE_ENABLE_ROOT)
    ADD_TEST(PyFrensie.Geometry.Model_Root_test ${PYTHON_EXECUTABLE} tstGeometry.Model.py --root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)
    SET_PROPERTY(TEST PyFrensie.Geometry.Model_Root_test PROPERTY LABLES pyfrensie root)
  ENDIF()
ENDIF()

# Add the Geometry.Navigator unit tests
IF(FRENSIE_ENABLE_DAGMC OR FRENSIE_ENABLE_ROOT)
  PyFrensie_MAKE_TEST(tstGeometry.Navigator)

  IF(FRENSIE_ENABLE_DAGMC)
    ADD_TEST(PyFrensie.Geometry.Navigator_DagMC_test ${PYTHON_EXECUTABLE} tstGeometry.Navigator.py --dagmc_sat_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.sat)
    SET_PROPERTY(TEST PyFrensie.Geometry.Navigator_DagMC_test PROPERTY LABELS pyfrensie dagmc)
  ENDIF()

  IF(FRENSIE_ENABLE_ROOT)
    ADD_TEST(PyFrensie.Geometry.Navigator_Root_test ${PYTHON_EXECUTABLE} tstGeometry.Navigator.py --root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)
    SET_PROPERTY(TEST PyFrensie.Geometry.Navigator_Root_test PROPERTY LABLES pyfrensie root)
  ENDIF()
ENDIF()

# # Add the MonteCarlo.Collision.PhotonKinematics unit tests
# PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.PhotonKinematics)
# ADD_TEST(PyFrensie.MonteCarlo.Collision.PhotonKinematics_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.PhotonKinematics.py)

# # Add the MonteCarlo.Collision.ElectronScatteringNativeDistribution unit tests
# PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.ElectronScatteringNativeDistribution)
# ADD_TEST(PyFrensie.MonteCarlo.Collision.ElectronScatteringNativeDistribution_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.ElectronScatteringNativeDistribution.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)
# SET_PROPERTY(TEST PyFrensie.MonteCarlo.Collision.ElectronScatteringNativeDistribution_test PROPERTY LABELS pyfrensie electron )

# # Add the MonteCarlo.Collision.ElectronScatteringACEDistribution unit tests
# PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.ElectronScatteringACEDistribution)
# ADD_TEST(PyFrensie.MonteCarlo.Collision.ElectronScatteringACEDistribution_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.ElectronScatteringACEDistribution.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h_epr14_ace_file.txt --tablename=1000.14p)
# SET_PROPERTY(TEST PyFrensie.MonteCarlo.Collision.ElectronScatteringACEDistribution_test PROPERTY LABELS pyfrensie electron )

# # Add the MonteCarlo.Collision.AdjointElectronScatteringDistribution unit tests
# PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.AdjointElectronScatteringDistribution)
# ADD_TEST(PyFrensie.MonteCarlo.Collision.AdjointElectronScatteringDistribution_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.AdjointElectronScatteringDistribution.py --adjointfile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)
# SET_PROPERTY(TEST PyFrensie.MonteCarlo.Collision.AdjointElectronScatteringDistribution_test PROPERTY LABELS pyfrensie electron adjoint)

# # Add the MonteCarlo.Collision.ElectroatomicReaction unit tests
# PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.ElectroatomicReaction)
# ADD_TEST(PyFrensie.MonteCarlo.Collision.ElectroatomicReaction_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.ElectroatomicReaction.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml )
# SET_PROPERTY(TEST PyFrensie.MonteCarlo.Collision.ElectroatomicReaction_test PROPERTY LABELS pyfrensie electron )

# # Add the adjoint MonteCarlo.Collision.ElectroatomicReaction unit tests
# PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.AdjointElectroatomicReaction)
# ADD_TEST(PyFrensie.MonteCarlo.Collision.AdjointElectroatomicReaction_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.AdjointElectroatomicReaction.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml )
# SET_PROPERTY(TEST PyFrensie.MonteCarlo.Collision.AdjointElectroatomicReaction_test PROPERTY LABELS pyfrensie electron )


