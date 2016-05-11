##---------------------------------------------------------------------------##
## Macro for making a PyFrensie python test
##---------------------------------------------------------------------------##
MACRO(PyFrensie_MAKE_TEST TEST_NAME)

  ADD_CUSTOM_COMMAND(OUTPUT ${TEST_NAME}.py
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/copyWithCMakeSubstitutions.py
            ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.py.in
	    ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}.py
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.py.in)

  ADD_CUSTOM_TARGET(PyFrensie_${TEST_NAME} ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}.py)
  
ENDMACRO()
