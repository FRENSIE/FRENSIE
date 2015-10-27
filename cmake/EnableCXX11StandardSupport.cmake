# Enable C++11 standard support
MACRO(ENABLE_CXX11_STANDARD_SUPPORT)

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fext-numeric-literals")

ENDMACRO()