//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringAngularDistribution.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The nuclear scattering angular distribution base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace MonteCarlo{

// Constructor
NuclearScatteringAngularDistribution::NuclearScatteringAngularDistribution(
	const NuclearScatteringAngularDistribution::AngularDistribution& dist )
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
double NuclearScatteringAngularDistribution::sampleAngleCosine(
						    const double energy ) const
{
  double angle_cosine;

  angle_cosine =
    sampleTwoDDistributionIndependent( energy, d_angular_distribution );

  // Due to floating-point roundoff, it is possible for the scattering angle
  // cosine to be outside [-1,1]. When this occurs, manually set to -1 or 1.
  if( std::fabs(angle_cosine) > 1.0 )
    angle_cosine = copysign( 1.0, angle_cosine );

  // Make sure that the scattering angle cosine is valid
  testPostcondition( angle_cosine >= -1.0 );
  testPostcondition( angle_cosine <= 1.0 );

  return angle_cosine;
}

// Evaluate the PDF
double NuclearScatteringAngularDistribution::evaluatePDF(
				const double energy,
				const double scattering_angle_cosine ) const
{
  double pdf_value;

  if( energy < Utility::get<0>( d_angular_distribution.front() ) )
  {
    pdf_value = Utility::get<1>( d_angular_distribution.front() )->evaluatePDF(
						  scattering_angle_cosine );
  }
  else if( energy >= Utility::get<0>( d_angular_distribution.back() ) )
  {
    pdf_value = Utility::get<1>( d_angular_distribution.back() )->evaluatePDF(
						  scattering_angle_cosine );
  }
  else
  {
    AngularDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;

    lower_bin_boundary = d_angular_distribution.begin();
    upper_bin_boundary = d_angular_distribution.end();

    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>(
							  lower_bin_boundary,
							  upper_bin_boundary,
							  energy );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Get the PDF value on the two grid points
    double pdf_low = Utility::get<1>( *lower_bin_boundary )->evaluatePDF(
						  scattering_angle_cosine );
    double pdf_high = Utility::get<1>( *upper_bin_boundary )->evaluatePDF(
						  scattering_angle_cosine );

    // Use linear interpolation to evaluate the PDF at the desired energy
    pdf_value = pdf_low +
      (pdf_high-pdf_low)/
      (Utility::get<0>(*upper_bin_boundary)-Utility::get<0>(*lower_bin_boundary))*
       (energy - Utility::get<0>(*lower_bin_boundary));
  }

  // Make sure the PDF value is valid
  testPostcondition( pdf_value >= 0.0 );

  return pdf_value;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringAngularDistribution.cpp
//---------------------------------------------------------------------------//
