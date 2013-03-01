SET(HEADERS
  Tuple.hpp
  DefaultParameterValues.hpp
  EPDL97DataProcessor.hpp
  FACEMC_Assertion.hpp
  HDF5DataFileNames.hpp
  HDF5ExceptionCatchMacro.hpp
  HDF5FileHandler.hpp
  HDF5TypeTraits.hpp
  HDF5ArrayPolicy.hpp
  PhotonDataCollection.hpp
  SimulationBase.hpp
  ElectronShells.hpp
  ${HEADERS}
  )

SET(SOURCES
  EPDL97DataProcessor.cpp
  HDF5FileHandler.cpp
  PhotonDataProcessor.cpp
  ${SOURCES}
  )

SET(TARGETS
  ${TARGETS}
  )

IF(CMAKE_VERBOSE_CONFIGURE)
  MESSAGE("HEADERS = ${HEADERS}")
  MESSAGE("SOURCES = ${SOURCES}")
  MESSAGE("TARGETS = ${TARGETS}")
ENDIF()

INSTALL(TARGETS ${TARGETS}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)