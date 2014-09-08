# Set up the geometry package directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

IF(FRENSIE_ENABLE_DAGMC)
  ADD_SUBDIRECTORY(dagmc)	
  INCLUDE_DIRECTORIES(damgc/src)
ENDIF()

#ADD_SUBDIRECTORY(native)
#INCLUDE_DIRECTORIES(native/src)

ADD_SUBDIRECTORY(interface)
