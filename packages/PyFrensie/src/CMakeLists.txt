# Create the swig runtime header use by the PyFrensie library
SET(SWIG_RUNTIME swigpyrun.h)
EXECUTE_PROCESS(COMMAND ${SWIG_EXECUTABLE} -python -external-runtime
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  OUTPUT_FILE ${SWIG_RUNTIME})
LIST(APPEND HEADERS ${CMAKE_CURRENT_BINARY_DIR}/${SWIG_RUNTIME})

# Set the PyTrilinos package headers and sources
SET(HEADERS "")
SET(SOURCES "")

LIST(APPEND HEADERS
  PyFrensie_NumPyTypeTraitsDecl.hpp
  PyFrensie_NumPyTypeTraits.hpp
  PyFrensie_ArrayConversionHelpers.hpp
  PyFrensie_DistributionHelpers.hpp)

INSTALL(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

# Set up the include paths
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${PYTRILINOS_SRC_DIR_PATH})

# Initialize the package and module lists
SET(PyFrensie_PACKAGES "")
SET(PyFrensie_MODULES "")

# Add the utility package
SET(PyFrensie_PACKAGES ${PyFrensie_PACKAGES} Utility)
SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.__init__)
SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.Prng)
SET(PyFrensie_MODULES ${PyFrensie_MODULES} Utility.Distribution)
SET(UTILITY_PACKAGE_LINK_LIBRARIES ${PYTHON_LIBRARIES} utility_core utility_dist ${TEUCHOS_CORE} ${PYTRILINOS})

# Add the data package
SET(PyFrensie_PACKAGES ${PyFrensie_PACKAGES} Data)
SET(PyFrensie_MODULES ${PyFrensie_MODULES} Data.__init__)
SET(PyFrensie_MODULES ${PyFrensie_MODULES} Data.ACE)
SET(PyFrensie_MODULES ${PyFrensie_MODULES} Data.Native)
SET(DATA_PACKAGE_LINK_LIBRARIES ${PYTHON_LIBRARIES} data_ace data_native ${TEUCHOS_CORE} ${PYTRILINOS})

# Add the geometry package
SET(PyFrensie_PACKAGES ${PyFrensie_PACKAGES} Geometry)
SET(PyFrensie_MODULES ${PyFrensie_MODULES} Geometry.__init__)

SET(GEOMETRY_PACKAGE_LINK_LIBRARIES ${PYTHON_LIBRARIES} geometry_core ${TEUCHOS_CORE} ${PYTRILINOS})
SET(PyFrensie_Geometry_PACKAGES "")

IF(FRENSIE_ENABLE_DAGMC)
  SET(PyFrensie_Geometry_PACKAGES ${PyFrensie_Geometry_PACKAGES} DagMC)
  SET(PyFrensie_MODULES ${PyFrensie_MODULES} Geometry.DagMC)
  SET(GEOMETRY_PACKAGE_LINK_LIBRARIES ${GEOMETRY_PACKAGE_LINK_LIBRARIES} geometry_dagmc)
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  SET(PyFrensie_Geometry_PACKAGES ${PyFrensie_Geometry_PACKAGES} ROOT)
  SET(PyFrensie_MODULES ${PyFrensie_MODULES} Geometry.ROOT)
  SET(GEOMETRY_PACKAGE_LINK_LIBRARIES ${GEOMETRY_PACKAGE_LINK_LIBRARIES} geometry_root)
ENDIF()

SET(PyFrensie_Geometry_ALL "__all__ = [")
FOREACH(PACKAGE ${PyFrensie_Geometry_PACKAGES})
  SET(PyFrensie_Geometry_ALL "${PyFrensie_Geometry_ALL}'${PACKAGE}',\n          ")
ENDFOREACH()
SET(PyFrensie_Geometry_ALL "${PyFrensie_Geometry_ALL}]")

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Geometry_Config.i.in
  ${CMAKE_CURRENT_BINARY_DIR}/Geometry_Config.i)

# Add the PyFrensie subdirectory
ADD_SUBDIRECTORY(PyFrensie)

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
  ENDIF()

ENDFOREACH(MODULE)
