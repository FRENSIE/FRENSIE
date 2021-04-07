# Set up the estimator subpackage directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(estimator)
INCLUDE_DIRECTORIES(estimator/src)

ADD_SUBDIRECTORY(particle_tracker)
INCLUDE_DIRECTORIES(particle_tracker/src)

ADD_SUBDIRECTORY(forced_collisions)
INCLUDE_DIRECTORIES(forced_collisions/src)

ADD_SUBDIRECTORY(population_control)
INCLUDE_DIRECTORIES(population_control/src)

ADD_SUBDIRECTORY(weight_cutoff)
INCLUDE_DIRECTORIES(weight_cutoff/src)

ADD_SUBDIRECTORY(dispatcher)
INCLUDE_DIRECTORIES(dispatcher/src)
