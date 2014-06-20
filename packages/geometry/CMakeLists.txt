# Set up the geometry package directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(dagmc)
INCLUDE_DIRECTORIES(damgc/src)

ADD_SUBDIRECTORY(native)
INCLUDE_DIRECTORIES(native/src)

ADD_SUBDIRECTORY(interface)
