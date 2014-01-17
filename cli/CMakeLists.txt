# Create the data processor
ADD_EXECUTABLE(process_data process_data.cpp)
TARGET_LINK_LIBRARIES(process_data ${PROJECT_NAME})

INSTALL(TARGETS process_data
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)