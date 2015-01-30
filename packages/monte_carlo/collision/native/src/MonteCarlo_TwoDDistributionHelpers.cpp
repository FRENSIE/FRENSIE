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
      lower_bin_boundary, upper_bin_boundary;
    
    lower_bin_boundary = dependent_distribution.begin();
    upper_bin_boundary = dependent_distribution.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							  lower_bin_boundary,
							  upper_bin_boundary,
							  independent_variable );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate the interpolation fraction
    double interpolation_fraction = ( independent_variable - lower_bin_boundary->first )/
      (upper_bin_boundary->first - lower_bin_boundary->first);
    
    double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
    if( random_number < interpolation_fraction )
    {
      return upper_bin_boundary->second->sample();
    }
    else
    {
      return lower_bin_boundary->second->sample();
    }
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDDistributionHelpers.cpp
//---------------------------------------------------------------------------//
