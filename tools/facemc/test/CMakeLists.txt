# Compute the relative path to the mcnp data directory
ADD_SUBDIRECTORY(h1-2500K)
ADD_SUBDIRECTORY(water-293.6K)
ADD_SUBDIRECTORY(u235-293.6K)

IF(DEFINED MCNP_DATA_DIR)

  # Check if the mcnp data dir is valid
  IF(NOT EXISTS ${MCNP_DATA_DIR})
    MESSAGE(FATAL_ERROR "The supplied mcnp data directory is not valid!" )
  ELSEIF(NOT EXISTS ${MCNP_DATA_DIR}/xsdir)
    MESSAGE(FATAL_ERROR "The supplied mcnp data directory is not valid!" )
  ENDIF()
    
  FILE(RELATIVE_PATH MCNP_DATA_DIR_REL_PATH ${CMAKE_CURRENT_BINARY_DIR} ${MCNP_DATA_DIR})
    
  # Configure the cross_sections.xml file
  CONFIGURE_FILE(mcnp_cross_sections.xml.in ${CMAKE_CURRENT_BINARY_DIR}/cross_sections.xml)

  # Add the Dag-Facemc H1-2500K Neutron tests
  IF(${FRENSIE_ENABLE_DAGMC})
    ADD_EXECUTABLE(tstDagFacemcH1-2500K tstDagFacemcH1-2500K.cpp tstFacemcH1-2500K.cpp)
    TARGET_LINK_LIBRARIES(tstDagFacemcH1-2500K facemc_core)
  
    ADD_TEST(DagFacemc_H1-2500K_test tstDagFacemcH1-2500K --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/h1-2500K/dag-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=DagFacemcH1-2500K --threads=4)

    IF(${FRENSIE_ENABLE_MPI})
      ADD_EXECUTABLE(tstDagFacemcH1-2500K-mpi tstDagFacemcH1-2500K-mpi.cpp tstFacemcH1-2500K.cpp)
      TARGET_LINK_LIBRARIES(tstDagFacemcH1-2500K-mpi facemc_core)
      ADD_TEST(DagFacemc_H1-2500K-mpi_test 
        ${MPIEXEC} -n 4 tstDagFacemcH1-2500K-mpi --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/h1-2500K/dag-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=DagFacemcH1-2500K-mpi --threads=1)
    ENDIF()
  ENDIF()

  # Add the Root-Facemc H1-2500K Neutron tests
  IF(${FRENSIE_ENABLE_ROOT})
    ADD_EXECUTABLE(tstRootFacemcH1-2500K tstRootFacemcH1-2500K.cpp tstFacemcH1-2500K.cpp)
    TARGET_LINK_LIBRARIES(tstRootFacemcH1-2500K facemc_core)
  
    ADD_TEST(RootFacemc_H1-2500K_test tstRootFacemcH1-2500K --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/h1-2500K/root-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=RootFacemcH1-2500K --threads=4)

    IF(${FRENSIE_ENABLE_MPI})
      ADD_EXECUTABLE(tstRootFacemcH1-2500K-mpi tstRootFacemcH1-2500K-mpi.cpp tstFacemcH1-2500K.cpp)
      TARGET_LINK_LIBRARIES(tstRootFacemcH1-2500K-mpi facemc_core)
      ADD_TEST(RootFacemc_H1-2500K-mpi_test 
        ${MPIEXEC} -n 4 tstRootFacemcH1-2500K-mpi --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/h1-2500K/root-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/h1-2500K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=RootFacemcH1-2500K-mpi --threads=1)
    ENDIF()
  ENDIF()

  # Add the Dag-Facemc Water-293.6K Neutron tests
  IF(${FRENSIE_ENABLE_DAGMC})
    ADD_EXECUTABLE(tstDagFacemcWater-293.6K tstDagFacemcWater-293.6K.cpp tstFacemcWater-293.6K.cpp)
    TARGET_LINK_LIBRARIES(tstDagFacemcWater-293.6K facemc_core)
    ADD_TEST(DagFacemc_Water-293.6K_test tstDagFacemcWater-293.6K --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/water-293.6K/dag-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=DagFacemcWater-293.6K --threads=4)

    IF(${FRENSIE_ENABLE_MPI})
      ADD_EXECUTABLE(tstDagFacemcWater-293.6K-mpi tstDagFacemcWater-293.6K-mpi.cpp tstFacemcWater-293.6K.cpp)
      TARGET_LINK_LIBRARIES(tstDagFacemcWater-293.6K-mpi facemc_core)
      ADD_TEST(DagFacemc_Water-293.6K-mpi_test 
        ${MPIEXEC} -n 4 tstDagFacemcWater-293.6K-mpi --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/water-293.6K/dag-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=DagFacemcWater-293.6K-mpi --threads=1)
    ENDIF()
  ENDIF()

  # Add the Root-Facemc Water-293.6K Neutron tests
  IF(${FRENSIE_ENABLE_ROOT})
    ADD_EXECUTABLE(tstRootFacemcWater-293.6K tstRootFacemcWater-293.6K.cpp tstFacemcWater-293.6K.cpp)
    TARGET_LINK_LIBRARIES(tstRootFacemcWater-293.6K facemc_core)
    ADD_TEST(RootFacemc_Water-293.6K_test tstRootFacemcWater-293.6K --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/water-293.6K/root-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=RootFacemcWater-293.6K --threads=4)
    
    IF(${FRENSIE_ENABLE_MPI})
      ADD_EXECUTABLE(tstRootFacemcWater-293.6K-mpi tstRootFacemcWater-293.6K-mpi.cpp tstFacemcWater-293.6K.cpp)
      TARGET_LINK_LIBRARIES(tstRootFacemcWater-293.6K-mpi facemc_core)
      ADD_TEST(RootFacemc_Water-293.6K-mpi_test 
        ${MPIEXEC} -n 4 tstRootFacemcWater-293.6K-mpi --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/water-293.6K/root-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/water-293.6K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=RootFacemcWater-293.6K-mpi --threads=1)
    ENDIF()
  ENDIF()
    
  # Add the Dag-Facemc U235-293.6K Neutron tests
  IF(${FRENSIE_ENABLE_DAGMC})
    ADD_EXECUTABLE(tstDagFacemcU235-293.6K tstDagFacemcU235-293.6K.cpp tstFacemcU235-293.6K.cpp)
    TARGET_LINK_LIBRARIES(tstDagFacemcU235-293.6K facemc_core)
    ADD_TEST(DagFacemc_U235-293.6K_test tstDagFacemcU235-293.6K --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/u235-293.6K/dag-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=DagFacemcU235-293.6K --threads=4)

    IF(${FRENSIE_ENABLE_MPI})
      ADD_EXECUTABLE(tstDagFacemcU235-293.6K-mpi tstDagFacemcU235-293.6K-mpi.cpp tstFacemcU235-293.6K.cpp)
    TARGET_LINK_LIBRARIES(tstDagFacemcU235-293.6K-mpi facemc_core)
    ADD_TEST(DagFacemc_U235-293.6K-mpi_test 
      ${MPIEXEC} -n 4 tstDagFacemcU235-293.6K-mpi --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/u235-293.6K/dag-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=DagFacemcU235-293.6K-mpi --threads=1)
    ENDIF()
  ENDIF()

  # Add the Root-Facemc U235-293.6K Neutron tests
  IF(${FRENSIE_ENABLE_ROOT})
    ADD_EXECUTABLE(tstRootFacemcU235-293.6K tstRootFacemcU235-293.6K.cpp tstFacemcU235-293.6K.cpp)
    TARGET_LINK_LIBRARIES(tstRootFacemcU235-293.6K facemc_core)
    ADD_TEST(RootFacemc_U235-293.6K_test tstRootFacemcU235-293.6K --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/u235-293.6K/root-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=RootFacemcU235-293.6K --threads=4)

    IF(${FRENSIE_ENABLE_MPI})
      ADD_EXECUTABLE(tstRootFacemcU235-293.6K-mpi tstRootFacemcU235-293.6K-mpi.cpp tstFacemcU235-293.6K.cpp)
    TARGET_LINK_LIBRARIES(tstRootFacemcU235-293.6K-mpi facemc_core)
    ADD_TEST(RootFacemc_U235-293.6K-mpi_test 
      ${MPIEXEC} -n 4 tstRootFacemcU235-293.6K-mpi --sim_info="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/sim_info.xml" --geom_def="${CMAKE_CURRENT_BINARY_DIR}/u235-293.6K/root-geom.xml" --src_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/source.xml" --resp_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/rsp_fn.xml" --est_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/est.xml" --mat_def="${CMAKE_CURRENT_SOURCE_DIR}/u235-293.6K/mat.xml" --cross_sec_dir="${CMAKE_CURRENT_BINARY_DIR}" --simulation_name=RootFacemcU235-293.6K-mpi --threads=1)
    ENDIF()
  ENDIF()
    
ELSE()
  MESSAGE(WARNING "FACEMC verification test cannot be done without specifying the data directory!")
ENDIF()