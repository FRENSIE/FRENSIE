//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Directional distribution factory class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_DirectionalDistributionFactory.hpp"
#include "Utility_MonoDirectionalDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Initialize static member data
const std::shared_ptr<Utility::OneDDistribution> 
DirectionalDistributionFactory::s_default_mu_dist( 
			     new Utility::UniformDistribution( -1., 1., 2. ) );

const std::shared_ptr<Utility::OneDDistribution>
DirectionalDistributionFactory::s_default_theta_dist(
   new Utility::UniformDistribution( 0., 2*PhysicalConstants::pi, 1. ) );

const std::shared_ptr<Utility::SphericalDirectionalDistribution>
DirectionalDistributionFactory::s_isotropic_directional_dist(
	      new Utility::SphericalDirectionalDistribution( 
		      DirectionalDistributionFactory::s_default_theta_dist,
		      DirectionalDistributionFactory::s_default_mu_dist ) );

// Create the directional distribution represented by the parameter list
std::shared_ptr<DirectionalDistribution>
DirectionalDistributionFactory::createDistribution( 
			       const Teuchos::ParameterList& distribution_rep )
{
  // Validate the distribution representation
  DirectionalDistributionFactory::validateDistributionRep( distribution_rep );

  // Create the directional distribution
  if( distribution_rep.isParameter( "Direction" ) )
  {
    Teuchos::Array<double> direction = 
      distribution_rep.get<Teuchos::Array<double> >( "Direction" );

    TEST_FOR_EXCEPTION( direction.size() != 3,
			InvalidDirectionalDistributionRepresentation,
			"Error: the direction is invalid - size ("
			<< direction.size() << ") != 3" );

    return std::shared_ptr<DirectionalDistribution>(
			     new MonoDirectionalDistribution( direction[0],
							      direction[1],
							      direction[2] ) );
  }
  else
  {
    Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
      distribution_rep.getEntryRCP( "Mu Distribution" );
    
    std::shared_ptr<OneDDistribution> mu_distribution = 
      OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );

    // Make sure the mu distribution is valid
    TEST_FOR_EXCEPTION( mu_distribution->getLowerBoundOfIndepVar() < -1.0,
			InvalidDirectionalDistributionRepresentation,
			"Error: the mu distribution must only be defined in "
			"the interval [-1,1]!" );

    TEST_FOR_EXCEPTION( mu_distribution->getUpperBoundOfIndepVar() > 1.0,
			InvalidDirectionalDistributionRepresentation,
			"Error: the mu distribution must only be defined in "
			"the interval [-1,1]!" );

    // Optional argument
    std::shared_ptr<OneDDistribution> theta_distribution;

    if( distribution_rep.isParameter( "Theta Distribution" ) )
    {
      entry = distribution_rep.getEntryRCP( "Theta Distribution" );
      
      theta_distribution = 
	OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
    }
    else
      theta_distribution = s_default_theta_dist;

    // Make sure the theta distribution is valid
    TEST_FOR_EXCEPTION( theta_distribution->getLowerBoundOfIndepVar() < 0.0,
			InvalidDirectionalDistributionRepresentation,
			"Error: the theta distribution must only be defined "
			"in the interval [0,2pi]" );

    TEST_FOR_EXCEPTION( theta_distribution->getUpperBoundOfIndepVar() > 
			2*Utility::PhysicalConstants::pi,
			InvalidDirectionalDistributionRepresentation,
			"Error: the theta distribution must only be defined "
			"in the interval [0,2pi]" );
    
    // Optional argument
    std::string axis_name;
    
    if( distribution_rep.isParameter( "Axis" ) )
      axis_name = distribution_rep.get<std::string>( "Axis" );
    else
      axis_name = "Z";

    DirectionalDistributionFactory::validateAxisName( axis_name );
    
    Axis axis = convertAxisNameToAxisEnum( axis_name );
    
    return std::shared_ptr<DirectionalDistribution>(
		     new SphericalDirectionalDistribution( theta_distribution,
							   mu_distribution,
							   axis ) );
  }
}

// Create an isotropic distribution
std::shared_ptr<DirectionalDistribution> 
DirectionalDistributionFactory::createIsotropicDistribution()
{
  return s_isotropic_directional_dist;
}

// Validate a distribution representation
void DirectionalDistributionFactory::validateDistributionRep( 
			       const Teuchos::ParameterList& distribution_rep )
{
  if( !distribution_rep.isParameter( "Direction" ) )
  {  
    TEST_FOR_EXCEPTION( !distribution_rep.isParameter( "Mu Distribution" ),
			InvalidDirectionalDistributionRepresentation,
			"Error: A spherical directional distribution needs to "
			"have the mu distribution specified!" );
  }
  else
  {
    TEST_FOR_EXCEPTION( !distribution_rep.isParameter( "Direction" ),
			InvalidDirectionalDistributionRepresentation,
			"Error: A mono directional distribution needs to "
			"have the direction specified!" );
  }
}

// Validate the axis name
void DirectionalDistributionFactory::validateAxisName( 
						 const std::string& axis_name )
{
  TEST_FOR_EXCEPTION( !isValidAxisName( axis_name ),
		      InvalidDirectionalDistributionRepresentation,
		      "Error: An invalid axis was specified (" 
		      << axis_name << "). Only 'X', 'Y', and 'Z' are valid "
		      " names!" );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DirectionalDistributionFactory.cpp
//---------------------------------------------------------------------------//
