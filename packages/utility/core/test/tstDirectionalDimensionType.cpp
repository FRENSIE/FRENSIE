//---------------------------------------------------------------------------//
//!
//! \file   tstDirectionalDimensionType.cpp
//! \author Alex Robinson
//! \brief  Directional dimension type enum unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// FRENSIE Includes
#include "Utility_DirectionalDimensionType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a directional dimension type enum can be converted to a string
FRENSIE_UNIT_TEST( DirectionalDimensionType, toString )
{
  std::string dimension_name =
    Utility::toString( Utility::U_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "U" );

  dimension_name =
    Utility::toString( Utility::V_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "V" );

  dimension_name =
    Utility::toString( Utility::W_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "W" );

  dimension_name =
    Utility::toString( Utility::R_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "|R|" );

  dimension_name =
    Utility::toString( Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Theta" );

  dimension_name =
    Utility::toString( Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Mu" );
}

//---------------------------------------------------------------------------//
// Check if the directional dimension type enum can be placed in a stream
FRENSIE_UNIT_TEST( DirectionalDimensionType, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, Utility::U_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "U" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::V_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "V" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::W_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "W" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::R_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "|R|" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "Theta" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "Mu" );
}

//---------------------------------------------------------------------------//
// Check if the directional dimension type enum can be placed in a stream
FRENSIE_UNIT_TEST( DirectionalDimensionType, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::U_DIRECTIONAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "U" );

  oss.str( "" );
  oss.clear();

  oss << Utility::V_DIRECTIONAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "V" );

  oss.str( "" );
  oss.clear();

  oss << Utility::W_DIRECTIONAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "W" );

  oss.str( "" );
  oss.clear();

  oss << Utility::R_DIRECTIONAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "|R|" );

  oss.str( "" );
  oss.clear();

  oss << Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Theta" );

  oss.str( "" );
  oss.clear();

  oss << Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Mu" );
}

//---------------------------------------------------------------------------//
// Check if a directional dimension name can be converted to a directional
// dimension type enum
FRENSIE_UNIT_TEST( DirectionalDimensionType, fromString )
{
  Utility::DirectionalDimensionType dimension =
    Utility::fromString<Utility::DirectionalDimensionType>( "U" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::U_DIRECTIONAL_DIMENSION );

  dimension = Utility::fromString<Utility::DirectionalDimensionType>( "V" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::V_DIRECTIONAL_DIMENSION );

  dimension = Utility::fromString<Utility::DirectionalDimensionType>( "W" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::W_DIRECTIONAL_DIMENSION );

  dimension = Utility::fromString<Utility::DirectionalDimensionType>( "|R|" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::R_DIRECTIONAL_DIMENSION );

  dimension = Utility::fromString<Utility::DirectionalDimensionType>( "Theta" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );

  dimension = Utility::fromString<Utility::DirectionalDimensionType>( "Mu" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );

  FRENSIE_CHECK_THROW( Utility::fromString<Utility::DirectionalDimensionType>( "Dummy Dimension" ),
                       std::runtime_error );       
}

//---------------------------------------------------------------------------//
// Check if a directional dimension enum can be extracted from a stream
FRENSIE_UNIT_TEST( DirectionalDimensionType, fromStream )
{
  std::istringstream iss( "U" );

  Utility::DirectionalDimensionType dimension;
  
  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::U_DIRECTIONAL_DIMENSION );

  iss.str( "V" );
  iss.clear();

  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::V_DIRECTIONAL_DIMENSION );

  iss.str( "W" );
  iss.clear();

  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::W_DIRECTIONAL_DIMENSION );

  iss.str( "|R|" );
  iss.clear();

  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::R_DIRECTIONAL_DIMENSION );

  iss.str( "Theta" );
  iss.clear();

  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );

  iss.str( "Mu" );
  iss.clear();

  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );

  iss.str( "Dummy Dimension" );
  iss.clear();
  
  FRENSIE_CHECK_THROW( Utility::fromStream( iss, dimension ),
                       std::runtime_error );       
}

//---------------------------------------------------------------------------//
// Check if a directional dimension enum can be extracted from a stream
FRENSIE_UNIT_TEST( DirectionalDimensionType, istream_operator )
{
  std::istringstream iss( "U" );

  Utility::DirectionalDimensionType dimension;
  
  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::U_DIRECTIONAL_DIMENSION );

  iss.str( "V" );
  iss.clear();

  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::V_DIRECTIONAL_DIMENSION );

  iss.str( "W" );
  iss.clear();

  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::W_DIRECTIONAL_DIMENSION );

  iss.str( "|R|" );
  iss.clear();

  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::R_DIRECTIONAL_DIMENSION );

  iss.str( "Theta" );
  iss.clear();

  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );

  iss.str( "Mu" );
  iss.clear();

  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );

  iss.str( "Dummy Dimension" );
  iss.clear();
  
  FRENSIE_CHECK_THROW( iss >> dimension,
                       std::runtime_error );       
}

//---------------------------------------------------------------------------//
// end tstDirectionalDimensionType.cpp
//---------------------------------------------------------------------------//
