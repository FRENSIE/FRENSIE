//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimension.cpp
//! \author Alex Robinson
//! \brief  Particle source dimension type helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_SpatialCoordinateSystemTraits.hpp"
#include "Utility_DirectionalCoordinateSystemTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Convert the spatial dimension to the equivalent phase space dimension
PhaseSpaceDimension convertSpatialDimensionToPhaseSpaceDimension(
                        const Utility::SpatialDimensionType spatial_dimension )
{
  typedef Utility::SpatialCoordinateSystemTraits<Utility::CARTESIAN_SPATIAL_COORDINATE_SYSTEM> CartesianCS;
  typedef Utility::SpatialCoordinateSystemTraits<Utility::CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM> CylindricalCS;
  typedef Utility::SpatialCoordinateSystemTraits<Utility::SPHERICAL_SPATIAL_COORDINATE_SYSTEM> SphericalCS;

  // Check if the spatial dimension is the primary spatial dimension
  if( spatial_dimension == CartesianCS::primarySpatialDimension() ||
      spatial_dimension == CylindricalCS::primarySpatialDimension() ||
      spatial_dimension == SphericalCS::primarySpatialDimension() )
    return PRIMARY_SPATIAL_DIMENSION;
  
  // Check if the spatial dimension is the secondary spatial dimension
  else if( spatial_dimension == CartesianCS::secondarySpatialDimension() ||
           spatial_dimension == CylindricalCS::secondarySpatialDimension() ||
           spatial_dimension == SphericalCS::secondarySpatialDimension() )
    return SECONDARY_SPATIAL_DIMENSION;
  
  // Check if the spatial dimension is the tertiary spatial dimension
  else if( spatial_dimension == CartesianCS::tertiarySpatialDimension() ||
           spatial_dimension == CylindricalCS::tertiarySpatialDimension() ||
           spatial_dimension == SphericalCS::tertiarySpatialDimension() )
    return TERTIARY_SPATIAL_DIMENSION;

  // Unknown spatial dimension
  else
  {
    THROW_EXCEPTION( std::logic_error,
                     "An unknown spatial dimension ("
                     << (unsigned)spatial_dimension << ") was encountered!" );
  }
}

// Convert the directional dimension to the equivalent phase space dimension
PhaseSpaceDimension convertDirectionalDimensionToPhaseSpaceDimension(
                const Utility::DirectionalDimensionType directional_dimension )
{
  typedef Utility::DirectionalCoordinateSystemTraits<Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM> CartesianCS;
  typedef Utility::DirectionalCoordinateSystemTraits<Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM> SphericalCS;

  // Check if the directional dimension is the primary directional dimension
  if( directional_dimension == CartesianCS::primaryDirectionalDimension() ||
      directional_dimension == SphericalCS::primaryDirectionalDimension() )
    return PRIMARY_DIRECTIONAL_DIMENSION;
  
  // Check if the directional dimension is the secondary directional dimension
  else if( directional_dimension == CartesianCS::secondaryDirectionalDimension() ||
           directional_dimension == SphericalCS::secondaryDirectionalDimension() )
    return SECONDARY_DIRECTIONAL_DIMENSION;
  
  // Check if the directional dimension is the tertiary directional dimension
  else if( directional_dimension == CartesianCS::tertiaryDirectionalDimension() ||
           directional_dimension == SphericalCS::tertiaryDirectionalDimension() )
    return TERTIARY_DIRECTIONAL_DIMENSION;

  // Unknown directional dimension
  else
  {
    THROW_EXCEPTION( std::logic_error,
                     "An unknown directional dimension ("
                     << (unsigned)directional_dimension <<
                     ") was encountered!" );
  }
}
  
} // end MonteCarlo namespace

namespace Utility{

// Convert a MonteCarlo::PhaseSpaceDimension to a string
std::string ToStringTraits<MonteCarlo::PhaseSpaceDimension>::toString(
                              const MonteCarlo::PhaseSpaceDimension dimension )

{
  switch( dimension )
  {
  case MonteCarlo::PRIMARY_SPATIAL_DIMENSION:
    return "Primary Spatial Dimension";
  case MonteCarlo::SECONDARY_SPATIAL_DIMENSION:
    return "Secondary Spatial Dimension";
  case MonteCarlo::TERTIARY_SPATIAL_DIMENSION:
    return "Tertiary Spatial Dimension";
  case MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION:
    return "Primary Directional Dimension";
  case MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION:
    return "Secondary Directional Dimension";
  case MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION:
    return "Tertiary Directional Dimension";
  case MonteCarlo::ENERGY_DIMENSION:
    return "Energy Dimension";
  case MonteCarlo::TIME_DIMENSION:
    return "Time Dimension";
  case MonteCarlo::WEIGHT_DIMENSION:
    return "Weight Dimension";
  case MonteCarlo::SOURCE_ENERGY_DIMENSION:
    return "Source Energy Dimension";
  case MonteCarlo::SOURCE_TIME_DIMENSION:
    return "Source Time Dimension";
  case MonteCarlo::SOURCE_WEIGHT_DIMENSION:
    return "Source Weight Dimension";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "An unknown PhaseSpaceDimension was "
                     "encountered (" << (unsigned)dimension << ")!" );
  }
}

// Place the MonteCarlo::PhaseSpaceDimension in a stream
void ToStringTraits<MonteCarlo::PhaseSpaceDimension>::toStream(
                              std::ostream& os,
                              const MonteCarlo::PhaseSpaceDimension dimension )
{
  os << ToStringTraits<MonteCarlo::PhaseSpaceDimension>::toString( dimension );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
