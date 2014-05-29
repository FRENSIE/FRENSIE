# Set up the facemc package directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(source)

ADD_SUBDIRECTORY(estimator)

ADD_SUBDIRECTORY(collision)