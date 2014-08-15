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
    
    double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
    if( random_number < interpolation_fraction )
      angle_cosine = upper_bin_boundary->second->sample();
    else
      angle_cosine = lower_bin_boundary->second->sample();
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

// Evaluate the PDF
double NeutronScatteringAngularDistribution::evaluatePDF( 
				const double energy,
				const double cm_scattering_angle_cosine ) const
{
  double pdf_value;
  
  if( energy < d_angular_distribution.front().first )
  {
    pdf_value = d_angular_distribution.front().second->evaluatePDF( 
						  cm_scattering_angle_cosine );
  }
  else if( energy >= d_angular_distribution.back().first )
  {
    pdf_value = d_angular_distribution.back().second->evaluatePDF(
						  cm_scattering_angle_cosine );
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

    // Get the PDF value on the two grid points
    double pdf_low = lower_bin_boundary->second->evaluatePDF( 
						  cm_scattering_angle_cosine );
    double pdf_high = upper_bin_boundary->second->evaluatePDF(
						  cm_scattering_angle_cosine );

    // Use linear interpolation to evaluate the PDF at the desired energy
    pdf_value = pdf_low + 
      (pdf_high-pdf_low)/(upper_bin_boundary->first-lower_bin_boundary->first)*
      (energy - lower_bin_boundary->first);
  }

  // Make sure the PDF value is valid
  testPostcondition( pdf_value >= 0.0 );

  return pdf_value;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringAngularDistribution.cpp
//---------------------------------------------------------------------------//
