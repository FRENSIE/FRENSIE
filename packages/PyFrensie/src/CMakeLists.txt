# Create the swig runtime header use by the PyFrensie library
SET(SWIG_RUNTIME swigpyrun.h)
EXECUTE_PROCESS(COMMAND ${SWIG_EXECUTABLE} -python -external-runtime
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  OUTPUT_FILE ${SWIG_RUNTIME})
LIST(APPEND HEADERS ${CMAKE_CURRENT_BINARY_DIR}/${SWIG_RUNTIME})

# Configure the PyFrensie_MPI_Setup.i file
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/PyFrensie_MPI_Setup.i.in
  ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie_MPI_Setup.i)

# Set the PyTrilinos package headers and sources
FRENSIE_SETUP_PACKAGE(pyfrensie_cpp
  MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
  NON_MPI_LIBRARIES ${Boost_LIBRARIES} ${PYTHON_LIBRARIES}
  SET_VERBOSE ${CMAKE_VERBOSE_CONFIGURE})

# Set up the include paths
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Initialize the package and module lists
SET(PyFrensie_PACKAGES "")
SET(PyFrensie_MODULES "")

# Add the Utility package
SET(UTILITY_MODULE_DOCSTRING "is the python interface to the FRENSIE utilities package.")
SET(UTILITY_PACKAGES "")

SET(PyFrensie_PACKAGES ${PyFrensie_PACKAGES} Utility)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.Utility__init__)
SET(UTILITY_PACKAGES ${UTILITY_PACKAGES} Utility__init__)
SET(UTILITY_MODULE_INIT_PACKAGE Utility__init__)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.Prng)
SET(UTILITY_PACKAGES ${UTILITY_PACKAGES} Prng)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.MPI)
SET(UTILITY_PACKAGES ${UTILITY_PACKAGES} MPI)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.UnivariateDistribution)
SET(UTILITY_PACKAGES ${UTILITY_PACKAGES} UnivariateDistribution)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.BivariateDistribution)
SET(UTILITY_PACKAGES ${UTILITY_PACKAGES} BivariateDistribution)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.Distribution)
SET(UTILITY_PACKAGES ${UTILITY_PACKAGES} Distribution)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.Coordinate)
SET(UTILITY_PACKAGES ${UTILITY_PACKAGES} Coordinate)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.Mesh)
SET(UTILITY_PACKAGES ${UTILITY_PACKAGES} Mesh)

# SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.Interpolation)
SET(UTILITY_PACKAGE_LINK_LIBRARIES ${PYTHON_LIBRARIES} utility_core utility_dist utility_system utility_mesh pyfrensie_cpp)

# Add the Data package
SET(DATA_MODULE_DOCSTRING "is the python interface to the FRENSIE data package.")
SET(DATA_PACKAGES "")

SET(PyFrensie_PACKAGES ${PyFrensie_PACKAGES} Data)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Data.Data__init__)
SET(DATA_PACKAGES ${DATA_PACKAGES} Data__init__)
SET(DATA_MODULE_INIT_PACKAGE Data__init__)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Data.ACE)
SET(DATA_PACKAGES ${DATA_PACKAGES} ACE)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Data.ENDL)
SET(DATA_PACKAGES ${DATA_PACKAGES} ENDL)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Data.Native)
SET(DATA_PACKAGES ${DATA_PACKAGES} Native)

SET(DATA_PACKAGE_LINK_LIBRARIES ${PYTHON_LIBRARIES} data_core data_database data_ace data_endl data_native data_xsdir pyfrensie_cpp)

# Add the DataGen package
SET(DATA_GEN_MODULE_DOCSTRING "is the python interface to the FRENSIE data_gen package.")
SET(DATA_GEN_PACKAGES "")

SET(PyFrensie_PACKAGES ${PyFrensie_PACKAGES} DataGen)
SET(PyFrensie_MODULES ${PyFrensie_MODULES} DataGen.DataGen__init__)
SET(DATA_GEN_PACKAGES ${DATA_GEN_PACKAGES} DataGen__init__)
SET(DATA_GEN_MODULE_INIT_PACKAGE DataGen__init__)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} DataGen.ElectronPhoton)
SET(DATA_GEN_PACKAGES ${DATA_GEN_PACKAGES} ElectronPhoton)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} DataGen.ENDL)
SET(DATA_GEN_PACKAGES ${DATA_GEN_PACKAGES} ENDL)

SET(DATA_GEN_PACKAGE_LINK_LIBRARIES ${PYTHON_LIBRARIES} data_gen_electron_photon data_gen_endl pyfrensie_cpp)

# Add the Geometry package
SET(GEOMETRY_MODULE_DOCSTRING "is the python interface to the FRENSIE geometry package")
SET(GEOMETRY_PACKAGES "")

SET(PyFrensie_PACKAGES ${PyFrensie_PACKAGES} Geometry)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} Geometry.Geometry__init__)
SET(GEOMETRY_PACKAGES ${GEOMETRY_PACKAGES} Geometry__init__)
SET(GEOMETRY_MODULE_INIT_PACKAGE Geometry__init__)

SET(GEOMETRY_PACKAGE_LINK_LIBRARIES ${PYTHON_LIBRARIES} geometry_core utility_core pyfrensie_cpp)

IF(FRENSIE_ENABLE_DAGMC)
  SET(PyFrensie_MODULES ${PyFrensie_MODULES} Geometry.DagMC)
  SET(GEOMETRY_PACKAGES ${GEOMETRY_PACKAGES} DagMC)

  SET(GEOMETRY_PACKAGE_LINK_LIBRARIES ${GEOMETRY_PACKAGE_LINK_LIBRARIES} geometry_dagmc pyfrensie_cpp)
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  SET(PyFrensie_MODULES ${PyFrensie_MODULES} Geometry.ROOT)
  SET(GEOMETRY_PACKAGES ${GEOMETRY_PACKAGES} ROOT)

  SET(GEOMETRY_PACKAGE_LINK_LIBRARIES ${GEOMETRY_PACKAGE_LINK_LIBRARIES} geometry_root pyfrensie_cpp)
ENDIF()

# Add the MonteCarlo package
SET(MONTE_CARLO_MODULE_DOCSTRING "is the python interface to the FRENSIE monte_carlo package.")
SET(MONTE_CARLO_PACKAGES "")

SET(PyFrensie_PACKAGES ${PyFrensie_PACKAGES} MonteCarlo)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} MonteCarlo.MonteCarlo__init__)
SET(MONTE_CARLO_PACKAGES ${MONTE_CARLO_PACKAGES} MonteCarlo__init__)
SET(MONTE_CARLO_MODULE_INIT_PACKAGE MonteCarlo__init__)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} MonteCarlo.Material)
SET(MONTE_CARLO_PACKAGES ${MONTE_CARLO_PACKAGES} Material)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} MonteCarlo.GeometryModel)
SET(MONTE_CARLO_PACKAGES ${MONTE_CARLO_PACKAGES} GeometryModel)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} MonteCarlo.Collision)
SET(MONTE_CARLO_PACKAGES ${MONTE_CARLO_PACKAGES} Collision)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} MonteCarlo.Photon)
SET(MONTE_CARLO_PACKAGES ${MONTE_CARLO_PACKAGES} Photon)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} MonteCarlo.Electron)
SET(MONTE_CARLO_PACKAGES ${MONTE_CARLO_PACKAGES} Electron)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} MonteCarlo.ActiveRegion)
SET(MONTE_CARLO_PACKAGES ${MONTE_CARLO_PACKAGES} ActiveRegion)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} MonteCarlo.Event)
SET(MONTE_CARLO_PACKAGES ${MONTE_CARLO_PACKAGES} Event)

SET(PyFrensie_MODULES ${PyFrensie_MODULES} MonteCarlo.Manager)
SET(MONTE_CARLO_PACKAGES ${MONTE_CARLO_PACKAGES} Manager)

SET(MONTE_CARLO_PACKAGE_LINK_LIBRARIES ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} monte_carlo_core monte_carlo_collision_core monte_carlo_collision_neutron monte_carlo_collision_photon monte_carlo_collision_electron monte_carlo_collision_kernel monte_carlo_active_region_core monte_carlo_active_region_response monte_carlo_active_region_source monte_carlo_event_core monte_carlo_event_estimator monte_carlo_event_particle_tracker monte_carlo_event_dispatcher monte_carlo_manager pyfrensie_cpp)

# Add the PyFrensie subdirectory
ADD_SUBDIRECTORY(PyFrensie)

# Track all PyFrensie targets
SET(PyFrensie_TARGETS pyfrensie_cpp)

# Loop over the PyFrensie modules and parse the corresponding swig .i files
FOREACH(MODULE ${PyFrensie_MODULES})

  # Set the module interface file properties
  SET_SOURCE_FILES_PROPERTIES(${MODULE}.i PROPERTIES CPLUSPLUS ON)

  # Determine the swig module output directory, name and unique target name
  SWIG_MODULE_GET_OUTDIR_AND_MODULE(${MODULE}.i MODULE_OUTDIR MODULE_NAME)

  # Define the target for this module
  STRING(TOUPPER ${MODULE} MODULE_UPPER)
  STRING(REPLACE "." "_" MODULE_NODOT ${MODULE})
  SET(PyFrensie_TARGET_NAME ${MODULE_NODOT})
  LIST(APPEND PyFrensie_TARGETS ${PyFrensie_TARGET_NAME})
  SWIG_ADD_MODULE(${PyFrensie_TARGET_NAME}
    python
    "${MODULE}.i"
    "${MODULE_OUTDIR}"
    "${MODULE_NAME}")
  SET_PROPERTY(TARGET ${PyFrensie_TARGET_NAME} PROPERTY NO_SONAME 1)

  IF("${MODULE_OUTDIR}" MATCHES "PyFrensie/Utility")
    SWIG_LINK_LIBRARIES(${PyFrensie_TARGET_NAME} ${UTILITY_PACKAGE_LINK_LIBRARIES})
    # Byte compile the generated python files
    ADD_CUSTOM_COMMAND(TARGET ${PyFrensie_TARGET_NAME} POST_BUILD
      COMMAND ${PYTHON_EXECUTABLE} -c "import py_compile; py_compile.compile('PyFrensie/Utility/${MODULE_NAME}.py')"
      COMMENT "Byte compiling Utility/${MODULE_NAME}.py"
      VERBATIM)

    # Install the generated files
    INSTALL(TARGETS ${PyFrensie_TARGET_NAME}
      DESTINATION ${PyFrensie_INSTALL_DIR}/Utility)
    INSTALL(FILES
      ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie/Utility/${MODULE_NAME}.py
      ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie/Utility/${MODULE_NAME}.pyc
      DESTINATION ${PyFrensie_INSTALL_DIR}/Utility)

  # The DataGen package must be compiled before the Data package or
  ELSEIF("${MODULE_OUTDIR}" MATCHES "PyFrensie/DataGen")
    SWIG_LINK_LIBRARIES(${PyFrensie_TARGET_NAME} ${DATA_GEN_PACKAGE_LINK_LIBRARIES})

    # Byte compile the generated python files
    ADD_CUSTOM_COMMAND(TARGET ${PyFrensie_TARGET_NAME} POST_BUILD
      COMMAND ${PYTHON_EXECUTABLE} -c "import py_compile; py_compile.compile('PyFrensie/DataGen/${MODULE_NAME}.py')"
      COMMENT "Byte compiling DataGen/${MODULE_NAME}.py"
      VERBATIM)

    # Install the generated files
    INSTALL(TARGETS ${PyFrensie_TARGET_NAME}
      DESTINATION ${PyFrensie_INSTALL_DIR}/DataGen)
    INSTALL(FILES
      ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie/DataGen/${MODULE_NAME}.py
      ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie/DataGen/${MODULE_NAME}.pyc
      DESTINATION ${PyFrensie_INSTALL_DIR}/DataGen)

  ELSEIF("${MODULE_OUTDIR}" MATCHES "PyFrensie/Data")
    SWIG_LINK_LIBRARIES(${PyFrensie_TARGET_NAME} ${DATA_PACKAGE_LINK_LIBRARIES})

    # Byte compile the generated python files
    ADD_CUSTOM_COMMAND(TARGET ${PyFrensie_TARGET_NAME} POST_BUILD
      COMMAND ${PYTHON_EXECUTABLE} -c "import py_compile; py_compile.compile('PyFrensie/Data/${MODULE_NAME}.py')"
      COMMENT "Byte compiling Data/${MODULE_NAME}.py"
      VERBATIM)

    # Install the generated files
    INSTALL(TARGETS ${PyFrensie_TARGET_NAME}
      DESTINATION ${PyFrensie_INSTALL_DIR}/Data)
    INSTALL(FILES
      ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie/Data/${MODULE_NAME}.py
      ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie/Data/${MODULE_NAME}.pyc
      DESTINATION ${PyFrensie_INSTALL_DIR}/Data)

  ELSEIF("${MODULE_OUTDIR}" MATCHES "PyFrensie/Geometry")
    SWIG_LINK_LIBRARIES(${PyFrensie_TARGET_NAME} ${GEOMETRY_PACKAGE_LINK_LIBRARIES})

    # Byte compile the generator python files
    ADD_CUSTOM_COMMAND(TARGET ${PyFrensie_TARGET_NAME} POST_BUILD
      COMMAND ${PYTHON_EXECUTABLE} -c "import py_compile; py_compile.compile('PyFrensie/Geometry/${MODULE_NAME}.py')"
      COMMENT "Byte compiling Geometry/${MODULE_NAME}.py"
      VERBATIM)

    # Install the generated files
    INSTALL(TARGETS ${PyFrensie_TARGET_NAME}
      DESTINATION ${PyFrensie_INSTALL_DIR}/Geometry)
    INSTALL(FILES
      ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie/Geometry/${MODULE_NAME}.py
      ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie/Geometry/${MODULE_NAME}.pyc
      DESTINATION ${PyFrensie_INSTALL_DIR}/Geometry)

  ELSEIF("${MODULE_OUTDIR}" MATCHES "PyFrensie/MonteCarlo")
    SWIG_LINK_LIBRARIES(${PyFrensie_TARGET_NAME} ${MONTE_CARLO_PACKAGE_LINK_LIBRARIES})

    # Byte compile the generator python files
    ADD_CUSTOM_COMMAND(TARGET ${PyFrensie_TARGET_NAME} POST_BUILD
      COMMAND ${PYTHON_EXECUTABLE} -c "import py_compile; py_compile.compile('PyFrensie/MonteCarlo/${MODULE_NAME}.py')"
      COMMENT "Byte compiling MonteCarlo/${MODULE_NAME}.py"
      VERBATIM)

    # Install the generated files
    INSTALL(TARGETS ${PyFrensie_TARGET_NAME}
      DESTINATION ${PyFrensie_INSTALL_DIR}/MonteCarlo)
    INSTALL(FILES
      ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie/MonteCarlo/${MODULE_NAME}.py
      ${CMAKE_CURRENT_BINARY_DIR}/PyFrensie/MonteCarlo/${MODULE_NAME}.pyc
      DESTINATION ${PyFrensie_INSTALL_DIR}/MonteCarlo)

  ENDIF()

ENDFOREACH(MODULE)

# Add the PyFrensie package custom target
ADD_CUSTOM_TARGET(pyfrensie
  DEPENDS ${PyFrensie_TARGETS})
