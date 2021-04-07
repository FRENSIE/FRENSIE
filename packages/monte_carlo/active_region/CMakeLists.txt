# Set up the source subpackage directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(response)
INCLUDE_DIRECTORIES(response/src)

ADD_SUBDIRECTORY(source)
INCLUDE_DIRECTORIES(source/src)
