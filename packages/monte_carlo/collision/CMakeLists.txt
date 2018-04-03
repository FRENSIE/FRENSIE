# Set up the collision subpackage directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(photon)
INCLUDE_DIRECTORIES(photon/src)
