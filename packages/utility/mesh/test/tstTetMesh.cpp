//---------------------------------------------------------------------------//
//!
//! \file   tstTetMesh.cpp
//! \author Alex Robinson
//! \brief  TetMesh class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Utility_TetMesh.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "FRENSIE_config.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

std::string tet_mesh_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the tet mesh can be constructed using a vtk file
FRENSIE_UNIT_TEST( TetMesh, constructor )
{
  std::unique_ptr<Utility::Mesh> mesh;

#ifdef HAVE_FRENSIE_MOAB
  FRENSIE_REQUIRE_NO_THROW( mesh.reset( new Utility::TetMesh( tet_mesh_file_name ) ) );

  FRENSIE_CHECK_EQUAL( mesh->getNumberOfElements(), 6 );
  FRENSIE_CHECK_EQUAL( std::distance( mesh->getStartElementHandleIterator(),
                                      mesh->getEndElementHandleIterator() ),
                       6 );
#else // HAVE_FRENSIE_MOAB
  FRENSIE_REQUIRE_THROW( mesh.reset( new Utility::TetMesh( tet_mesh_file_name ) ),
                         std::logic_error );
#endif // end HAVE_FRENSIE_MOAB
}

#ifdef HAVE_FRENSIE_MOAB

//---------------------------------------------------------------------------//
// Check that the mesh type name can be returned
FRENSIE_UNIT_TEST( TetMesh, getMeshTypeName )
{
  std::unique_ptr<Utility::Mesh> mesh( new Utility::TetMesh( tet_mesh_file_name ) );

  FRENSIE_CHECK_EQUAL( mesh->getMeshTypeName(), "Tet Mesh" );
}

//---------------------------------------------------------------------------//
// Check that the mesh element type name can be returned
FRENSIE_UNIT_TEST( TetMesh, getMeshElementTypeName )
{
  std::unique_ptr<Utility::Mesh> mesh( new Utility::TetMesh( tet_mesh_file_name ) );

  FRENSIE_CHECK_EQUAL( mesh->getMeshElementTypeName(), "Tet" );
}

//---------------------------------------------------------------------------//
// Check that the volume of each tet element can be calculated
FRENSIE_UNIT_TEST( TetMesh, getElementVolumes )
{
  std::unique_ptr<Utility::Mesh> mesh( new Utility::TetMesh( tet_mesh_file_name ) );
  
  Utility::TetMesh::ElementHandleVolumeMap volume_map;

  mesh->getElementVolumes( volume_map );

  FRENSIE_REQUIRE_EQUAL( volume_map.size(), 6 );

  for( auto&& element_volume_pair : volume_map )
  {
    FRENSIE_CHECK_FLOATING_EQUALITY( element_volume_pair.second,
                                     1.0/6,
                                     1e-15 );
    std::cout << element_volume_pair.first << " " << element_volume_pair.second << std::endl;
  }
}

//---------------------------------------------------------------------------//
// Check if a point is in the mesh
FRENSIE_UNIT_TEST( TetMesh, isPointInMesh )
{
  std::unique_ptr<Utility::Mesh> mesh( new Utility::TetMesh( tet_mesh_file_name ) );

  double surface_point_1[3] = { 0.25, 0.0, 0.75 };
  double surface_point_2[3] = { 0.0, 0.25, 0.75 };
  double surface_point_3[3] = { 0.75, 0.0, 0.25 };
  double surface_point_4[3] = { 0.0, 0.75, 0.25 };
  double surface_point_5[3] = { 0.75, 0.25, 0.0 };
  double surface_point_6[3] = { 0.25, 0.75, 0.0 };
  double surface_point_7[3] = { 0.75, 0.25, 1.0 };
  double surface_point_8[3] = { 0.25, 0.75, 1.0 };
  double surface_point_9[3] = { 1.0, 0.25, 0.75 };
  double surface_point_10[3] = { 0.25, 1.0, 0.75 };
  double surface_point_11[3] = { 1.0, 0.75, 0.25 };
  double surface_point_12[3] = { 0.75, 1.0, 0.25 };
  double surface_point_13[3] = { 0.0, 0.0, 0.0 };
  double surface_point_14[3] = { 1.0, 0.0, 0.0 };
  double surface_point_15[3] = { 0.0, 1.0, 0.0 };
  double surface_point_16[3] = { 0.0, 0.0, 1.0 };
  double surface_point_17[3] = { 0.0, 1.0, 1.0 };
  double surface_point_18[3] = { 1.0, 0.0, 1.0 };
  double surface_point_19[3] = { 1.0, 1.0, 0.0 };
  double surface_point_20[3] = { 1.0, 1.0, 1.0 };

  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_1 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_2 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_3 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_4 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_5 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_6 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_7 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_8 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_9 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_10 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_11 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_12 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_13 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_14 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_15 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_16 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_17 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_18 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_19 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_20 ) );

  double outside_point_1[3] = { 0.5, 0.5, -0.5 };
  double outside_point_2[3] = { 0.5, 0.5, 1.5 };
  double outside_point_3[3] = { 0.5, -0.5, 0.5 };
  double outside_point_4[3] = { 0.5, 1.5, 0.5 };
  double outside_point_5[3] = { -0.5, 0.5, 0.5 };
  double outside_point_6[3] = { 1.5, 0.5, 0.5 };

  FRENSIE_CHECK( !mesh->isPointInMesh( outside_point_1 ) );
  FRENSIE_CHECK( !mesh->isPointInMesh( outside_point_2 ) );
  FRENSIE_CHECK( !mesh->isPointInMesh( outside_point_3 ) );
  FRENSIE_CHECK( !mesh->isPointInMesh( outside_point_4 ) );
  FRENSIE_CHECK( !mesh->isPointInMesh( outside_point_5 ) );
  FRENSIE_CHECK( !mesh->isPointInMesh( outside_point_6 ) );

  double inside_point_1[3] = { 0.5, 0.5, 0.5 };
  double inside_point_2[3] = { 0.0, 0.0, 0.5 };
  double inside_point_3[3] = { 0.0, 0.5, 0.0 };
  double inside_point_4[3] = { 0.5, 0.0, 0.0 };
  double inside_point_5[3] = { 0.0, 0.5, 0.5 };
  double inside_point_6[3] = { 0.5, 0.0, 0.5 };
  double inside_point_7[3] = { 0.5, 0.5, 0.0 };

  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_1 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_2 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_3 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_4 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_5 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_6 ) );
  FRENSIE_CHECK( mesh->isPointInMesh( surface_point_7 ) );
}

//---------------------------------------------------------------------------//
// Check that the tet that a point falls in can be determined
FRENSIE_UNIT_TEST( TetMesh, whichElementIsPointIn )
{
  std::unique_ptr<Utility::Mesh> mesh( new Utility::TetMesh( tet_mesh_file_name ) );

  double inside_point_1[3] = { 0.5, 0.25, 0.75 };
  double inside_point_2[3] = { 0.75, 0.25, 0.5 };
  double inside_point_3[3] = { 0.25, 0.5, 0.75 };
  double inside_point_4[3] = { 0.25, 0.75, 0.5 };
  double inside_point_5[3] = { 0.75, 0.75, 0.25 };
  double inside_point_6[3] = { 0.5, 0.75, 0.25 };

  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( inside_point_1 ),
                       5764607523034234881 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( inside_point_2 ),
                       5764607523034234882 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( inside_point_3 ),
                       5764607523034234883 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( inside_point_4 ),
                       5764607523034234884 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( inside_point_5 ),
                       5764607523034234885 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( inside_point_6 ),
                       5764607523034234886 );

  double surface_point_1[3] = { 0.25, 0.0, 0.75 };
  double surface_point_2[3] = { 0.0, 0.25, 0.75 };
  double surface_point_3[3] = { 0.75, 0.0, 0.25 };
  double surface_point_4[3] = { 0.0, 0.75, 0.25 };
  double surface_point_5[3] = { 0.75, 0.25, 0.0 };
  double surface_point_6[3] = { 0.25, 0.75, 0.0 };
  double surface_point_7[3] = { 0.75, 0.25, 1.0 };
  double surface_point_8[3] = { 0.25, 0.75, 1.0 };
  double surface_point_9[3] = { 1.0, 0.25, 0.75 };
  double surface_point_10[3] = { 0.25, 1.0, 0.75 };
  double surface_point_11[3] = { 1.0, 0.75, 0.25 };
  double surface_point_12[3] = { 0.75, 1.0, 0.25 };
  
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_1 ),
                       5764607523034234881 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_2 ),
                       5764607523034234883 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_3 ),
                       5764607523034234882 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_4 ),
                       5764607523034234884 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_5 ),
                       5764607523034234885 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_6 ),
                       5764607523034234886 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_7 ),
                       5764607523034234881 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_8 ),
                       5764607523034234883 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_9 ),
                       5764607523034234882 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_10 ),
                       5764607523034234884 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_11 ),
                       5764607523034234885 );
  FRENSIE_CHECK_EQUAL( mesh->whichElementIsPointIn( surface_point_12 ),
                       5764607523034234886 );
}

//---------------------------------------------------------------------------//
// Check that the tracks through tets can be calculated
FRENSIE_UNIT_TEST( TetMesh, computeTrackLengths )
{
  std::unique_ptr<Utility::Mesh> mesh( new Utility::TetMesh( tet_mesh_file_name ) );

  double start_point[3], end_point[3];

  // No intersection
  start_point[0] = 2.0;
  start_point[1] = -1.0;
  start_point[2] = 0.0;

  end_point[0] = 4.0;
  end_point[1] = -1.0;
  end_point[2] = 0.0;

  Utility::TetMesh::ElementHandleTrackLengthArray contribution;

  mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_CHECK( contribution.empty() );

  // Start and end point on mesh element surfaces
  start_point[0] = 0.25;
  start_point[1] = 0.0;
  start_point[2] = 0.75;

  end_point[0] = 0.75;
  end_point[1] = 0.25;
  end_point[2] = 1.0;

  mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 5764607523034234881 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.25, 0.0, 0.75} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.6123724356957945,
                                   1e-12 );

  // Start point outside of mesh, end point on mesh element surface
  // start intersection { 0.0, 0.25, 0.75 };
  start_point[0] = -0.4082482904638631;
  start_point[1] = -0.5664965809277261;
  start_point[2] = 0.3417517095361369;

  end_point[0] = 0.25;
  end_point[1] = 0.75;
  end_point[2] = 1.0;

  mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 5764607523034234883 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.0, 0.25, 0.75} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.6123724356957945,
                                   1e-12 );

  // Start point on mesh element surface, end point outside of surface
  // end intersection { 1.0, 0.25, 0.75 }
  start_point[0] = 0.75;
  start_point[1] = 0.0;
  start_point[2] = 0.25;

  end_point[0] = 1.4082482904638631;
  end_point[1] = 0.6582482904638631;
  end_point[2] = 1.5664965809277263;

  mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 5764607523034234882 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.75, 0.0, 0.25} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.6123724356957945,
                                   1e-12 );

  // Start point and end point outside of surface
  // start intersection { 0.0, 0.75, 0.25 }
  // end intersection { 0.25, 1.0, 0.75 }
  start_point[0] = -0.4082482904638631;
  start_point[1] = 0.3417517095361369;
  start_point[2] = -0.5664965809277261;

  end_point[0] = 0.6582482904638631;
  end_point[1] = 1.4082482904638631;
  end_point[2] = 1.5664965809277263;

  mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 5764607523034234884 );
  FRENSIE_CHECK_SMALL( Utility::get<1>(contribution[0])[0], 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0])[1],
                                   0.75,
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0])[2],
                                   0.25,
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.6123724356957945,
                                   1e-12 );

  // Start point outside of mesh, end point inside of mesh element
  // start intersection { 0.75, 0.25, 0.0 }
  start_point[0] = 0.3417517095361369;
  start_point[1] = -0.5664965809277261;
  start_point[2] = -0.4082482904638631;

  end_point[0] = 0.875;
  end_point[1] = 0.5;
  end_point[2] = 0.125;

  mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 5764607523034234885 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0])[0],
                                   0.75,
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0])[1],
                                   0.25,
                                   1e-12 );
  FRENSIE_CHECK_SMALL( Utility::get<1>(contribution[0])[2], 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.30618621784789724,
                                   1e-12 );

  // Start point inside of mesh, end point outside of mesh
  // end intersection { 1.0, 0.75, 0.25 }
  start_point[0] = 0.875;
  start_point[1] = 0.5;
  start_point[2] = 0.125;

  end_point[0] = 1.4082482904638631;
  end_point[1] = 1.5664965809277263;
  end_point[2] = 0.6582482904638631;

  mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 5764607523034234885 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.875, 0.5, 0.125} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.30618621784789724,
                                   1e-12 );

  // Start point on mesh element surface, end point in mesh element
  // start intersection { 0.25, 0.75, 0.0 }
  start_point[0] = 0.25;
  start_point[1] = 0.75;
  start_point[2] = 0.0;

  end_point[0] = 0.41666666666666663;
  end_point[1] = 0.8333333333333334;
  end_point[2] = 0.08333333333333333;

  mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 5764607523034234886 );
  FRENSIE_CHECK_EQUAL( Utility::get<1>(contribution[0]),
                       (std::array<double,3>( {0.25, 0.75, 0.0} )) );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.20412414523193148,
                                   1e-12 );

  // Start point in mesh element, end point in mesh element
  start_point[0] = 0.41666666666666663;
  start_point[1] = 0.8333333333333334;
  start_point[2] = 0.08333333333333333;

  end_point[0] = 0.5833333333333333;
  end_point[1] = 0.9166666666666666;
  end_point[2] = 0.16666666666666666;

  mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 5764607523034234886 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0]),
                                   (std::array<double,3>( {0.41666666666666663, 0.8333333333333334, 0.08333333333333333} )),
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.20412414523193148,
                                   1e-12 );

  // Start point in mesh element, end point on mesh element surface
  // end intersection { 0.75, 1.0, 0.25 }
  start_point[0] = 0.5833333333333333;
  start_point[1] = 0.9166666666666666;
  start_point[2] = 0.16666666666666666;

  end_point[0] = 0.75;
  end_point[1] = 1.0;
  end_point[2] = 0.25;

  mesh->computeTrackLengths( start_point, end_point, contribution );

  FRENSIE_REQUIRE_EQUAL( contribution.size(), 1 );
  FRENSIE_CHECK_EQUAL( Utility::get<0>(contribution[0]), 5764607523034234886 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<1>(contribution[0]),
                                   (std::array<double,3>( {0.5833333333333333, 0.9166666666666666, 0.16666666666666666 } )),
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<2>(contribution[0]),
                                   0.20412414523193148,
                                   1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the tet mesh data can be exported
FRENSIE_UNIT_TEST( TetMesh, exportData )
{
  std::unique_ptr<Utility::Mesh> mesh( new Utility::TetMesh( tet_mesh_file_name ) );

  // Export an empty mesh
  FRENSIE_CHECK_NO_THROW( mesh->exportData( "empty_test_tet_mesh.vtk" ) );

  // Export the mesh with tag data
  Utility::TetMesh::TagNameSet tag_name_set( {"mean", "rel_err"} );

  Utility::TetMesh::MeshElementHandleDataMap element_data_map;

  Utility::TetMesh::ElementHandleIterator element_it =
    mesh->getStartElementHandleIterator();

  int i = 0;
  
  while( element_it != mesh->getEndElementHandleIterator() )
  {
    element_data_map[*element_it]["mean"] = std::vector<std::pair<std::string,double> >( {std::make_pair("b0", 0.1*i), std::make_pair("b1", 0.2*i), std::make_pair("b2", 0.3*i)} );
    element_data_map[*element_it]["rel_err"] = std::vector<std::pair<std::string,double> >( {std::make_pair("b0", 0.01), std::make_pair("b1", 0.001), std::make_pair("b2", 0.01)} );

    ++element_it;
    ++i;
  }

  FRENSIE_CHECK_NO_THROW( mesh->exportData( "test_tet_mesh.vtk",
                                            tag_name_set,
                                            element_data_map ) );
}

//---------------------------------------------------------------------------//
// Check that a tet mesh can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( TetMesh, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_structured_hex_mesh" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::unique_ptr<Utility::TetMesh> concrete_tet_mesh(
                                  new Utility::TetMesh( tet_mesh_file_name ) );
    
    std::unique_ptr<Utility::Mesh> tet_mesh(
                                  new Utility::TetMesh( tet_mesh_file_name ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( concrete_tet_mesh ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( tet_mesh ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<Utility::TetMesh> concrete_tet_mesh;
  std::unique_ptr<Utility::Mesh> tet_mesh;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( concrete_tet_mesh ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( tet_mesh ) );

  iarchive.reset();

  {
    FRENSIE_CHECK_EQUAL( concrete_tet_mesh->getNumberOfElements(), 6 );
    FRENSIE_CHECK_EQUAL( std::distance( concrete_tet_mesh->getStartElementHandleIterator(),
                                        concrete_tet_mesh->getEndElementHandleIterator() ),
                         6 );

    double inside_point_1[3] = { 0.5, 0.25, 0.75 };
    double inside_point_2[3] = { 0.75, 0.25, 0.5 };
    double inside_point_3[3] = { 0.25, 0.5, 0.75 };
    double inside_point_4[3] = { 0.25, 0.75, 0.5 };
    double inside_point_5[3] = { 0.75, 0.75, 0.25 };
    double inside_point_6[3] = { 0.5, 0.75, 0.25 };
    
    FRENSIE_CHECK_EQUAL( concrete_tet_mesh->whichElementIsPointIn( inside_point_1 ),
                         5764607523034234881 );
    FRENSIE_CHECK_EQUAL( concrete_tet_mesh->whichElementIsPointIn( inside_point_2 ),
                         5764607523034234882 );
    FRENSIE_CHECK_EQUAL( concrete_tet_mesh->whichElementIsPointIn( inside_point_3 ),
                         5764607523034234883 );
    FRENSIE_CHECK_EQUAL( concrete_tet_mesh->whichElementIsPointIn( inside_point_4 ),
                         5764607523034234884 );
    FRENSIE_CHECK_EQUAL( concrete_tet_mesh->whichElementIsPointIn( inside_point_5 ),
                         5764607523034234885 );
    FRENSIE_CHECK_EQUAL( concrete_tet_mesh->whichElementIsPointIn( inside_point_6 ),
                         5764607523034234886 );
  }

  {
    FRENSIE_CHECK_EQUAL( tet_mesh->getNumberOfElements(), 6 );
    FRENSIE_CHECK_EQUAL( std::distance( tet_mesh->getStartElementHandleIterator(),
                                        tet_mesh->getEndElementHandleIterator() ),
                         6 );

    double inside_point_1[3] = { 0.5, 0.25, 0.75 };
    double inside_point_2[3] = { 0.75, 0.25, 0.5 };
    double inside_point_3[3] = { 0.25, 0.5, 0.75 };
    double inside_point_4[3] = { 0.25, 0.75, 0.5 };
    double inside_point_5[3] = { 0.75, 0.75, 0.25 };
    double inside_point_6[3] = { 0.5, 0.75, 0.25 };
    
    FRENSIE_CHECK_EQUAL( tet_mesh->whichElementIsPointIn( inside_point_1 ),
                         5764607523034234881 );
    FRENSIE_CHECK_EQUAL( tet_mesh->whichElementIsPointIn( inside_point_2 ),
                         5764607523034234882 );
    FRENSIE_CHECK_EQUAL( tet_mesh->whichElementIsPointIn( inside_point_3 ),
                         5764607523034234883 );
    FRENSIE_CHECK_EQUAL( tet_mesh->whichElementIsPointIn( inside_point_4 ),
                         5764607523034234884 );
    FRENSIE_CHECK_EQUAL( tet_mesh->whichElementIsPointIn( inside_point_5 ),
                         5764607523034234885 );
    FRENSIE_CHECK_EQUAL( tet_mesh->whichElementIsPointIn( inside_point_6 ),
                         5764607523034234886 );
  }
}

#endif // end HAVE_FRENSIE_MOAB

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_tet_mesh_file",
                                        tet_mesh_file_name, "",
                                        "Test tet mesh file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstTetMesh.cpp
//---------------------------------------------------------------------------//
