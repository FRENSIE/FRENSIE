# Compute the relative path to the mcnp data directory
ADD_SUBDIRECTORY(h1-2500k)

IF(${FRENSIE_ENABLE_DAGMC})
  IF(DEFINED MCNP_DATA_DIR)

    SET(FACEMC_CORE_CPP "../src/facemcCore.cpp")

    # Check if the mcnp data dir is valid
    IF(NOT EXISTS ${MCNP_DATA_DIR})
      MESSAGE(FATAL_ERROR "The supplied mcnp data directory is not valid!" )
    ELSEIF(NOT EXISTS ${MCNP_DATA_DIR}/endf70a)
      MESSAGE(FATAL_ERROR "The supplied mcnp data directory is not valid!" )
    ENDIF()
    
    FILE(RELATIVE_PATH MCNP_DATA_DIR_REL_PATH ${CMAKE_CURRENT_BINARY_DIR} ${MCNP_DATA_DIR})
    
    # Configure the cross_sections.xml file
    CONFIGURE_FILE(mcnp_cross_sections.xml.in ${CMAKE_CURRENT_BINARY_DIR}/cross_sections.xml)

    # Add the verification tests
    ADD_EXECUTABLE(tstFacemcH1-2500K tstFacemcH1-2500K.cpp ${FACEMC_CORE_CPP})
    TARGET_LINK_LIBRARIES(tstFacemcH1-2500K monte_carlo_manager)
    ADD_TEST(FacemcH1-2500K_verification_test tstFacemcH1-2500K --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500k/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/h1-2500k/geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500k/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500k/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500k/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500k/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=FacemcH1-2500K --threads=4)
    
  ELSE()
    MESSAGE(WARNING "FACEMC verification test cannot be done without specifying the data directory!")
  ENDIF()

ENDIF()