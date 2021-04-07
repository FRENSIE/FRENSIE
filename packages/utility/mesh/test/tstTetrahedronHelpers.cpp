//---------------------------------------------------------------------------//
//!
//! \file   tstTetrahedronHelpers.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tetrahedron helper functions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <vector>

// FRENSIE Includes
#include "Utility_TetrahedronHelpers.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the volume of a tet can be calculated
FRENSIE_UNIT_TEST( TetrahedronHelpers, calculateTetrahedronVolume )
{
  double vertex_a[3] = {0.0, 0.0, 0.0};
  double vertex_b[3] = {1.0, 0.0, 0.0};
  double vertex_c[3] = {0.0, 1.0, 0.0};
  double vertex_d[3] = {0.0, 0.0, 1.0};

  double volume = Utility::calculateTetrahedronVolume( vertex_a,
						       vertex_b,
						       vertex_c,
						       vertex_d );

  FRENSIE_CHECK_EQUAL( volume, 1.0/6.0 );
}

//---------------------------------------------------------------------------//
// Check that the barycentric transform matrix can be calculated with arrays
FRENSIE_UNIT_TEST( TetrahedronHelpers, calculateBarycentricTransformMatrix )
{
  double vertex_a[3] = { 0.0, 0.0, 0.0 };
  double vertex_b[3] = { 1.0, 0.0, 0.0 };
  double vertex_c[3] = { 0.0, 1.0, 0.0 };
  double vertex_d[3] = { 0.0, 0.0, 1.0 };
  double transform_arrays[9];
  std::vector<double> std_transform_array( 9 );
  std::array<double,9> std_transform_tuple;

  // Usage A Test (safe)
  Utility::calculateBarycentricTransformMatrix( vertex_a,
						vertex_b,
						vertex_c,
						vertex_d,
						transform_arrays );

  FRENSIE_CHECK_FLOATING_EQUALITY( transform_arrays[0], -1.0, 1e-12 );

  // Usage B Test (safe)
  Utility::calculateBarycentricTransformMatrix(
					 vertex_a,
					 vertex_b,
					 vertex_c,
					 vertex_d,
					 std_transform_array.data() );

  FRENSIE_CHECK_FLOATING_EQUALITY( std_transform_array[0], -1.0, 1e-12 );

  // Usage C Test (safest)
  Utility::calculateBarycentricTransformMatrix(
					 vertex_a,
					 vertex_b,
					 vertex_c,
					 vertex_d,
					 std_transform_tuple.data() );

  std::array<double,9> expected_transform_tuple =
    {-1.0, -1.0, -1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0};

  FRENSIE_CHECK_FLOATING_EQUALITY( std_transform_tuple,
                                   expected_transform_tuple,
                                   1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the point is in the tet
FRENSIE_UNIT_TEST( TetrahedronHelpers, isPointInTet )
{
  const double point_in[3] = { 0.25, 0.25, 0.25 };
  const double point_out[3] = { 0.75, 0.75, 0.75 };
  const double reference_vertex[3] = { 0.0, 0.0, 1.0 };

  std::array<double,9> transform_tuple =
    {-1.0, -1.0, -1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0};

  bool is_point_in_in_tet = Utility::isPointInTet( point_in,
                                                   reference_vertex,
                                                   transform_tuple.data() );
  bool is_point_out_in_tet = Utility::isPointInTet( point_out,
                                                    reference_vertex,
                                                    transform_tuple.data() );

  FRENSIE_CHECK( is_point_in_in_tet );
  FRENSIE_CHECK( !is_point_out_in_tet );
}

//---------------------------------------------------------------------------//
// end tstTetrahedronHelpers.cpp
//---------------------------------------------------------------------------//
