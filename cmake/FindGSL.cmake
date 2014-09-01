# Try to find gnu scientific library GSL
# See 
# http://www.gnu.org/software/gsl/  and 
# http://gnuwin32.sourceforge.net/packages/gsl.htm
#
# Based on a script of Felix Woelk and Jan Woetzel
# (www.mip.informatik.uni-kiel.de)
# 
# It defines the following variables:
#  GSL_FOUND - system has GSL lib
#  GSL_INCLUDE_DIRS - where to find headers 
#  GSL_LIBRARIES - full path to the libraries
#  GSL_LIBRARY_DIRS, the directory where the PLplot library is found.
#  GSL_LIBRARY - full path to the gsl library
#  CMAKE_GSL_CXX_FLAGS  = Unix compiler flags for GSL, essentially "`gsl-config --cxxflags`"
#  GSL_LINK_DIRECTORIES = link directories, useful for rpath on Unix
#  GSL_EXE_LINKER_FLAGS = rpath on Unix
SET( GSL_FOUND OFF )
SET( GSL_CBLAS_FOUND OFF )

# Windows, but not for Cygwin and MSys where gsl-config is available
IF( WIN32 AND NOT CYGWIN AND NOT MSYS )
  # look for headers
  FIND_PATH( GSL_INCLUDE_DIR
    NAMES gsl/gsl_cdf.h gsl/gsl_randist.h
    )
  IF( GSL_INCLUDE_DIR )
    # look for gsl library
    FIND_LIBRARY( GSL_LIBRARY 
      NAMES gsl 
      )  
    IF( GSL_LIBRARY )
      SET( GSL_INCLUDE_DIRS ${GSL_INCLUDE_DIR} )
      GET_FILENAME_COMPONENT( GSL_LIBRARY_DIRS ${GSL_LIBRARY} PATH )
      SET( GSL_FOUND ON )
    ENDIF( GSL_LIBRARY )
    
    # look for gsl cblas library
    FIND_LIBRARY( GSL_CBLAS_LIBRARY
      NAMES gslcblas 
      )
    IF( GSL_CBLAS_LIBRARY )
      SET( GSL_CBLAS_FOUND ON )
    ENDIF( GSL_CBLAS_LIBRARY )
    
    SET( GSL_LIBRARIES ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} )
  ENDIF( GSL_INCLUDE_DIR )
  
  MARK_AS_ADVANCED(
    GSL_INCLUDE_DIR
    GSL_LIBRARY
    GSL_CBLAS_LIBRARY
    )
ELSE( WIN32 AND NOT CYGWIN AND NOT MSYS )
  IF( UNIX OR MSYS )
    FIND_PROGRAM( GSL_CONFIG_EXECUTABLE gsl-config
      /usr/bin/
      /usr/local/bin
      )
    
    IF( GSL_CONFIG_EXECUTABLE ) 
      SET( GSL_FOUND ON )
      
      # run the gsl-config program to get cxxflags
      EXECUTE_PROCESS(
        COMMAND sh "${GSL_CONFIG_EXECUTABLE}" --cflags
        OUTPUT_VARIABLE GSL_CFLAGS
        RESULT_VARIABLE RET
        ERROR_QUIET
        )
      IF( RET EQUAL 0 )
        STRING( STRIP "${GSL_CFLAGS}" GSL_CFLAGS )
        SEPARATE_ARGUMENTS( GSL_CFLAGS )
	
        # parse definitions from cflags; drop -D* from CFLAGS
        STRING( REGEX MATCHALL "-D[^;]+"
          GSL_DEFINITIONS  "${GSL_CFLAGS}" )
        STRING( REGEX REPLACE "-D[^;]+;" ""
          GSL_CFLAGS "${GSL_CFLAGS}" )
	
        # parse include dirs from cflags; drop -I prefix
        STRING( REGEX MATCHALL "-I[^;]+"
          GSL_INCLUDE_DIRS "${GSL_CFLAGS}" )
        STRING( REPLACE "-I" ""
          GSL_INCLUDE_DIRS "${GSL_INCLUDE_DIRS}")
        STRING( REGEX REPLACE "-I[^;]+;" ""
          GSL_CFLAGS "${GSL_CFLAGS}")
	
        MESSAGE("GSL_DEFINITIONS=${GSL_DEFINITIONS}")
        MESSAGE("GSL_INCLUDE_DIRS=${GSL_INCLUDE_DIRS}")
        MESSAGE("GSL_CFLAGS=${GSL_CFLAGS}")
      ELSE( RET EQUAL 0 )
        SET( GSL_FOUND FALSE )
      ENDIF( RET EQUAL 0 )
      
      # run the gsl-config program to get the libs
      EXECUTE_PROCESS(
        COMMAND sh "${GSL_CONFIG_EXECUTABLE}" --libs
        OUTPUT_VARIABLE GSL_LIBRARIES
        RESULT_VARIABLE RET
        ERROR_QUIET
        )
      IF( RET EQUAL 0 )
        STRING(STRIP "${GSL_LIBRARIES}" GSL_LIBRARIES )
        SEPARATE_ARGUMENTS( GSL_LIBRARIES )
	  
        # extract linkdirs (-L) for rpath (i.e., LINK_DIRECTORIES)
        STRING( REGEX MATCHALL "-L[^;]+"
          GSL_LIBRARY_DIRS "${GSL_LIBRARIES}" )
        STRING( REPLACE "-L" ""
          GSL_LIBRARY_DIRS "${GSL_LIBRARY_DIRS}" )
      ELSE( RET EQUAL 0 )
        SET( GSL_FOUND FALSE )
      ENDIF( RET EQUAL 0 )
      
      MARK_AS_ADVANCED(
        GSL_CFLAGS
	)
      MESSAGE( STATUS "Using GSL from ${GSL_PREFIX}" )
    ELSE( GSL_CONFIG_EXECUTABLE )
      MESSAGE( STATUS "FindGSL: gsl-config not found.")
    ENDIF( GSL_CONFIG_EXECUTABLE )
  ENDIF( UNIX OR MSYS )
ENDIF( WIN32 AND NOT CYGWIN AND NOT MSYS )

IF( GSL_FOUND )
  IF( NOT GSL_FIND_QUIETLY )
    MESSAGE( STATUS "FindGSL: Found both GSL headers and library" )
  ENDIF( NOT GSL_FIND_QUIETLY )
ELSE( GSL_FOUND )
  IF( GSL_FIND_REQUIRED )
    MESSAGE( FATAL_ERROR "FindGSL: Could not find GSL headers or library" )
  ENDIF( GSL_FIND_REQUIRED )
ENDIF( GSL_FOUND )