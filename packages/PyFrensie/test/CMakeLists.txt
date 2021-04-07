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
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/PyFrensieSetupTests.cmake)

# Add the testHelpers module to the unit test directory
ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/testutil.py
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/copyWithCMakeSubstitutions.py
          ${CMAKE_CURRENT_SOURCE_DIR}/testingHelpers.py.in
	  ${CMAKE_CURRENT_BINARY_DIR}/testingHelpers.py
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/testingHelpers.py.in)

ADD_CUSTOM_TARGET(testingHelpers ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/testutil.py)

PyFrensie_INITIALIZE_PACKAGE_TESTS()

# Add the Utility logging unit tests
PyFrensie_MAKE_TEST(Utility.Logging)
PyFrensie_ADD_TEST(Utility.Logging)

# Add the Utility arrayFromString unit tests
PyFrensie_MAKE_TEST(Utility.ArrayFromString)
PyFrensie_ADD_TEST(Utility.ArrayFromString)

# Add the Utility just-in-time initialization unit tests
PyFrensie_MAKE_TEST(Utility.JustInTimeInitialization)
PyFrensie_ADD_TEST(Utility.JustInTimeInitialization)

IF(HAVE_FRENSIE_MPI)
  # Add the Utility_GlobalMPISession unit tests
  PyFrensie_MAKE_TEST(Utility.MPI.GlobalMPISessionInit)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISessionInit_default
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    MPI_PROCS 4
    EXTRA_ARGS --constructor_type=default)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISessionInit_advanced
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    MPI_PROCS 4
    EXTRA_ARGS --constructor_type=advanced)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISessionInit_basic_single
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    MPI_PROCS 4
    EXTRA_ARGS --constructor_type=basic_single)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISessionInit_advanced_single
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    MPI_PROCS 4
    EXTRA_ARGS --constructor_type=advanced_single)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISessionInit_basic_funneled
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    MPI_PROCS 4
    EXTRA_ARGS --constructor_type=basic_funneled)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISessionInit_advanced_funneled
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    MPI_PROCS 4
    EXTRA_ARGS --constructor_type=advanced_funneled)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISessionInit_basic_serialized
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    MPI_PROCS 4
    EXTRA_ARGS --constructor_type=basic_serialized)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISessionInit_advanced_serialized
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    MPI_PROCS 4
    EXTRA_ARGS --constructor_type=advanced_serialized)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISessionInit_basic_multiple
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    MPI_PROCS 4
    EXTRA_ARGS --constructor_type=basic_multiple)
  PyFrensie_ADD_TEST(PyFrensie.Utility.MPI.GlobalMPISessionInit_advanced_multiple
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    MPI_PROCS 4
    EXTRA_ARGS --constructor_type=advanced_multiple)
  
  PyFrensie_MAKE_TEST(Utility.MPI.GlobalMPISession)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISession
    MPI_PROCS 2)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISession
    MPI_PROCS 4)
ELSE()
  PyFrensie_MAKE_TEST(Utility.MPI.GlobalMPISessionInit)
  PyFrensie_ADD_TEST(Utility.MPI.GlobalMPISessionInit_default
    TEST_EXEC_NAME_ROOT Utility.MPI.GlobalMPISessionInit
    EXTRA_ARGS --constructor_type=default)
ENDIF()

# Add the Utility.Prng unit tests
PyFrensie_MAKE_TEST(Utility.Prng)
PyFrensie_ADD_TEST(Utility.Prng)

# Add the Utility.Distribution unit tests
PyFrensie_MAKE_TEST(Utility.Distribution.UnivariateDistribution)
PyFrensie_ADD_TEST(Utility.Distribution.UnivariateDistribution)

PyFrensie_MAKE_TEST(Utility.Distribution.BivariateDistribution)
PyFrensie_ADD_TEST(Utility.Distribution.BivariateDistribution)

PyFrensie_MAKE_TEST(Utility.Coordinate.CartesianCoordinate)
PyFrensie_ADD_TEST(Utility.Coordinate.CartesianCoordinate)

PyFrensie_MAKE_TEST(Utility.Coordinate.SphericalCoordinate)
PyFrensie_ADD_TEST(Utility.Coordinate.SphericalCoordinate)

PyFrensie_MAKE_TEST(Utility.Coordinate.CylindricalCoordinate)
PyFrensie_ADD_TEST(Utility.Coordinate.CylindricalCoordinate)

# Add the Utility.Mesh unit tests
PyFrensie_MAKE_TEST(Utility.Mesh)
PyFrensie_ADD_TEST(Utility.Mesh
  EXTRA_ARGS --tet_mesh_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk)

# Add the Data.AtomProperties unit tests
PyFrensie_MAKE_TEST(Data.AtomProperties)
PyFrensie_ADD_TEST(Data.AtomProperties)

# Add the Data.NuclideProperties unit tests
PyFrensie_MAKE_TEST(Data.NuclideProperties)
PyFrensie_ADD_TEST(Data.NuclideProperties)

# Add the Data.ScatteringCenterPropertiesDatabaseImpl unit tests
PyFrensie_MAKE_TEST(Data.ScatteringCenterPropertiesDatabaseImpl)
PyFrensie_ADD_TEST(Data.ScatteringCenterPropertiesDatabaseImpl)

# Add the Data.ScatteringCenterPropertiesDatabase unit tests
PyFrensie_MAKE_TEST(Data.ScatteringCenterPropertiesDatabase)
PyFrensie_ADD_TEST(Data.ScatteringCenterPropertiesDatabase)

IF(HAVE_FRENSIE_HDF5)
  PyFrensie_ADD_TEST(Data.ScatteringCenterPropertiesDatabase_hdf5
    TEST_EXEC_NAME_ROOT Data.ScatteringCenterPropertiesDatabase
    EXTRA_LABELS hdf5
    EXTRA_ARGS --hdf5)
ENDIF()

# Add the Data.Xsdir unit tests
PyFrensie_MAKE_TEST(Data.Xsdir)
PyFrensie_ADD_TEST(Data.Xsdir
  EXTRA_ARGS --test_xsdir_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_xsdir)

# Add the Data.ACE.ACEElectroatomicDataProperties unit tests
PyFrensie_MAKE_TEST(Data.ACE.ACEElectroatomicDataProperties)
PyFrensie_ADD_TEST(Data.ACE.ACEElectroatomicDataProperties)

# Add the Data.ACE.ACEPhotoatomicDataProperties unit tests
PyFrensie_MAKE_TEST(Data.ACE.ACEPhotoatomicDataProperties)
PyFrensie_ADD_TEST(Data.ACE.ACEPhotoatomicDataProperties)

# Add the Data.ACE.ACENuclearDataProperties unit tests
PyFrensie_MAKE_TEST(Data.ACE.ACENuclearDataProperties)
PyFrensie_ADD_TEST(Data.ACE.ACENuclearDataProperties)

# Add the Data.ACE.ACEThermalNuclearDataProperties unit tests
PyFrensie_MAKE_TEST(Data.ACE.ACEThermalNuclearDataProperties)
PyFrensie_ADD_TEST(Data.ACE.ACEThermalNuclearDataProperties)

# Add the Data.ACE.ACEFileHandler unit tests
PyFrensie_MAKE_TEST(Data.ACE.ACEFileHandler)
PyFrensie_ADD_TEST(Data.ACE.ACEFileHandler
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --acefile=1001.70c:filepath
  --startline=1001.70c:filestartline)

# Add the Data.ACE.XSSNeutronDataExtractor unit tests
PyFrensie_MAKE_TEST(Data.ACE.XSSNeutronDataExtractor)
PyFrensie_ADD_TEST(Data.ACE.XSSNeutronDataExtractor_H1
  TEST_EXEC_NAME_ROOT Data.ACE.XSSNeutronDataExtractor
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --tablename=1001.70c
  --acefile=1001.70c:filepath
  --startline=1001.70c:filestartline)
PyFrensie_ADD_TEST(Data.ACE.XSSNeutronDataExtractor_U238
  TEST_EXEC_NAME_ROOT Data.ACE.XSSNeutronDataExtractor
  ACE_LIB_DEPENDS 92238.70c
  EXTRA_ARGS
  --tablename=92238.70c
  --acefile=92238.70c:filepath
  --startline=92238.70c:filestartline)

# Add the Data.ACE.XSSEPRDataExtractor unit tests
PyFrensie_MAKE_TEST(Data.ACE.XSSEPRDataExtractor)
PyFrensie_ADD_TEST(Data.ACE.XSSEPRDataExtractor_B
  TEST_EXEC_NAME_ROOT Data.ACE.XSSEPRDataExtractor
  ACE_LIB_DEPENDS 5000.12p
  EXTRA_ARGS
  --tablename=5000.12p
  --acefile=5000.12p:filepath
  --startline=5000.12p:filestartline)
PyFrensie_ADD_TEST(Data.ACE.XSSEPRDataExtractor_Pb
  TEST_EXEC_NAME_ROOT Data.ACE.XSSEPRDataExtractor
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --tablename=82000.12p
  --acefile=82000.12p:filepath
  --startline=82000.12p:filestartline)
PyFrensie_ADD_TEST(Data.ACE.XSSEPRDataExtractor_epr14_Pb
  TEST_EXEC_NAME_ROOT Data.ACE.XSSEPRDataExtractor
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --tablename=82000.14p
  --acefile=82000.14p:filepath
  --startline=82000.14p:filestartline)

# Add the Data.ACE.XSSElectronDataExtractor unit tests
PyFrensie_MAKE_TEST(Data.ACE.XSSElectronDataExtractor)
PyFrensie_ADD_TEST(Data.ACE.XSSElectronDataExtractor_B
  TEST_EXEC_NAME_ROOT Data.ACE.XSSElectronDataExtractor
  ACE_LIB_DEPENDS 5000.03e
  EXTRA_ARGS
  --tablename=5000.03e
  --acefile=5000.03e:filepath
  --startline=5000.03e:filestartline)
PyFrensie_ADD_TEST(Data.ACE.XSSElectronDataExtractor_Pb
  TEST_EXEC_NAME_ROOT Data.ACE.XSSElectronDataExtractor
  ACE_LIB_DEPENDS 82000.03e
  EXTRA_ARGS
  --tablename=82000.03e
  --acefile=82000.03e:filepath
  --startline=82000.03e:filestartline)

# Add the Data.ENDL.ENDLElectroatomicDataProperties unit tests
PyFrensie_MAKE_TEST(Data.ENDL.ENDLElectroatomicDataProperties)
PyFrensie_ADD_TEST(Data.ENDL.ENDLElectroatomicDataProperties)

# Add the Data.ENDL.ENDLPhotoatomicDataProperties unit tests
PyFrensie_MAKE_TEST(Data.ENDL.ENDLPhotoatomicDataProperties)
PyFrensie_ADD_TEST(Data.ENDL.ENDLPhotoatomicDataProperties)

# Add the Data.ENDL.ENDLDataContainer unit tests
PyFrensie_MAKE_TEST(Data.ENDL.ENDLDataContainer
  TARGET_DEPENDS ${TEST_H_ENDL_NATIVE_FILE_TARGET})
PyFrensie_ADD_TEST(Data.ENDL.ENDLDataContainer
  EXTRA_ARGS --endlfile=${TEST_H_ENDL_NATIVE_FILE})

# Add the Data.Native.NativeEPRElectroatomicDataProperties unit tests
PyFrensie_MAKE_TEST(Data.Native.NativeEPRElectroatomicDataProperties)
PyFrensie_ADD_TEST(Data.Native.NativeEPRElectroatomicDataProperties)

# Add the Data.Native.NativeEPRPhotoatomicDataProperties unit tests
PyFrensie_MAKE_TEST(Data.Native.NativeEPRPhotoatomicDataProperties)
PyFrensie_ADD_TEST(Data.Native.NativeEPRPhotoatomicDataProperties)

# Add the Data.Native.NativeMomentPreservingElectroatomicDataProperties unit tests
PyFrensie_MAKE_TEST(Data.Native.NativeMomentPreservingElectroatomicDataProperties)
PyFrensie_ADD_TEST(Data.Native.NativeMomentPreservingElectroatomicDataProperties)

# Add the Data.Native.NativeEPRAdjointElectroatomicDataProperties unit tests
PyFrensie_MAKE_TEST(Data.Native.NativeEPRAdjointElectroatomicDataProperties)
PyFrensie_ADD_TEST(Data.Native.NativeEPRAdjointElectroatomicDataProperties)

# Add the Data.Native.NativeEPRAdjointPhotoatomicDataProperties unit tests
PyFrensie_MAKE_TEST(Data.Native.NativeEPRAdjointPhotoatomicDataProperties)
PyFrensie_ADD_TEST(Data.Native.NativeEPRAdjointPhotoatomicDataProperties)

# Add the Data.Native.ElectronPhotonRelaxationDataContainer unit tests
PyFrensie_MAKE_TEST(Data.Native.ElectronPhotonRelaxationDataContainer)
PyFrensie_ADD_TEST(Data.Native.ElectronPhotonRelaxationDataContainer
  EXTRA_ARGS
  --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_6_native.xml)

# Add the Data.Native.AdjointElectronPhotonRelaxationDataContainer unit tests
PyFrensie_MAKE_TEST(Data.Native.AdjointElectronPhotonRelaxationDataContainer)
PyFrensie_ADD_TEST(Data.Native.AdjointElectronPhotonRelaxationDataContainer
  EXTRA_ARGS
  --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_6_native.xml)

# Add the Geometry.Ray unit tests
PyFrensie_MAKE_TEST(Geometry.Ray)
PyFrensie_ADD_TEST(Geometry.Ray)

# Add the Geometry.ModelProperties unit tests
PyFrensie_MAKE_TEST(Geometry.InfiniteMediumModel)
PyFrensie_ADD_TEST(Geometry.InfiniteMediumModel)

IF(${FRENSIE_ENABLE_DAGMC} OR ${FRENSIE_ENABLE_ROOT})
  PyFrensie_MAKE_TEST(Geometry.ModelProperties)

  IF(${FRENSIE_ENABLE_DAGMC})
    PyFrensie_ADD_TEST(Geometry.ModelProperties_DagMC
      TEST_EXEC_NAME_ROOT Geometry.ModelProperties
      EXTRA_LABELS dagmc
      EXTRA_ARGS --dagmc_h5m_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)
  ENDIF()

  IF(${FRENSIE_ENABLE_ROOT})
    PyFrensie_ADD_TEST(Geometry.ModelProperties_Root
      TEST_EXEC_NAME_ROOT Geometry.ModelProperties
      EXTRA_LABELS root
      EXTRA_ARGS --root_file=${CMAKE_CURRENT_BINARY_DIR}}/test_files/test_root_geom.root)
  ENDIF()
ENDIF()

# Add the Geometry.Model unit tests
IF(${FRENSIE_ENABLE_DAGMC} OR ${FRENSIE_ENABLE_ROOT})

  IF(${FRENSIE_ENABLE_ROOT})
    PyFrensie_MAKE_TEST(Geometry.Model
      TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET})
  ELSE()
    PyFrensie_MAKE_TEST(Geometry.Model)
  ENDIF()

  IF(${FRENSIE_ENABLE_DAGMC})
    PyFrensie_ADD_TEST(Geometry.Model_DagMC
      TEST_EXEC_NAME_ROOT Geometry.Model
      EXTRA_LABELS dagmc
      EXTRA_ARGS --dagmc_h5m_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)
  ENDIF()

   IF(${FRENSIE_ENABLE_ROOT})
     PyFrensie_ADD_TEST(Geometry.Model_Root
       TEST_EXEC_NAME_ROOT Geometry.Model
       EXTRA_LABELS root
       EXTRA_ARGS --root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)
  ENDIF()
ENDIF()

# Add the Geometry.Navigator unit tests
IF(${FRENSIE_ENABLE_DAGMC} OR ${FRENSIE_ENABLE_ROOT})

  IF(${FRENSIE_ENABLE_ROOT})
    PyFrensie_MAKE_TEST(Geometry.Navigator
      TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET})
  ELSE()
    PyFrensie_MAKE_TEST(Geometry.Navigator)
  ENDIF()

  IF(${FRENSIE_ENABLE_DAGMC})
    PyFrensie_ADD_TEST(Geometry.Navigator_DagMC
      TEST_EXEC_NAME_ROOT Geometry.Navigator
      EXTRA_LABELS dagmc
      EXTRA_ARGS --dagmc_h5m_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)
  ENDIF()

  IF(${FRENSIE_ENABLE_ROOT})
    PyFrensie_ADD_TEST(Geometry.Navigator_Root
      TEST_EXEC_NAME_ROOT Geometry.Navigator
      EXTRA_LABELS root
      EXTRA_ARGS --root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)
  ENDIF()
ENDIF()

# Add the MonteCarlo.ParticleState unit tests
PyFrensie_MAKE_TEST(MonteCarlo.ParticleState)
PyFrensie_ADD_TEST(MonteCarlo.ParticleState)

# Add the MonteCarlo.ParticleBank unit tests
PyFrensie_MAKE_TEST(MonteCarlo.ParticleBank)
PyFrensie_ADD_TEST(MonteCarlo.ParticleBank)

# Add the MonteCarlo.SimulationGeneralProperties unit tests
PyFrensie_MAKE_TEST(MonteCarlo.SimulationGeneralProperties)
PyFrensie_ADD_TEST(MonteCarlo.SimulationGeneralProperties)

# Add the MonteCarlo.SimulationNeutronProperties unit tests
PyFrensie_MAKE_TEST(MonteCarlo.SimulationNeutronProperties)
PyFrensie_ADD_TEST(MonteCarlo.SimulationNeutronProperties)

# Add the MonteCarlo.SimulationPhotonProperties unit tests
PyFrensie_MAKE_TEST(MonteCarlo.SimulationPhotonProperties)
PyFrensie_ADD_TEST(MonteCarlo.SimulationPhotonProperties)

# Add the MonteCarlo.SimulationAdjointPhotonProperties unit tests
PyFrensie_MAKE_TEST(MonteCarlo.SimulationAdjointPhotonProperties)
PyFrensie_ADD_TEST(MonteCarlo.SimulationAdjointPhotonProperties)

# Add the MonteCarlo.SimulationElectronProperties unit tests
PyFrensie_MAKE_TEST(MonteCarlo.SimulationElectronProperties)
PyFrensie_ADD_TEST(MonteCarlo.SimulationElectronProperties)

# Add the MonteCarlo.SimulationAdjointElectronProperties unit tests
PyFrensie_MAKE_TEST(MonteCarlo.SimulationAdjointElectronProperties)
PyFrensie_ADD_TEST(MonteCarlo.SimulationAdjointElectronProperties)

# Add the MonteCarlo.SimulationProperties unit tests
PyFrensie_MAKE_TEST(MonteCarlo.SimulationProperties)
PyFrensie_ADD_TEST(MonteCarlo.SimulationProperties)

# Add the MonteCarlo.Collision.ScatteringCenterDefinition unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Collision.ScatteringCenterDefinition)
PyFrensie_ADD_TEST(MonteCarlo.Collision.ScatteringCenterDefinition)

# Add the MonteCarlo.Collision.ScatteringCenterDefinitionDatabase unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Collision.ScatteringCenterDefinitionDatabase)
PyFrensie_ADD_TEST(MonteCarlo.Collision.ScatteringCenterDefinitionDatabase)

# Add the MonteCarlo.Collision.MaterialDefinitionDatabase unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Collision.MaterialDefinitionDatabase)
PyFrensie_ADD_TEST(MonteCarlo.Collision.MaterialDefinitionDatabase)

IF(${FRENSIE_ENABLE_DAGMC})
  # Add the MonteCarlo.Collision.FilledGeometryModel unit tests
  PyFrensie_MAKE_TEST(MonteCarlo.Collision.FilledGeometryModel
    TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
  PyFrensie_ADD_TEST(MonteCarlo.Collision.FilledGeometryModel
    ACE_LIB_DEPENDS 1001.70c 8000.12p
    EXTRA_ARGS
    --dagmc_h5m_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m
    --database_path=${COLLISION_DATABASE_XML_FILE})
ENDIF()

# # Add the MonteCarlo.Photon.PhotonKinematics unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Photon.PhotonKinematics)
PyFrensie_ADD_TEST(MonteCarlo.Photon.PhotonKinematics)

# Add the MonteCarlo.Photon.DopplerBroadenedPhotonEnergyDistributionACEFactory
# unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Photon.DopplerBroadenedPhotonEnergyDistributionACEFactory)
PyFrensie_ADD_TEST(MonteCarlo.Photon.DopplerBroadenedPhotonEnergyDistributionACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

# Add the MonteCarlo.Photon.DopplerBroadenedPhotonEnergyDistributionNativeFactory
# unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Photon.DopplerBroadenedPhotonEnergyDistributionNativeFactory)
PyFrensie_ADD_TEST(MonteCarlo.Photon.DopplerBroadenedPhotonEnergyDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

# Add the MonteCarlo.Photon.IncoherentPhotonScatteringDistributionACEFactory
# unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Photon.IncoherentPhotonScatteringDistributionACEFactory)
PyFrensie_ADD_TEST(MonteCarlo.Photon.IncoherentPhotonScatteringDistributionACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

# Add the MonteCarlo.Photon.IncoherentPhotonScatteringDistributionNativeFactory
# unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Photon.IncoherentPhotonScatteringDistributionNativeFactory)
PyFrensie_ADD_TEST(MonteCarlo.Photon.IncoherentPhotonScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

# Add the MonteCarlo.Photon.IncoherentAdjointPhotonScatteringDistributionNativeFactory
# unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Photon.IncoherentAdjointPhotonScatteringDistributionNativeFactory)
PyFrensie_ADD_TEST(MonteCarlo.Photon.IncoherentAdjointPhotonScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

# Add the MonteCarlo.Photon.CoherentScatteringDistributionACEFactory
# unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Photon.CoherentScatteringDistributionACEFactory)
PyFrensie_ADD_TEST(MonteCarlo.Photon.CoherentScatteringDistributionACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

# Add the MonteCarlo.Photon.CoherentScatteringDistributionNativeFactory
# unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Photon.CoherentScatteringDistributionNativeFactory)
PyFrensie_ADD_TEST(MonteCarlo.Photon.CoherentScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml
  --test_adjoint_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

# Add the MonteCarlo.Electron.ElectronScatteringNativeDistribution unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Electron.ElectronScatteringNativeDistribution)
PyFrensie_ADD_TEST(MonteCarlo.Electron.ElectronScatteringNativeDistribution
  EXTRA_ARGS
  --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)

# Add the MonteCarlo.Electron.ElectroatomicReaction unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Electron.ElectroatomicReaction)
PyFrensie_ADD_TEST(MonteCarlo.Electron.ElectroatomicReaction
  EXTRA_ARGS
  --nativefile=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

# Add the MonteCarlo.ActiveRegion.PhaseSpaceDimension unit tests
PyFrensie_MAKE_TEST(MonteCarlo.ActiveRegion.PhaseSpaceDimension)
PyFrensie_ADD_TEST(MonteCarlo.ActiveRegion.PhaseSpaceDimension)

# Add the MonteCarlo.ActiveRegion.StandardParticleDistribution unit tests
PyFrensie_MAKE_TEST(MonteCarlo.ActiveRegion.StandardParticleDistribution)
PyFrensie_ADD_TEST(MonteCarlo.ActiveRegion.StandardParticleDistribution)

# Add the MonteCarlo.ActiveRegion.ParticleResponse unit tests
PyFrensie_MAKE_TEST(MonteCarlo.ActiveRegion.ParticleResponse
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
PyFrensie_ADD_TEST(MonteCarlo.ActiveRegion.ParticleResponse
  ACE_LIB_DEPENDS 1001.70c 8000.12p
  EXTRA_ARGS
  --database=${COLLISION_DATABASE_XML_FILE})

# Add the MonteCarlo.ActiveRegion.ParticleSource unit tests
PyFrensie_MAKE_TEST(MonteCarlo.ActiveRegion.ParticleSource
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
PyFrensie_ADD_TEST(MonteCarlo.ActiveRegion.ParticleSource
  EXTRA_ARGS
  --database=${COLLISION_DATABASE_XML_FILE})

# Add the MonteCarlo.Event.ObserverPhaseSpaceDimensionDiscretization unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.ObserverPhaseSpaceDimensionDiscretization)
PyFrensie_ADD_TEST(MonteCarlo.Event.ObserverPhaseSpaceDimensionDiscretization)

# Add the MonteCarlo.Event.StandardEntityEstimator unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.StandardEntityEstimator)
PyFrensie_ADD_TEST(MonteCarlo.Event.StandardEntityEstimator)

# Add the MonteCarlo.Event.SurfaceCurrentEstimator unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.SurfaceCurrentEstimator)
PyFrensie_ADD_TEST(MonteCarlo.Event.SurfaceCurrentEstimator)

# Add the MonteCarlo.Event.SurfaceFluxEstimator unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.SurfaceFluxEstimator)
PyFrensie_ADD_TEST(MonteCarlo.Event.SurfaceFluxEstimator)

# Add the MonteCarlo.Event.CellCollisionFluxEstimator unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.CellCollisionFluxEstimator)
PyFrensie_ADD_TEST(MonteCarlo.Event.CellCollisionFluxEstimator)

# Add the MonteCarlo.Event.CellTrackLengthFluxEstimator unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.CellTrackLengthFluxEstimator)
PyFrensie_ADD_TEST(MonteCarlo.Event.CellTrackLengthFluxEstimator)

# Add the MonteCarlo.Event.CellPulseHeightEstimator unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.CellPulseHeightEstimator)
PyFrensie_ADD_TEST(MonteCarlo.Event.CellPulseHeightEstimator)

# Add the MonteCarlo.Event.MeshTrackLengthFluxEstimator unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.MeshTrackLengthFluxEstimator)
PyFrensie_ADD_TEST(MonteCarlo.Event.MeshTrackLengthFluxEstimator
  EXTRA_ARGS
  --tet_mesh_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_unit_cube_tets-6.vtk)

# Add the DAGMC Estimator unit tests
IF(${FRENSIE_ENABLE_DAGMC})
  PyFrensie_MAKE_TEST(MonteCarlo.Event.SurfaceFluxEstimatorDagMC)
  PyFrensie_ADD_TEST(MonteCarlo.Event.SurfaceFluxEstimatorDagMC
    EXTRA_ARGS
    --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)

  PyFrensie_MAKE_TEST(MonteCarlo.Event.CellCollisionFluxEstimatorDagMC)
  PyFrensie_ADD_TEST(MonteCarlo.Event.CellCollisionFluxEstimatorDagMC
    EXTRA_ARGS
    --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)

  PyFrensie_MAKE_TEST(MonteCarlo.Event.CellTrackLengthFluxEstimatorDagMC)
  PyFrensie_ADD_TEST(MonteCarlo.Event.CellTrackLengthFluxEstimatorDagMC
    EXTRA_ARGS
    --test_cad_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_dagmc_geom.h5m)
ENDIF()

# Add the Root Estimator unit tests
IF(${FRENSIE_ENABLE_ROOT})
  PyFrensie_MAKE_TEST(MonteCarlo.Event.CellCollisionFluxEstimatorRoot
    TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET})
  PyFrensie_ADD_TEST(MonteCarlo.Event.CellCollisionFluxEstimatorRoot
    EXTRA_ARGS
    --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)

  PyFrensie_MAKE_TEST(MonteCarlo.Event.CellTrackLengthFluxEstimatorRoot
    TARGET_DEPENDS ${ROOT_GEOM_TEST_TARGET})
  PyFrensie_ADD_TEST(MonteCarlo.Event.CellTrackLengthFluxEstimatorRoot
    EXTRA_ARGS --test_root_file=${CMAKE_CURRENT_BINARY_DIR}/test_files/test_root_geom.root)
ENDIF()

# Add the MonteCarlo.Event.ParticleTracker unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.ParticleTracker)
PyFrensie_ADD_TEST(MonteCarlo.Event.ParticleTracker)

# Add the MonteCarlo.Event.EventHandler unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.EventHandler)
PyFrensie_ADD_TEST(MonteCarlo.Event.EventHandler)

# Add the MonteCarlo.Event.CollisionForcer unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Event.CollisionForcer
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
PyFrensie_ADD_TEST(MonteCarlo.Event.CollisionForcer
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --database_path=${COLLISION_DATABASE_XML_FILE})

# Add the MonteCarlo.Manager.ParticleSimulationManagerFactory unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Manager.ParticleSimulationManagerFactory
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
PyFrensie_ADD_TEST(MonteCarlo.Manager.ParticleSimulationManagerFactory
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --database_path=${COLLISION_DATABASE_XML_FILE}
  --threads=1)

IF(HAVE_FRENSIE_MPI)
  PyFrensie_ADD_TEST(MonteCarlo.Manager.ParticleSimulationManagerFactory
    ACE_LIB_DEPENDS 1001.70c
    MPI_PROCS 2
    OPENMP_TEST
    EXTRA_ARGS
    --database_path=${COLLISION_DATABASE_XML_FILE}
    --threads=2)
  PyFrensie_ADD_TEST(MonteCarlo.Manager.ParticleSimulationManagerFactory
    ACE_LIB_DEPENDS 1001.70c
    MPI_PROCS 4
    OPENMP_TEST
    EXTRA_ARGS
    --database_path=${COLLISION_DATABASE_XML_FILE}
    --threads=2)
ENDIF()

IF(HAVE_FRENSIE_HDF5)
  SET(HAVE_HDF5_FLAG --have_hdf5)
ENDIF()

# Add the MonteCarlo.Manager.ParticleSimulationManager unit tests
PyFrensie_MAKE_TEST(MonteCarlo.Manager.ParticleSimulationManager
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
PyFrensie_ADD_TEST(MonteCarlo.Manager.ParticleSimulationManager
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --database_path=${COLLISION_DATABASE_XML_FILE}
  --threads=1
  ${HAVE_HDF5_FLAG})

IF(HAVE_FRENSIE_OPENMP)
  PyFrensie_ADD_TEST(MonteCarlo.Manager.SharedParallelParticleSimulationManager_2
    TEST_EXEC_NAME_ROOT MonteCarlo.Manager.ParticleSimulationManager
    ACE_LIB_DEPENDS 1001.70c
    OPENMP_TEST
    EXTRA_ARGS
    --database_path=${COLLISION_DATABASE_XML_FILE}
    --threads=2
    ${HAVE_HDF5_FLAG})
  PyFrensie_ADD_TEST(MonteCarlo.Manager.SharedParallelParticleSimulationManager_4
    TEST_EXEC_NAME_ROOT MonteCarlo.Manager.ParticleSimulationManager
    ACE_LIB_DEPENDS 1001.70c
    OPENMP_TEST
    EXTRA_ARGS
    --database_path=${COLLISION_DATABASE_XML_FILE}
    --threads=4
    ${HAVE_HDF5_FLAG})
ENDIF()

IF(HAVE_FRENSIE_MPI)
  PyFrensie_MAKE_TEST(MonteCarlo.Manager.DistributedParticleSimulationManager
    TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
  PyFrensie_ADD_TEST(MonteCarlo.Manager.DistributedParticleSimulationManager
    ACE_LIB_DEPENDS 1001.70c
    MPI_PROCS 2
    EXTRA_ARGS
    --database_path=${COLLISION_DATABASE_XML_FILE}
    --threads=1
    ${HAVE_HDF5_FLAG})
  PyFrensie_ADD_TEST(MonteCarlo.Manager.DistributedParticleSimulationManager
    ACE_LIB_DEPENDS 1001.70c
    MPI_PROCS 4
    EXTRA_ARGS
    --database_path=${COLLISION_DATABASE_XML_FILE}
    --threads=1
    ${HAVE_HDF5_FLAG})
ENDIF()

IF(HAVE_FRENSIE_HDF5)
  UNSET(HAVE_HDF5_FLAG)
ENDIF()

PyFrensie_MAKE_TEST(DataGen.ENDL.StandardENDLDataGenerator)
PyFrensie_ADD_TEST(DataGen.ENDL.StandardENDLDataGenerator
  EXTRA_ARGS
  --test_h_eadl_file=${eadl1}
  --test_h_epdl_file=${epdl1}
  --test_h_eedl_file=${eedl1})

PyFrensie_MAKE_TEST(DataGen.ElectronPhoton.ElectronPhotonRelaxationDataGenerator
  TARGET_DEPENDS ${TEST_H_ENDL_NATIVE_FILE_TARGET})
PyFrensie_ADD_TEST(DataGen.ElectronPhoton.ElectronPhotonRelaxationDataGenerator
  ACE_LIB_DEPENDS 1000.12p
  EXTRA_ARGS
  --test_h_endl_file=${TEST_H_ENDL_NATIVE_FILE}
  --test_h_ace_file=1000.12p:filepath
  --test_h_ace_file_start_line=1000.12p:filestartline)

PyFrensie_MAKE_TEST(DataGen.ElectronPhoton.AdjointElectronPhotonRelaxationDataGenerator)
PyFrensie_ADD_TEST(DataGen.ElectronPhoton.AdjointElectronPhotonRelaxationDataGenerator
  EXTRA_ARGS
  --test_h_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)

PyFrensie_FINALIZE_PACKAGE_TESTS()
