# Create the PyFrensie_ALL string
SET(PyFrensie_ALL "__all__ = [")
FOREACH(PACKAGE ${PyFrensie_PACKAGES})
  SET(PyFrensie_ALL "${PyFrensie_ALL}'${PACKAGE}',\n          ")
ENDFOREACH()
SET(PyFrensie_ALL "${PyFrensie_ALL}]")

# Add a new target
ADD_CUSTOM_TARGET(Local_Python_Modules ALL)

# Define the local python modules
SET(LOCAL_MODULES __init__)

# Create the local python modules
FOREACH(MODULE ${LOCAL_MODULES})

  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}.py.in
    ${CMAKE_CURRENT_BINARY_DIR}/${MODULE}.py)
  ADD_CUSTOM_COMMAND(TARGET Local_Python_Modules
    COMMAND ${PYTHON_EXECUTABLE} -c "import py_compile; py_compile.compile('${MODULE}.py')"
    COMMENT "Byte compiling ${MODULE}.py"
    VERBATIM)
  INSTALL(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${MODULE}.py
    ${CMAKE_CURRENT_BINARY_DIR}/${MODULE}.pyc
    DESTINATION ${PyFrensie_INSTALL_DIR})

ENDFOREACH()
    