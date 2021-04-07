# Configure the OpenMP options that will be required in a project using OpenMP
MACRO(ENABLE_OPENMP_SUPPORT)

  # Find the default OpenMP package available on this system
  FIND_PACKAGE("OpenMP" REQUIRED)

  # Add the OpenMP-specific compile and linker flags and include paths
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  SET(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${OpenMP_Fortran_FLAGS}")

ENDMACRO()