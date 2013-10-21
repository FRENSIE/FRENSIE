# Include all of the macros that you've defined here
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/EnforceOutOfSourceBuild.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/EnableMPISupport.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/EnableTrilinosSupport.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/EnableMoabSupport.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/EnableHDF5Support.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/EnableBoostSupport.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/EnableSprngSupport.cmake)