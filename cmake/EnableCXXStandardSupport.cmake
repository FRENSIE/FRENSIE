# Enable C++11 standard support
MACRO(ENABLE_CXX_STANDARD_SUPPORT STD_NUMBER)

  IF(${STD_NUMBER} EQUAL 11)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fext-numeric-literals")
  ELSEIF(${STD_NUMBER} EQUAL 14)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fext-numeric-literals")
  ELSEIF(${STD_NUMBER} EQUAL 17)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fext_numeric_literals")
  ELSE()
    MESSAGE(FATAL_ERROR "Support for c++ standard ${STD_NUMBER} could not be "
      "set up because that standard is unknown!")
  ENDIF()      

ENDMACRO()
