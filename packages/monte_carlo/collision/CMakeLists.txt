# Set up the collision subpackage directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(photon)
INCLUDE_DIRECTORIES(photon/src)

ADD_SUBDIRECTORY(electron)
INCLUDE_DIRECTORIES(electron/src)

ADD_SUBDIRECTORY(neutron)
INCLUDE_DIRECTORIES(neutron/src)

ADD_SUBDIRECTORY(kernel)
INCLUDE_DIRECTORIES(kernel/src)
