//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NeutronScatteringAngularDistribution.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering angular distribution base class definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringAngularDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace Facemc{

// Constructor
NeutronScatteringAngularDistribution::NeutronScatteringAngularDistribution( 
	const NeutronScatteringAngularDistribution::AngularDistribution& dist )
  : d_angular_distribution( dist )
{
  // Make sure the array has at least one value
  testPrecondition( dist.size() > 0 );
  // Make sure that the array is sorted
  testPrecondition( Utility::Sort::isSortedAscending<Utility::FIRST>( 
				                                dist.begin(),
								dist.end() ) );
}

// Sample a scattering angle cosine
double NeutronScatteringAngularDistribution::sampleAngleCosine( 
						    const double energy ) const
{
  double angle_cosine;

  if( energy < d_angular_distribution.front().first )
  {
    angle_cosine = 
      d_angular_distribution.front().second->sample();
  }
  else if( energy >= d_angular_distribution.back().first )
  {
    angle_cosine = 
      d_angular_distribution.back().second->sample();
  }
  else
  {
    Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >::const_iterator
      lower_bin_boundary, upper_bin_boundary;
    
    lower_bin_boundary = d_angular_distribution.begin();
    upper_bin_boundary = d_angular_distribution.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							  lower_bin_boundary,
							  upper_bin_boundary,
							  energy );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate the interpolation fraction
    double interpolation_fraction = ( energy - lower_bin_boundary->first )/
      (upper_bin_boundary->first - lower_bin_boundary->first);
    
    double angle_cosine_prime;
    double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
    if( random_number < interpolation_fraction )
      angle_cosine_prime = upper_bin_boundary->second->sample();
    else
      angle_cosine_prime = lower_bin_boundary->second->sample();
  
    double angle_cosine_lower = 
      lower_bin_boundary->second->getLowerBoundOfIndepVar() + 
      interpolation_fraction*
      (upper_bin_boundary->second->getLowerBoundOfIndepVar() - 
       lower_bin_boundary->second->getLowerBoundOfIndepVar());

    double angle_cosine_upper = 
      lower_bin_boundary->second->getUpperBoundOfIndepVar() +
      interpolation_fraction*
      (upper_bin_boundary->second->getUpperBoundOfIndepVar() - 
       lower_bin_boundary->second->getUpperBoundOfIndepVar());
  
    // Calculate the outgoing angle
    if( random_number < interpolation_fraction )
    {
      angle_cosine = angle_cosine_lower + 
	(angle_cosine_prime - 
	 upper_bin_boundary->second->getLowerBoundOfIndepVar())*
	(angle_cosine_upper - angle_cosine_lower)/
	(upper_bin_boundary->second->getUpperBoundOfIndepVar() - 
	 upper_bin_boundary->second->getLowerBoundOfIndepVar());
    }
    else
    {
      angle_cosine = angle_cosine_lower +
	(angle_cosine_prime - 
	 lower_bin_boundary->second->getLowerBoundOfIndepVar())*
	(angle_cosine_upper - angle_cosine_lower)/
	(lower_bin_boundary->second->getUpperBoundOfIndepVar() - 
       lower_bin_boundary->second->getLowerBoundOfIndepVar());
    }
  }

  // Due to floating-point roundoff, it is possible for the scattering angle
  // cosine to be outside [-1,1]. When this occurs, manually set to -1 or 1.
  if(Teuchos::ScalarTraits<double>::magnitude(angle_cosine) >1.0)
    angle_cosine = copysign( 1.0, angle_cosine );

  // Make sure that the scattering angle cosine is valid
  testPrecondition( angle_cosine >= -1.0 );
  testPrecondition( angle_cosine <= 1.0 );

  return angle_cosine;
}



} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringAngularDistribution.cpp
//---------------------------------------------------------------------------//
