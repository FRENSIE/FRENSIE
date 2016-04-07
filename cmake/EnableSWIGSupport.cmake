# Configure the SWIG options that will be required in this project. The
# following variables will be set
# 1.) 
MACRO(ENABLE_SWIG_SUPPORT)
  
  FIND_PACKAGE(SWIG 3.0.8 REQUIRED)
  INCLUDE(${SWIG_USE_FILE})

  FIND_PACKAGE(PythonLibs)
  INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

  SET(CMAKE_SWIG_FLAGS "")
  
ENDMACRO()