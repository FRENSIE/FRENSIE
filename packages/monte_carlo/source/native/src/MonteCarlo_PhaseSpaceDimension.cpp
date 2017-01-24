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

// Test if the dimension name is valid
bool isValidPhaseSpaceDimensionName( const std::string& dimension_name )
{
  if( dimension_name == "Primary Spatial Dimension" )
    return true;
  else if( dimension_name == "Secondary Spatial Dimension" )
    return true;
  else if( dimension_name == "Tertiary Spatial Dimension" )
    return true;
  else if( dimension_name == "Primary Directional Dimension" )
    return true;
  else if( dimension_name == "Secondary Directional Dimension" )
    return true;
  else if( dimension_name == "Tertiary Directional Dimension" )
    return true;
  else if( dimension_name == "Energy Dimension" )
    return true;
  else if( dimension_name == "Time Dimension" )
    return true;
  else if( dimension_name == "Weight Dimension" )
    return true;
  else
    return false;
}

// Convert the dimension name to a dimension type enum
PhaseSpaceDimension convertPhaseSpaceDimensionNameToEnum(
                                            const std::string& dimension_name )
{
  if( dimension_name == "Primary Spatial Dimension" )
    return PRIMARY_SPATIAL_DIMENSION;
  else if( dimension_name == "Secondary Spatial Dimension" )
    return SECONDARY_SPATIAL_DIMENSION;
  else if( dimension_name == "Tertiary Spatial Dimension" )
    return TERTIARY_SPATIAL_DIMENSION;
  else if( dimension_name == "Primary Directional Dimension" )
    return PRIMARY_DIRECTIONAL_DIMENSION;
  else if( dimension_name == "Secondary Directional Dimension" )
    return SECONDARY_DIRECTIONAL_DIMENSION;
  else if( dimension_name == "Tertiary Directional Dimension" )
    return TERTIARY_DIRECTIONAL_DIMENSION;
  else if( dimension_name == "Energy Dimension" )
    return ENERGY_DIMENSION;
  else if( dimension_name == "Time Dimension" )
    return TIME_DIMENSION;
  else if( dimension_name == "Weight Dimension" )
    return WEIGHT_DIMENSION;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: Dimension name " << dimension_name << " is not "
                     "supported!" );
  }
}

// Convert the dimension type enum to a string
std::string convertPhaseSpaceDimensionEnumToString(
                                  const PhaseSpaceDimension dimension )
{
  switch( dimension )
  {
  case PRIMARY_SPATIAL_DIMENSION:
    return "Primary Spatial Dimension";
  case SECONDARY_SPATIAL_DIMENSION:
    return "Secondary Spatial Dimension";
  case TERTIARY_SPATIAL_DIMENSION:
    return "Tertiary Spatial Dimension";
  case PRIMARY_DIRECTIONAL_DIMENSION:
    return "Primary Directional Dimension";
  case SECONDARY_DIRECTIONAL_DIMENSION:
    return "Secondary Directional Dimension";
  case TERTIARY_DIRECTIONAL_DIMENSION:
    return "Tertiary Directional Dimension";
  case ENERGY_DIMENSION:
    return "Energy Dimension";
  case TIME_DIMENSION:
    return "Time Dimension";
  case WEIGHT_DIMENSION:
    return "Weight Dimension";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: An unknown PhaseSpaceDimension was "
                     "encountered (" << (unsigned)dimension << ")!" );
  }
}

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
                     "Error: An unknown spatial dimension ("
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
                     "Error: An unknown directional dimension ("
                     << (unsigned)directional_dimension <<
                     ") was encountered!" );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
