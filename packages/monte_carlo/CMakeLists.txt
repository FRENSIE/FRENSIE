# Set up the monte carlo package directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(collision)
<<<<<<< HEAD
INCLUDE_DIRECTORIES(collision/core/src collision/interface collision/neutron/src collision/photon/src collision/electron/src)
=======
INCLUDE_DIRECTORIES(collision/core/src collision/photon/src collision/electron/src collision/neutron/src collision/kernel/src)
>>>>>>> 3675d6aeb55d11849e18cf820eff8fd9c43d5ef2

ADD_SUBDIRECTORY(active_region)
INCLUDE_DIRECTORIES(active_region/core/src)

ADD_SUBDIRECTORY(event)
INCLUDE_DIRECTORIES(event/core/src event/estimator/src event/particle_tracker/src event/weight_window/src event/dispatcher/src)

ADD_SUBDIRECTORY(manager)
INCLUDE_DIRECTORIES(manager/src)
