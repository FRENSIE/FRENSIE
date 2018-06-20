# Set up the estimator subpackage directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)
 
# ADD_SUBDIRECTORY(estimator)
# INCLUDE_DIRECTORIES(estimator/src)
 
# ADD_SUBDIRECTORY(particle_tracker)
# INCLUDE_DIRECTORIES(particle_tracker/src)

ADD_SUBDIRECTORY(forced_collisions)
INCLUDE_DIRECTORIES(forced_collisions/src)

# ADD_SUBDIRECTORY(weight_windows)
# INCLUDE_DIRECTORIES(weight_windows/src)

# ADD_SUBDIRECTORY(dispatcher)
# INCLUDE_DIRECTORIES(dispatcher/src) 

# ADD_SUBDIRECTORY(interface)
