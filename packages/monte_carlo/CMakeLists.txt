# Set up the monte carlo package directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(collision)
INCLUDE_DIRECTORIES(collision/core/src collision/photon/src collision/electron/src collision/neutron/src collision/kernel/src)

ADD_SUBDIRECTORY(active_region)
INCLUDE_DIRECTORIES(active_region/core/src active_region/source/src active_region/response/src)

ADD_SUBDIRECTORY(event)
INCLUDE_DIRECTORIES(event/core/src event/estimator/src event/particle_tracker/src event/population_control/src event/weight_cutoff/src event/forced_collisions/src event/dispatcher/src)

ADD_SUBDIRECTORY(manager)
INCLUDE_DIRECTORIES(manager/src)
