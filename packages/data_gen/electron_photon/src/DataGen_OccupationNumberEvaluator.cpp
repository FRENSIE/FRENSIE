//---------------------------------------------------------------------------//
//!
//! \file   DataGen_OccupationNumberEvaluator.cpp
//! \author Alex Robinson
//! \brief  The occupation number evaluator definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <functional>

// FRENSIE Includes
#include "DataGen_OccupationNumberEvaluator.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
OccupationNumberEvaluator::OccupationNumberEvaluator(
            std::unique_ptr<const MonteCarlo::ComptonProfile>& compton_profile,
            const double norm_constant_precision )
  : d_compton_profile_norm_constant( 1.0 )
{
  // Make sure the Compton profile is valid
  testPrecondition( compton_profile.get() );
  // Make sure the precision is valid
  testPrecondition( norm_constant_precision > 0.0 );
  testPrecondition( norm_constant_precision < 1.0 );

  // Take ownership of the Compton profile object
  d_compton_profile.swap( compton_profile );

  // Roundoff errors are common in the available Compton profile tables -
  // renormalize the table
  d_compton_profile_norm_constant = this->evaluateOccupationNumber(
                          d_compton_profile->getUpperBoundOfMomentum().value(),
                          norm_constant_precision );
}

// Return the normalization constant used with the Compton profile
double OccupationNumberEvaluator::getComptonProfileNormConstant() const
{
  return d_compton_profile_norm_constant;
}

// Evaluate the compton profile
/*! \details The electron momentum projection must be in me*c units. The
 * returned Compton profile value will have units of (me*c)^-1.
 */
double OccupationNumberEvaluator::evaluateComptonProfile(
			      const double electron_momentum_projection ) const
{
  // Make sure the electron momentum projection is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf(
					      electron_momentum_projection ) );

  return d_compton_profile->evaluate( electron_momentum_projection*Utility::Units::mec_momentum ).value()/
    d_compton_profile_norm_constant;
}

// Return a function that wraps the Compton profile evaluation method
std::function<double(double)>
OccupationNumberEvaluator::getComptonProfileEvaluationWrapper() const
{
  return std::bind<double>( &OccupationNumberEvaluator::evaluateComptonProfile,
                            std::cref( *this ),
                            std::placeholders::_1 );
}

// Evaluate the occupation number at a given electron momentum projection
/*! \details The electron momentum projection must be in me*c units. The
 * returned occupation number is unitless.
 */
double OccupationNumberEvaluator::evaluateOccupationNumber(
				     const double electron_momentum_projection,
				     const double precision ) const
{
  // Make sure the electron momentum projection is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf(
					      electron_momentum_projection ) );

  long double occupation_number;

  if( electron_momentum_projection <=
      d_compton_profile->getLowerBoundOfMomentum().value() )
  {
    occupation_number = 0.0;
  }
  else if( electron_momentum_projection >
	   d_compton_profile->getLowerBoundOfMomentum().value() )
  {
    std::function<double(double)> compton_profile_wrapper =
      this->getComptonProfileEvaluationWrapper();

    long double abs_error;

    Utility::GaussKronrodIntegrator<long double> quadrature_gkq( precision );

    if( electron_momentum_projection <
	d_compton_profile->getUpperBoundOfMomentum().value() )
    {
      quadrature_gkq.integrateAdaptively<15>(
			  compton_profile_wrapper,
			  d_compton_profile->getLowerBoundOfMomentum().value(),
                          electron_momentum_projection,
                          occupation_number,
                          abs_error );
    }
    else
    {
      quadrature_gkq.integrateAdaptively<15>(
			  compton_profile_wrapper,
			  d_compton_profile->getLowerBoundOfMomentum().value(),
                          d_compton_profile->getUpperBoundOfMomentum().value(),
                          occupation_number,
                          abs_error );
    }
  }

  // Make sure the occupation number is valid
  testPostcondition( occupation_number >= 0.0 );

  return occupation_number;
}

// Return a function that wraps the occupation number evaluation method
std::function<double(double)>
OccupationNumberEvaluator::getOccupationNumberEvaluationWrapper(
                                                 const double precision ) const
{
  return std::bind<double>( &OccupationNumberEvaluator::evaluateOccupationNumber,
                            std::cref( *this ),
                            std::placeholders::_1,
                            precision );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_OccupationNumberEvaluator.cpp
//---------------------------------------------------------------------------//
