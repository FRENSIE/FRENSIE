# Configure the MPI options that will be required in a project using MPI
MACRO(ENABLE_MPI_SUPPORT)
  
  # Find the default MPI package available on this system
  FIND_PACKAGE("MPI" REQUIRED)
  
  # Add the MPI-specific compile and linker flags and include paths  
  LIST(APPEND CMAKE_CXX_COMPILE_FLAGS ${MPI_CXX_COMPILE_FLAGS})
  LIST(APPEND CMAKE_CXX_LINK_FLAGS ${MPI_CXX_LINK_FLAGS})
  INCLUDE_DIRECTORIES(${MPI_CXX_INCLUDE_PATH})

ENDMACRO()