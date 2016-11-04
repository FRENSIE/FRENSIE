# Set up the monte carlo package directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

ADD_SUBDIRECTORY(source)
INCLUDE_DIRECTORIES(source/core/src source/interface source/native/src)

ADD_SUBDIRECTORY(collision)
INCLUDE_DIRECTORIES(collision/core/src collision/interface collision/native/src)

ADD_SUBDIRECTORY(event)
INCLUDE_DIRECTORIES(event/core/src event/interface event/native/src)

ADD_SUBDIRECTORY(manager)
INCLUDE_DIRECTORIES(manager/src)
