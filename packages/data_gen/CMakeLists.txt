# Set up the data gen package directory hierarchy
ADD_SUBDIRECTORY(adjoint_photon)
INCLUDE_DIRECTORIES(adjoint_photon/src)

ADD_SUBDIRECTORY(free_gas_sab)
INCLUDE_DIRECTORIES(free_gas_sab/src)