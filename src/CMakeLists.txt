SET(HEADERS
  Tuple.hpp
  DefaultParameterValues.hpp
  ENDLIB97FileHandler.hpp
  DataProcessor.hpp
  FACEMC_Assertion.hpp
  ExceptionCatchMacros.hpp
  ArrayTraits.hpp
  HDF5TypeTraits.hpp
  SearchAlgorithms.hpp
  TupleMemberTraits.hpp
  PhotonDataBasic.hpp
  PhotonDataFluorescence.hpp
  PhotonDataDopplerBroadening.hpp
  PhotonData.hpp
  Surface.hpp
  SetOperationFunctor.hpp
  BooleanCellFunctor.hpp
  Cell.hpp
  CellFactory.hpp
  ${HEADERS}
  )

SET(SOURCES
  ENDLIB97FileHandler.cpp
  DataProcessor.cpp
  HDF5FileHandler.cpp
  PhotonDataProcessor.cpp
  process_data.cpp
  PhotonDataBasic.cpp
  PhotonDataFluorescence.cpp
  PhotonDataDopplerBroadening.cpp
  BooleanCellFunctor.cpp
  Cell.cpp
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
  ENDLIB97FileHandler.cpp
  DataProcessor.cpp
  PhotonDataProcessor.cpp
  HDF5FileHandler.cpp)

TARGET_LINK_LIBRARIES(process_data ${TEUCHOS_CORE} ${HDF5})

INSTALL(TARGETS ${TARGETS}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
INSTALL(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)