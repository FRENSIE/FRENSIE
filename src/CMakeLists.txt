SET(HEADERS
  Tuple.hpp
  DefaultParameterValues.hpp
  EPDL97DataProcessor.hpp
  FACEMC_Assertion.hpp
  ExceptionCatchMacros.hpp
  HDF5FileHandler.hpp
  HDF5TypeTraits.hpp
  HDF5ArrayPolicy.hpp
  PhotonDataCollection.hpp
  SimulationBase.hpp
  ElectronShells.hpp
  SearchAlgorithms.hpp
  TupleComparePolicy.hpp
  PhotonDataBasic.hpp
  ${HEADERS}
  )

SET(SOURCES
  EPDL97DataProcessor.cpp
  HDF5FileHandler.cpp
  PhotonDataProcessor.cpp
  process_data.cpp
  PhotonDataBasic.cpp
  ${SOURCES}
  )

SET(TARGETS
  process_data
  ${TARGETS}
  )

IF(CMAKE_VERBOSE_CONFIGURE)
  MESSAGE("HEADERS = ${HEADERS}")
  MESSAGE("SOURCES = ${SOURCES}")
  MESSAGE("TARGETS = ${TARGETS}")
ENDIF()

ADD_EXECUTABLE(process_data
  process_data.cpp
  EPDL97DataProcessor.cpp
  PhotonDataProcessor.cpp
  HDF5FileHandler.cpp)

TARGET_LINK_LIBRARIES(process_data ${TEUCHOS} ${HDF5})

INSTALL(TARGETS ${TARGETS}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
INSTALL(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)