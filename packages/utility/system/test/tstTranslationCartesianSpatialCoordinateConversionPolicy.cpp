//---------------------------------------------------------------------------//
//!
//! \file   tstTranslationCartesianCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Translation Cartesian coordinate conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Utility_TranslationCartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the local Cartesian spatial coordinates can be converted to
// global Cartesian spatial coordinates
FRENSIE_UNIT_TEST( TranslationCartesianSpatialCoordinateConversionPolicy,
                   convertToCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
            new Utility::TranslationCartesianSpatialCoordinateConversionPolicy(
                               std::vector<double>({1.0, 1.0, 1.0}).data() ) );

  std::array<double,3> local_position = {1.0, 1.0, 1.0};

  std::array<double,3> global_position, ref_global_position;
  ref_global_position[0] = 2.0;
  ref_global_position[1] = 2.0;
  ref_global_position[2] = 2.0;

  policy->convertToCartesianSpatialCoordinates( local_position.data(),
                                                global_position.data() );

  FRENSIE_CHECK_EQUAL( global_position, ref_global_position );

  local_position[0] = 2.0;
  local_position[1] = -1.0;
  local_position[2] = 0.1;

  ref_global_position[0] = 3.0;
  ref_global_position[1] = 0.0;
  ref_global_position[2] = 1.1;

  policy->convertToCartesianSpatialCoordinates( local_position[0],
                                                local_position[1],
                                                local_position[2],
                                                global_position[0],
                                                global_position[1],
                                                global_position[2] );

  FRENSIE_CHECK_EQUAL( global_position, ref_global_position );
}

//---------------------------------------------------------------------------//
// Check that the global Cartesian spatial coordinates can be converted to
// local Cartesian spatial coordinates
FRENSIE_UNIT_TEST( TranslationCartesianSpatialCoordinateConversionPolicy,
                   convertFromCartesianSpatialCoordinates )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy> policy(
            new Utility::TranslationCartesianSpatialCoordinateConversionPolicy(
                              std::vector<double>({1.0, 1.0, 1.0 }).data() ) );

  std::array<double,3> global_position = {2.0, 2.0, 2.0};

  std::array<double,3> local_position, ref_local_position;
  ref_local_position[0] = 1.0;
  ref_local_position[1] = 1.0;
  ref_local_position[2] = 1.0;

  policy->convertFromCartesianSpatialCoordinates( global_position.data(),
                                                  local_position.data() );

  FRENSIE_CHECK_EQUAL( local_position, ref_local_position );

  global_position[0] = 3.0;
  global_position[1] = 0.0;
  global_position[2] = 1.1;

  ref_local_position[0] = 2.0;
  ref_local_position[1] = -1.0;
  ref_local_position[2] = 0.1;

  policy->convertFromCartesianSpatialCoordinates( global_position[0],
                                                  global_position[1],
                                                  global_position[2],
                                                  local_position[0],
                                                  local_position[1],
                                                  local_position[2] );

  FRENSIE_CHECK_FLOATING_EQUALITY( local_position, ref_local_position, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstTranslationCartesianSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
