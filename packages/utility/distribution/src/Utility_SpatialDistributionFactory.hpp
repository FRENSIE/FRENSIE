//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialDistributionFactory.hpp
//! \author Alex Robinson
//! \brief  Spatial distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPATIAL_DISTRIBUTION_FACTORY_HPP
#define UTILITY_SPATIAL_DISTRIBUTION_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <memory>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Utility_SpatialDistribution.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_Axis.hpp"

namespace Utility{

//! The spatial distribution factory class
class SpatialDistributionFactory
{

public:

  //! Create the spatial distribution represented by the parameter list
  static std::shared_ptr<SpatialDistribution> 
  createDistribution( const Teuchos::ParameterList& distribution_rep );

private:

  // Validate a distribution representation
  static void validateDistributionRep( 
			      const Teuchos::ParameterList& distribution_rep );

  // Validate the axis name
  static void validateAxisName( const std::string& axis_name );

  // Create a cartesian distribution
  static std::shared_ptr<Utility::SpatialDistribution> 
  createCartesianDistribution(const Teuchos::ParameterList& distribution_rep );

  // Create a cylindrical distribution
  static std::shared_ptr<Utility::SpatialDistribution> 
  createCylindricalDistribution(
			      const Teuchos::ParameterList& distribution_rep );

  // Create a spherical distribution
  static std::shared_ptr<Utility::SpatialDistribution> 
  createSphericalDistribution(const Teuchos::ParameterList& distribution_rep );

  // Create a point distribution
  static std::shared_ptr<Utility::SpatialDistribution>
  createPointDistribution( const Teuchos::ParameterList& distribution_rep );

  // Constructor
  SpatialDistributionFactory();
};

//! The invalid spatial distribution representation error
class InvalidSpatialDistributionRepresentation : public std::logic_error
{

public:

  InvalidSpatialDistributionRepresentation( const std::string& what_arg )
    : std::logic_error( what_arg )
  { /* ... */ }
};

} // end Utility namespace

#endif // end UTILITY_SPATIAL_DISTRIBUTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Utility_SpatialDistributionFactory.hpp
//---------------------------------------------------------------------------//
