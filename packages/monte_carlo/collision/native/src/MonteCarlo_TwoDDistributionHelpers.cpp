//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDDistributionHelpers.cpp
//! \author Luke Kersting
//! \brief  Two dimensional distribution helpers base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_SearchAlgorithms.hpp"

namespace MonteCarlo{


// Sample a two dimensional ditribution
/*! \details This function is designed for lin-lin base interpolation data and 
 *  is not appropriate for unit base interpolations
 */  
double sampleTwoDDistribution(
   const double independent_variable,
   const Teuchos::Array<Utility::Pair<double,
     Teuchos::RCP<Utility::OneDDistribution> > >& dependent_distribution )
{

  if( independent_variable < dependent_distribution.front().first )
  {
    return dependent_distribution.front().second->sample();
  }
  else if( independent_variable >= dependent_distribution.back().first )
  {
    return dependent_distribution.back().second->sample();
  }
  else
  {
    Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >::const_iterator
      lower_dist_boundary, upper_dist_boundary;
    
    lower_dist_boundary = dependent_distribution.begin();
    upper_dist_boundary = dependent_distribution.end();
    
    lower_dist_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							  lower_dist_boundary,
							  upper_dist_boundary,
							  independent_variable );

    upper_dist_boundary = lower_dist_boundary;
    ++upper_dist_boundary;

    // Calculate the interpolation fraction
    double interpolation_fraction = ( independent_variable - lower_dist_boundary->first )/
      (upper_dist_boundary->first - lower_dist_boundary->first);
    
    // Sample the upper and lower distributions using the same random number
    double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
    double upper_bin_dependent_variable = 
                   upper_dist_boundary->second->sampleCDFValue( random_number );

    double lower_bin_dependent_variable = 
                   lower_dist_boundary->second->sampleCDFValue( random_number );

    // Linearly interpolate between the upper and lower distributions
    return lower_bin_dependent_variable + interpolation_fraction*
                  (upper_bin_dependent_variable - lower_bin_dependent_variable);
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers.cpp
//---------------------------------------------------------------------------//
