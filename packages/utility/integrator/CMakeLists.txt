# Set up the integrator subpackage directory hierarchy
ADD_SUBDIRECTORY(src)
INCLUDE_DIRECTORIES(src ${CMAKE_CURRENT_BINARY_DIR}/src)

ADD_SUBDIRECTORY(test)
