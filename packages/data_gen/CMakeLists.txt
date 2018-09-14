# Set up the data gen package directory hierarchy
ADD_SUBDIRECTORY(endl)
INCLUDE_DIRECTORIES(endl/src)

ADD_SUBDIRECTORY(electron_photon)
INCLUDE_DIRECTORIES(electron_photon/src)

ADD_SUBDIRECTORY(free_gas_sab)
INCLUDE_DIRECTORIES(free_gas_sab/src)
