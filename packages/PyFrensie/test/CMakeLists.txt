# Configure the test files
SET(ROOT_GEOM_TEST_TARGET pyfrensie_test_root_geometry)
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

# Add the Utility logging unit tests
PyFrensie_MAKE_TEST(tstUtility.Logging)
ADD_TEST(PyFrensie.Utility.Logging_test tstUtility.Logging.py)
SET_PROPERTY(TEST PyFrensie.Utility.Logging_test PROPERTY LABELS pyfrensie)

# Add the Utility arrayFromString unit tests
PyFrensie_MAKE_TEST(tstUtility.ArrayFromString)
ADD_TEST(PyFrensie.Utility.ArrayFromString_test tstUtility.ArrayFromString.py)
SET_PROPERTY(TEST PyFrensie.Utility.ArrayFromString_test PROPERTY LABELS pyfrensie)

IF(HAVE_FRENSIE_MPI)
  # Add the Utility_GlobalMPISession unit tests
  PyFrensie_MAKE_TEST(tstUtility.MPI.GlobalMPISessionInit)
  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_default_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=default)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_default_test PROPERTY LABELS pyfrensie)

  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=advanced)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_test PROPERTY LABELS pyfrensie)

  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_basic_single_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=basic_single)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_basic_single_test PROPERTY LABELS pyfrensie)

  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_single_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=advanced_single)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_single_test PROPERTY LABELS pyfrensie)

  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_basic_funneled_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=basic_funneled)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_basic_funneled_test PROPERTY LABELS pyfrensie)

  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_funneled_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=advanced_funneled)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_funneled_test PROPERTY LABELS pyfrensie)

  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_basic_serialized_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=basic_serialized)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_basic_serialized_test PROPERTY LABELS pyfrensie)

  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_serialized_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=advanced_serialized)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_serialized_test PROPERTY LABELS pyfrensie)

  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_basic_multiple_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=basic_multiple)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_basic_multiple_test PROPERTY LABELS pyfrensie)

  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_multiple_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=advanced_multiple)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_multiple_test PROPERTY LABELS pyfrensie)

  PyFrensie_MAKE_TEST(tstUtility.MPI.GlobalMPISession)
  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISession2_test ${MPIEXEC} -n 2 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISession.py )
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISession2_test PROPERTY LABELS pyfrensie)

  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISession4_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISession.py )
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISession4_test PROPERTY LABELS pyfrensie)

ELSE()
  PyFrensie_MAKE_TEST(tstUtility.MPI.GlobalMPISessionInit)
  ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_default_test ${PYTHON_EXECUTABLE} tstUtility.MPI.GlobalMPISessionInit.py --constructor_type=default)
  SET_PROPERTY(TEST PyFrensie.Utility.MPI.GlobalMPISessionInit_default_test PROPERTY LABELS pyfrensie)
ENDIF()

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

# Add the Utility.Mesh unit tests
PyFrensie_MAKE_TEST(tstUtility.Mesh)
ADD_TEST(PyFrensie.Utility.Mesh_test ${PYTHON_EXECUTABLE} tstUtility.Mesh.py --tet_mesh_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk)
SET_PROPERTY(TEST PyFrensie.Utility.Mesh_test PROPERTY LABELS pyfrensie)

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

IF(HAVE_FRENSIE_HDF5)
  ADD_TEST(PyFrensie.Data.ScatteringCenterPropertiesDatabase_test ${PYTHON_EXECUTABLE} tstData.ScatteringCenterPropertiesDatabase.py --hdf5)
  SET_PROPERTY(TEST PyFrensie.Data.ScatteringCenterPropertiesDatabase_test PROPERTY LABELS pyfrensie hdf5)
ENDIF()

# Add the Data.Xsdir unit tests
PyFrensie_MAKE_TEST(tstData.Xsdir)
ADD_TEST(PyFrensie.Data.Xsdir_test ${PYTHON_EXECUTABLE} tstData.Xsdir.py --test_xsdir_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_xsdir)
SET_PROPERTY(TEST PyFrensie.Data.Xsdir_test PROPERTY LABELS pyfrensie)

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
ADD_DEPENDENCIES(PyFrensie_tstData.ENDL.ENDLDataContainer ${TEST_H_ENDL_NATIVE_FILE_TARGET})
ADD_TEST(PyFrensie.Data.ENDL.ENDLDataContainer_test ${PYTHON_EXECUTABLE} tstData.ENDL.ENDLDataContainer.py --endlfile=${TEST_H_ENDL_NATIVE_FILE})
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
IF(${FRENSIE_ENABLE_DAGMC} OR ${FRENSIE_ENABLE_ROOT})
  PyFrensie_MAKE_TEST(tstGeometry.ModelProperties)

  IF(${FRENSIE_ENABLE_DAGMC})
    ADD_TEST(PyFrensie.Geometry.ModelProperties_DagMC_test ${PYTHON_EXECUTABLE} tstGeometry.ModelProperties.py --dagmc_h5m_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)
    SET_PROPERTY(TEST PyFrensie.Geometry.ModelProperties_DagMC_test PROPERTY LABELS pyfrensie dagmc)
  ENDIF()

  IF(${FRENSIE_ENABLE_ROOT})
    ADD_TEST(PyFrensie.Geometry.ModelProperties_Root_test ${PYTHON_EXECUTABLE} tstGeometry.ModelProperties.py --root_file=${CMAKE_CURRENT_BINARY_DIR}}/test_files/test_root_geom.root)
    SET_PROPERTY(TEST PyFrensie.Geometry.ModelProperties_Root_test PROPERTY LABLES pyfrensie root)
  ENDIF()
ENDIF()

# Add the Geometry.Model unit tests
IF(${FRENSIE_ENABLE_DAGMC} OR ${FRENSIE_ENABLE_ROOT})
  PyFrensie_MAKE_TEST(tstGeometry.Model)

  IF(${FRENSIE_ENABLE_DAGMC})
    ADD_TEST(PyFrensie.Geometry.Model_DagMC_test ${PYTHON_EXECUTABLE} tstGeometry.Model.py --dagmc_h5m_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)
    SET_PROPERTY(TEST PyFrensie.Geometry.Model_DagMC_test PROPERTY LABELS pyfrensie dagmc)
  ENDIF()

  IF(${FRENSIE_ENABLE_ROOT})
    ADD_DEPENDENCIES(PyFrensie_tstGeometry.Model ${ROOT_GEOM_TEST_TARGET})
    ADD_TEST(PyFrensie.Geometry.Model_Root_test ${PYTHON_EXECUTABLE} tstGeometry.Model.py --root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)
    SET_PROPERTY(TEST PyFrensie.Geometry.Model_Root_test PROPERTY LABLES pyfrensie root)
  ENDIF()
ENDIF()

# Add the Geometry.Navigator unit tests
IF(${FRENSIE_ENABLE_DAGMC} OR ${FRENSIE_ENABLE_ROOT})
  PyFrensie_MAKE_TEST(tstGeometry.Navigator)

  IF(${FRENSIE_ENABLE_DAGMC})
    ADD_TEST(PyFrensie.Geometry.Navigator_DagMC_test ${PYTHON_EXECUTABLE} tstGeometry.Navigator.py --dagmc_h5m_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)
    SET_PROPERTY(TEST PyFrensie.Geometry.Navigator_DagMC_test PROPERTY LABELS pyfrensie dagmc)
  ENDIF()

  IF(${FRENSIE_ENABLE_ROOT})
    ADD_DEPENDENCIES(PyFrensie_tstGeometry.Navigator ${ROOT_GEOM_TEST_TARGET})
    ADD_TEST(PyFrensie.Geometry.Navigator_Root_test ${PYTHON_EXECUTABLE} tstGeometry.Navigator.py --root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)
    SET_PROPERTY(TEST PyFrensie.Geometry.Navigator_Root_test PROPERTY LABLES pyfrensie root)
  ENDIF()
ENDIF()

# Add the MonteCarlo.ParticleState unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.ParticleState)
ADD_TEST(PyFrensie.MonteCarlo.ParticleState_test ${PYTHON_EXECUTABLE} tstMonteCarlo.ParticleState.py)

# Add the MonteCarlo.ParticleBank unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.ParticleBank)
ADD_TEST(PyFrensie.MonteCarlo.ParticleBank_test ${PYTHON_EXECUTABLE} tstMonteCarlo.ParticleBank.py)

# Add the MonteCarlo.SimulationGeneralProperties unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.SimulationGeneralProperties)
ADD_TEST(PyFrensie.MonteCarlo.SimulationGeneralProperties_test ${PYTHON_EXECUTABLE} tstMonteCarlo.SimulationGeneralProperties.py)

# Add the MonteCarlo.SimulationNeutronProperties unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.SimulationNeutronProperties)
ADD_TEST(PyFrensie.MonteCarlo.SimulationNeutronProperties_test ${PYTHON_EXECUTABLE} tstMonteCarlo.SimulationNeutronProperties.py)

# Add the MonteCarlo.SimulationPhotonProperties unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.SimulationPhotonProperties)
ADD_TEST(PyFrensie.MonteCarlo.SimulationPhotonProperties_test ${PYTHON_EXECUTABLE} tstMonteCarlo.SimulationPhotonProperties.py)

# Add the MonteCarlo.SimulationAdjointPhotonProperties unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.SimulationAdjointPhotonProperties)
ADD_TEST(PyFrensie.MonteCarlo.SimulationAdjointPhotonProperties_test ${PYTHON_EXECUTABLE} tstMonteCarlo.SimulationAdjointPhotonProperties.py)

# Add the MonteCarlo.SimulationElectronProperties unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.SimulationElectronProperties)
ADD_TEST(PyFrensie.MonteCarlo.SimulationElectronProperties_test ${PYTHON_EXECUTABLE} tstMonteCarlo.SimulationElectronProperties.py)

# Add the MonteCarlo.SimulationAdjointElectronProperties unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.SimulationAdjointElectronProperties)
ADD_TEST(PyFrensie.MonteCarlo.SimulationAdjointElectronProperties_test ${PYTHON_EXECUTABLE} tstMonteCarlo.SimulationAdjointElectronProperties.py)

# Add the MonteCarlo.SimulationProperties unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.SimulationProperties)
ADD_TEST(PyFrensie.MonteCarlo.SimulationProperties_test ${PYTHON_EXECUTABLE} tstMonteCarlo.SimulationProperties.py)

# Add the MonteCarlo.Collision.ScatteringCenterDefinition unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.ScatteringCenterDefinition)
ADD_TEST(PyFrensie.MonteCarlo.Collision.ScatteringCenterDefinition_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.ScatteringCenterDefinition.py)

# Add the MonteCarlo.Collision.ScatteringCenterDefinitionDatabase unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.ScatteringCenterDefinitionDatabase)
ADD_TEST(PyFrensie.MonteCarlo.Collision.ScatteringCenterDefinitionDatabase_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.ScatteringCenterDefinitionDatabase.py)

# Add the MonteCarlo.Collision.MaterialDefinitionDatabase unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.MaterialDefinitionDatabase)
ADD_TEST(PyFrensie.MonteCarlo.Collision.MaterialDefinitionDatabase_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.MaterialDefinitionDatabase.py)

IF(${FRENSIE_ENABLE_DAGMC})
  # Add the MonteCarlo.Collision.FilledGeometryModel unit tests
  PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.FilledGeometryModel)
  ADD_TEST(PyFrensie.MonteCarlo.Collision.FilledGeometryModel_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.FilledGeometryModel.py --dagmc_h5m_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m --database_path=${COLLISION_DATABASE_XML_FILE})
  ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Collision.FilledGeometryModel ${COLLISION_DATABASE_XML_FILE_TARGET} )
ENDIF()

# # Add the MonteCarlo.Collision.PhotonKinematics unit tests
# PyFrensie_MAKE_TEST(tstMonteCarlo.Collision.PhotonKinematics)
# ADD_TEST(PyFrensie.MonteCarlo.Collision.PhotonKinematics_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Collision.PhotonKinematics.py)

# Add the MonteCarlo.Electron.ElectronScatteringNativeDistribution unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Electron.ElectronScatteringNativeDistribution)
ADD_TEST(PyFrensie.MonteCarlo.Electron.ElectronScatteringNativeDistribution_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Electron.ElectronScatteringNativeDistribution.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)
SET_PROPERTY(TEST PyFrensie.MonteCarlo.Electron.ElectronScatteringNativeDistribution_test PROPERTY LABELS pyfrensie electron )

# # Add the MonteCarlo.Electron.ElectronScatteringACEDistribution unit tests
# PyFrensie_MAKE_TEST(tstMonteCarlo.Electron.ElectronScatteringACEDistribution)
# ADD_TEST(PyFrensie.MonteCarlo.Electron.ElectronScatteringACEDistribution_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Electron.ElectronScatteringACEDistribution.py --acefile=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h_epr14_ace_file.txt --tablename=1000.14p)
# SET_PROPERTY(TEST PyFrensie.MonteCarlo.Electron.ElectronScatteringACEDistribution_test PROPERTY LABELS pyfrensie electron )

# # Add the MonteCarlo.Electron.AdjointElectronScatteringDistribution unit tests
# PyFrensie_MAKE_TEST(tstMonteCarlo.Electron.AdjointElectronScatteringDistribution)
# ADD_TEST(PyFrensie.MonteCarlo.Electron.AdjointElectronScatteringDistribution_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Electron.AdjointElectronScatteringDistribution.py --adjointfile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)
# SET_PROPERTY(TEST PyFrensie.MonteCarlo.Electron.AdjointElectronScatteringDistribution_test PROPERTY LABELS pyfrensie electron adjoint)

# Add the MonteCarlo.Electron.ElectroatomicReaction unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Electron.ElectroatomicReaction)
ADD_TEST(PyFrensie.MonteCarlo.Electron.ElectroatomicReaction_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Electron.ElectroatomicReaction.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml )

# # Add the adjoint MonteCarlo.Electron.AdjointElectroatomicReaction unit tests
# PyFrensie_MAKE_TEST(tstMonteCarlo.Electron.AdjointElectroatomicReaction)
# ADD_TEST(PyFrensie.MonteCarlo.Electron.AdjointElectroatomicReaction_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Electron.AdjointElectroatomicReaction.py --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml )
# SET_PROPERTY(TEST PyFrensie.MonteCarlo.Electron.AdjointElectroatomicReaction_test PROPERTY LABELS pyfrensie electron )

# Add the MonteCarlo.ActiveRegion.PhaseSpaceDimension unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.ActiveRegion.PhaseSpaceDimension)
ADD_TEST(PyFrensie.MonteCarlo.ActiveRegion.PhaseSpaceDimension_test ${PYTHON_EXECUTABLE} tstMonteCarlo.ActiveRegion.PhaseSpaceDimension.py)

# Add the MonteCarlo.ActiveRegion.StandardParticleDistribution unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.ActiveRegion.StandardParticleDistribution)
ADD_TEST(PyFrensie.MonteCarlo.ActiveRegion.StandardParticleDistribution_test ${PYTHON_EXECUTABLE} tstMonteCarlo.ActiveRegion.StandardParticleDistribution.py)

# Add the MonteCarlo.ActiveRegion.ParticleResponse unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.ActiveRegion.ParticleResponse)
ADD_TEST(PyFrensie.MonteCarlo.ActiveRegion.ParticleResponse_test ${PYTHON_EXECUTABLE} tstMonteCarlo.ActiveRegion.ParticleResponse.py --database=${COLLISION_DATABASE_XML_FILE})
ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.ActiveRegion.ParticleResponse ${COLLISION_DATABASE_XML_FILE_TARGET} )

# Add the MonteCarlo.ActiveRegion.ParticleSource unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.ActiveRegion.ParticleSource)
ADD_TEST(PyFrensie.MonteCarlo.ActiveRegion.ParticleSource_test ${PYTHON_EXECUTABLE} tstMonteCarlo.ActiveRegion.ParticleSource.py --database=${COLLISION_DATABASE_XML_FILE})
ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.ActiveRegion.ParticleSource ${COLLISION_DATABASE_XML_FILE_TARGET} )

# Add the MonteCarlo.Event.ObserverPhaseSpaceDimensionDiscretization unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Event.ObserverPhaseSpaceDimensionDiscretization)
ADD_TEST(PyFrensie.MonteCarlo.Event.ObserverPhaseSpaceDimensionDiscretization_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.ObserverPhaseSpaceDimensionDiscretization.py)

# Add the MonteCarlo.Event.StandardEntityEstimator unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Event.StandardEntityEstimator)
ADD_TEST(PyFrensie.MonteCarlo.Event.StandardEntityEstimator_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.StandardEntityEstimator.py)

# Add the MonteCarlo.Event.SurfaceCurrentEstimator unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Event.SurfaceCurrentEstimator)
ADD_TEST(PyFrensie.MonteCarlo.Event.SurfaceCurrentEstimator_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.SurfaceCurrentEstimator.py)

# Add the MonteCarlo.Event.SurfaceFluxEstimator unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Event.SurfaceFluxEstimator)
ADD_TEST(PyFrensie.MonteCarlo.Event.SurfaceFluxEstimator_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.SurfaceFluxEstimator.py)

# Add the MonteCarlo.Event.CellCollisionFluxEstimator unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Event.CellCollisionFluxEstimator)
ADD_TEST(PyFrensie.MonteCarlo.Event.CellCollisionFluxEstimator_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.CellCollisionFluxEstimator.py)

# Add the MonteCarlo.Event.CellTrackLengthFluxEstimator unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Event.CellTrackLengthFluxEstimator)
ADD_TEST(PyFrensie.MonteCarlo.Event.CellTrackLengthFluxEstimator_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.CellTrackLengthFluxEstimator.py)

# Add the MonteCarlo.Event.CellPulseHeightEstimator unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Event.CellPulseHeightEstimator)
ADD_TEST(PyFrensie.MonteCarlo.Event.CellPulseHeightEstimator_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.CellPulseHeightEstimator.py)

# Add the MonteCarlo.Event.MeshTrackLengthFluxEstimator unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Event.MeshTrackLengthFluxEstimator)
ADD_TEST(PyFrensie.MonteCarlo.Event.MeshTrackLengthFluxEstimator_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.MeshTrackLengthFluxEstimator.py --tet_mesh_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk)
SET_PROPERTY(TEST PyFrensie.MonteCarlo.Event.MeshTrackLengthFluxEstimator_test PROPERTY LABELS pyfrensie)

# Add the DAGMC Estimator unit tests
IF(${FRENSIE_ENABLE_DAGMC})
  PyFrensie_MAKE_TEST(tstMonteCarlo.Event.SurfaceFluxEstimatorDagMC)
  ADD_TEST(PyFrensie.MonteCarlo.Event.SurfaceFluxEstimatorDagMC_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.SurfaceFluxEstimatorDagMC.py --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)

  PyFrensie_MAKE_TEST(tstMonteCarlo.Event.CellCollisionFluxEstimatorDagMC)
  ADD_TEST(PyFrensie.MonteCarlo.Event.CellCollisionFluxEstimatorDagMC_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.CellCollisionFluxEstimatorDagMC.py --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)

  PyFrensie_MAKE_TEST(tstMonteCarlo.Event.CellTrackLengthFluxEstimatorDagMC)
  ADD_TEST(PyFrensie.MonteCarlo.Event.CellTrackLengthFluxEstimatorDagMC_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.CellTrackLengthFluxEstimatorDagMC.py --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)
ENDIF()

# Add the Root Estimator unit tests
IF(${FRENSIE_ENABLE_ROOT})
  PyFrensie_MAKE_TEST(tstMonteCarlo.Event.CellCollisionFluxEstimatorRoot)
  ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Event.CellCollisionFluxEstimatorRoot ${ROOT_GEOM_TEST_TARGET})
  ADD_TEST(PyFrensie.MonteCarlo.Event.CellCollisionFluxEstimatorRoot_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.CellCollisionFluxEstimatorRoot.py --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)

  PyFrensie_MAKE_TEST(tstMonteCarlo.Event.CellTrackLengthFluxEstimatorRoot)
  ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Event.CellTrackLengthFluxEstimatorRoot ${ROOT_GEOM_TEST_TARGET})
  ADD_TEST(PyFrensie.MonteCarlo.Event.CellTrackLengthFluxEstimatorRoot_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.CellTrackLengthFluxEstimatorRoot.py --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)
ENDIF()

# Add the MonteCarlo.Event.ParticleTracker unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Event.ParticleTracker)
ADD_TEST(PyFrensie.MonteCarlo.Event.ParticleTracker_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.ParticleTracker.py)

# Add the MonteCarlo.Event.EventHandler unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Event.EventHandler)
ADD_TEST(PyFrensie.MonteCarlo.Event.EventHandler_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Event.EventHandler.py)

# Add the MonteCarlo.Manager.ParticleSimulationManagerFactory unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Manager.ParticleSimulationManagerFactory)
ADD_TEST(PyFrensie.MonteCarlo.Manager.ParticleSimulationManagerFactory_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Manager.ParticleSimulationManagerFactory.py --database_path=${COLLISION_DATABASE_XML_FILE} --threads=1 )
ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Manager.ParticleSimulationManagerFactory ${COLLISION_DATABASE_XML_FILE_TARGET} )

IF(HAVE_FRENSIE_MPI)
  ADD_TEST(PyFrensie.MonteCarlo.Manager.ParticleSimulationManagerFactory_2_test ${MPIEXEC} -n 2 ${PYTHON_EXECUTABLE} tstMonteCarlo.Manager.ParticleSimulationManagerFactory.py --database_path=${COLLISION_DATABASE_XML_FILE} --threads=2 )
  ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Manager.ParticleSimulationManagerFactory ${COLLISION_DATABASE_XML_FILE_TARGET} )

  ADD_TEST(PyFrensie.MonteCarlo.Manager.ParticleSimulationManagerFactory_4_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstMonteCarlo.Manager.ParticleSimulationManagerFactory.py --database_path=${COLLISION_DATABASE_XML_FILE} --threads=4 )
  ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Manager.ParticleSimulationManagerFactory ${COLLISION_DATABASE_XML_FILE_TARGET} )
ENDIF()

IF(HAVE_FRENSIE_HDF5)
  SET(HAVE_HDF5_FLAG --have_hdf5)
ENDIF()

# Add the MonteCarlo.Manager.ParticleSimulationManager unit tests
PyFrensie_MAKE_TEST(tstMonteCarlo.Manager.ParticleSimulationManager)
ADD_TEST(PyFrensie.MonteCarlo.Manager.ParticleSimulationManager_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Manager.ParticleSimulationManager.py --database_path=${COLLISION_DATABASE_XML_FILE} --threads=1 ${HAVE_HDF5_FLAG} )
ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Manager.ParticleSimulationManager ${COLLISION_DATABASE_XML_FILE_TARGET} )

IF(HAVE_FRENSIE_OPENMP)
  ADD_TEST(PyFrensie.MonteCarlo.Manager.SharedParallelParticleSimulationManager_2_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Manager.ParticleSimulationManager.py --database_path=${COLLISION_DATABASE_XML_FILE} --threads=2 ${HAVE_HDF5_FLAG} )
  ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Manager.ParticleSimulationManager ${COLLISION_DATABASE_XML_FILE_TARGET} )

  ADD_TEST(PyFrensie.MonteCarlo.Manager.SharedParallelParticleSimulationManager_4_test ${PYTHON_EXECUTABLE} tstMonteCarlo.Manager.ParticleSimulationManager.py --database_path=${COLLISION_DATABASE_XML_FILE} --threads=4 ${HAVE_HDF5_FLAG} )
  ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Manager.ParticleSimulationManager ${COLLISION_DATABASE_XML_FILE_TARGET} )
ENDIF()

IF(HAVE_FRENSIE_MPI)
  PyFrensie_MAKE_TEST(tstMonteCarlo.Manager.DistributedParticleSimulationManager)
  ADD_TEST(PyFrensie.MonteCarlo.Manager.DistributedParticleSimulationManager_2_test ${MPIEXEC} -n 2 ${PYTHON_EXECUTABLE} tstMonteCarlo.Manager.DistributedParticleSimulationManager.py --database_path=${COLLISION_DATABASE_XML_FILE} --threads=1 ${HAVE_HDF5_FLAG} )
  ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Manager.DistributedParticleSimulationManager ${COLLISION_DATABASE_XML_FILE_TARGET} )

  ADD_TEST(PyFrensie.MonteCarlo.Manager.DistributedParticleSimulationManager_4_test ${MPIEXEC} -n 4 ${PYTHON_EXECUTABLE} tstMonteCarlo.Manager.DistributedParticleSimulationManager.py --database_path=${COLLISION_DATABASE_XML_FILE} --threads=1 ${HAVE_HDF5_FLAG} )
  ADD_DEPENDENCIES(PyFrensie_tstMonteCarlo.Manager.DistributedParticleSimulationManager ${COLLISION_DATABASE_XML_FILE_TARGET} )
ENDIF()

IF(HAVE_FRENSIE_HDF5)
  UNSET(HAVE_HDF5_FLAG)
ENDIF()

PyFrensie_MAKE_TEST(tstDataGen.ElectronPhoton.ElectronPhotonRelaxationDataGenerator)
ADD_DEPENDENCIES(PyFrensie_tstDataGen.ElectronPhoton.ElectronPhotonRelaxationDataGenerator ${TEST_H_ENDL_NATIVE_FILE_TARGET})
ADD_TEST(PyFrensie.DataGen.ElectronPhoton.ElectronPhotonRelaxationDataGenerator tstDataGen.ElectronPhoton.ElectronPhotonRelaxationDataGenerator.py --test_h_endl_file=${TEST_H_ENDL_NATIVE_FILE} --test_h_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h_epr_ace_file.txt)

PyFrensie_MAKE_TEST(tstDataGen.ElectronPhoton.AdjointElectronPhotonRelaxationDataGenerator)
ADD_TEST(PyFrensie.DataGen.ElectronPhoton.AdjointElectronPhotonRelaxationDataGenerator tstDataGen.ElectronPhoton.AdjointElectronPhotonRelaxationDataGenerator.py --test_h_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)

PyFrensie_MAKE_TEST(tstDataGen.ENDL.StandardENDLDataGenerator)
ADD_TEST(PyFrensie.DataGen.ENDL.StandardENDLDataGenerator tstDataGen.ENDL.StandardENDLDataGenerator.py --test_h_eadl_file=${eadl1} --test_h_epdl_file=${epdl1} --test_h_eedl_file=${eedl1})


