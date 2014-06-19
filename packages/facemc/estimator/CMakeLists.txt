# Set up the estimator subpackage directory hierarchy
 ADD_SUBDIRECTORY(core)
 INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(native)
INCLUDE_DIRECTORIES(native/src)

# ADD_SUBDIRECTORY(interface)
