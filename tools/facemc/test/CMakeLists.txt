# Compute the relative path to the mcnp data directory
IF(DEFINED MCNP_DATA_DIR)

  # Check if the mcnp data dir is valid
  IF(NOT EXISTS ${MCNP_DATA_DIR})
    MESSAGE(FATAL_ERROR "The supplied mcnp data directory is not valid!" )
  ELSEIF(NOT EXISTS ${MCNP_DATA_DIR}/endf70a)
    MESSAGE(FATAL_ERROR "The supplied mcnp data directory is not valid!" )
  ENDIF()
  
  FILE(RELATIVE_PATH MCNP_DATA_DIR_REL_PATH ${CMAKE_CURRENT_BINARY_DIR} ${MCNP_DATA_DIR})

  # Configure the cross_sections.xml file
  CONFIGURE_FILE(mcnp_cross_sections.xml.in ${CMAKE_CURRENT_BINARY_DIR}/cross_sections.xml)

ENDIF()