ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstGeometryModuleInterface_Root
  tstModuleInterface.cpp)
TARGET_LINK_LIBRARIES(tstGeometryModuleInterface_Root geometry_core geometry_root ${MPI_CXX_LIBRARIES} ${ROOT})
ADD_TEST(GeometryModuleInterface_Root_test tstGeometryModuleInterface_Root --test_root_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/Test_Root_Geometry.C")
