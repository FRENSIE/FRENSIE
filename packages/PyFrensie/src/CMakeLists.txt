# Create the utility module
SET_SOURCE_FILES_PROPERTIES(Utility.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(Utility python Utility.i)
SWIG_LINK_LIBRARIES(Utility ${PYTHON_LIBRARIES} "${CMAKE_BINARY_DIR}/packages/utility/distribution/src/libutility_dist.so" "${CMAKE_BINARY_DIR}/packages/utility/prng/src/libutility_prng.so" ${TEUCHOS_CORE})
INSTALL(TARGETS ${SWIG_MODULE_Utility_REAL_NAME}
  DESTINATION ${PyFrensie_INSTALL_DIR})
ADD_CUSTOM_COMMAND(TARGET ${SWIG_MODULE_Utility_REAL_NAME} POST_BUILD
  COMMAND ${PYTHON_EXECUTABLE} -c "import py_compile; py_compile.compile('Utility.py')"
  COMMENT "Byte compiling Utility.py"
  VERBATIM)
INSTALL(FILES 
  ${CMAKE_CURRENT_BINARY_DIR}/Utility.py
  ${CMAKE_CURRENT_BINARY_DIR}/Utility.pyc
  DESTINATION ${PyFrensie_INSTALL_DIR})
LIST(APPEND PyFrensie_MODULES Utility)

# Add the PyFrensie subdirectory
ADD_SUBDIRECTORY(PyFrensie)