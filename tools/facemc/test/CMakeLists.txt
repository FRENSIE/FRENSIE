# Compute the relative path to the mcnp data directory
ADD_SUBDIRECTORY(h1-2500K)
ADD_SUBDIRECTORY(water-293.6K)
ADD_SUBDIRECTORY(u235-293.6K)

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
    ADD_TEST(Facemc_H1-2500K_verification_test tstFacemcH1-2500K --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/h1-2500K/geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=FacemcH1-2500K --threads=4)

    ADD_EXECUTABLE(tstFacemcWater-293.6K tstFacemcWater-293.6K.cpp ${FACEMC_CORE_CPP})
    TARGET_LINK_LIBRARIES(tstFacemcWater-293.6K monte_carlo_manager)
    ADD_TEST(Facemc_Water-293.6K_verification_test tstFacemcWater-293.6K --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/water-293.6K/geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=FacemcWater-293.6K --threads=4)
    
    ADD_EXECUTABLE(tstFacemcU235-293.6K tstFacemcU235-293.6K.cpp ${FACEMC_CORE_CPP})
    TARGET_LINK_LIBRARIES(tstFacemcU235-293.6K monte_carlo_manager)
    ADD_TEST(Facemc_U235-293.6K_verification_test tstFacemcU235-293.6K --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/u235-293.6K/geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=FacemcU235-293.6K --threads=4)
    
  ELSE()
    MESSAGE(WARNING "FACEMC verification test cannot be done without specifying the data directory!")
  ENDIF()

ENDIF()