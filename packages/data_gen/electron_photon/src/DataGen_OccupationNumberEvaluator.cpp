//---------------------------------------------------------------------------//
//!
//! \file   DataGen_OccupationNumberEvaluator.cpp
//! \author Alex Robinson
//! \brief  The occupation number evaluator definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Teuchos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "DataGen_OccupationNumberEvaluator.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
/*! \details The full electron momentum grid and Compton profile should 
 * be given. 
 */
OccupationNumberEvaluator::OccupationNumberEvaluator(
		   const Teuchos::Array<double>& electron_momentum_projections,
		   const Teuchos::Array<double>& compton_profile,
		   const double norm_constant_precision )
  : d_compton_profile_norm_constant( 1.0 )
{
  // Make sure the electron momentum projections are valid
  testPrecondition( electron_momentum_projections.size() > 1 );
  testPrecondition( electron_momentum_projections.front() != 0.0 );
  testPrecondition( electron_momentum_projections.front() == 
		    -electron_momentum_projections.back() );
  testPrecondition( Utility::Sort::isSortedAscending( 
				       electron_momentum_projections.begin(),
				       electron_momentum_projections.end() ) );
  // Make sure the compton profile is valid
  testPrecondition( compton_profile.back() > 0.0 );
  testPrecondition( compton_profile.front() == compton_profile.back() );
  testPrecondition( compton_profile.size() == 
		    electron_momentum_projections.size() );
  
  // Store the profile in a tabular distribution for quick interpolation
  d_compton_profile.reset( new Utility::TabularDistribution<Utility::LogLin>(
					         electron_momentum_projections,
					         compton_profile ) );
  
  // Roundoff errors are common in the available Compton profile tables - 
  // renormalize the table
  d_compton_profile_norm_constant = this->evaluateOccupationNumber( 
			                  electron_momentum_projections.back(),
					  norm_constant_precision );
}

// Return the normalization constant used with the Compton profile
double OccupationNumberEvaluator::getComptonProfileNormConstant() const
{
  return d_compton_profile_norm_constant;
}

// Evaluate the compton profile
double OccupationNumberEvaluator::evaluateComptonProfile(
			      const double electron_momentum_projection ) const
{
  // Make sure the electron momentum projection is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf(
					      electron_momentum_projection ) );

  return d_compton_profile->evaluate( electron_momentum_projection )/
    d_compton_profile_norm_constant;
}

// Evaluate the occupation number at a given electron momentum projection
double OccupationNumberEvaluator::evaluateOccupationNumber(
				     const double electron_momentum_projection,
				     const double precision ) const
{
  // Make sure the electron momentum projection is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf(
					      electron_momentum_projection ) );

  double occupation_number;
  long double long_occupation_number;

  if( electron_momentum_projection <= 
      d_compton_profile->getLowerBoundOfIndepVar() )
  {
    occupation_number = 0.0;
  }
  else if( electron_momentum_projection > 
	   d_compton_profile->getLowerBoundOfIndepVar() )
  {
    boost::function<double (double pz)> compton_profile_wrapper = 
      boost::bind<double>( &OccupationNumberEvaluator::evaluateComptonProfile,
			   boost::cref( *this ),
			   _1 );

    long double long_abs_error;
    
    Utility::GaussKronrodIntegrator<long double> quadrature_gkq( precision );

    if( electron_momentum_projection < 
	d_compton_profile->getUpperBoundOfIndepVar() )
    {
      quadrature_gkq.integrateAdaptively<15>(
				  compton_profile_wrapper,
				  (long double)d_compton_profile->getLowerBoundOfIndepVar(),
				  (long double)electron_momentum_projection,
				  long_occupation_number,
				  long_abs_error );
    }
    else
    {
      quadrature_gkq.integrateAdaptively<15>(
				  compton_profile_wrapper,
				  (long double)d_compton_profile->getLowerBoundOfIndepVar(),
				  (long double)d_compton_profile->getUpperBoundOfIndepVar(),
				  long_occupation_number,
				  long_abs_error );
    }
    occupation_number = (double)long_occupation_number;
  }

  // Make sure the occupation number is valid
  testPostcondition( occupation_number >= 0.0 );

  return occupation_number;
}
/*
// Evaluate the compton profile
double OccupationNumberEvaluator::evaluateComptonProfile(
			      const double electron_momentum_projection ) const
{
  // Make sure the electron momentum projection is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf(
					      electron_momentum_projection ) );

  return d_compton_profile->evaluate( electron_momentum_projection )/
    d_compton_profile_norm_constant;
}

// Evaluate the occupation number at a given electron momentum projection
double OccupationNumberEvaluator::evaluateOccupationNumber(
				     const double electron_momentum_projection,
				     const double precision ) const
{
  // Make sure the electron momentum projection is valid
  testPrecondition( std::isfinite( electron_momentum_projection ) );

  double occupation_number;

  if( electron_momentum_projection <= 
      d_compton_profile->getLowerBoundOfIndepVar() )
  {
    occupation_number = 0.0;
  }
  else if( electron_momentum_projection > 
	   d_compton_profile->getLowerBoundOfIndepVar() )
  {
    boost::function<double (double pz)> compton_profile_wrapper = 
      boost::bind<double>( &OccupationNumberEvaluator::evaluateComptonProfile,
			   boost::cref( *this ),
			   _1 );
    
    double abs_error;
    Utility::GaussKronrodIntegrator<double> quadrature_gkq( precision );

    if( electron_momentum_projection < 
	d_compton_profile->getUpperBoundOfIndepVar() )
    {
      quadrature_gkq.integrateAdaptively<15>(
				  compton_profile_wrapper,
				  d_compton_profile->getLowerBoundOfIndepVar(),
				  electron_momentum_projection,
				  occupation_number,
				  abs_error );
    }
    else
    {
      quadrature_gkq.integrateAdaptively<15>(
				  compton_profile_wrapper,
				  d_compton_profile->getLowerBoundOfIndepVar(),
				  d_compton_profile->getUpperBoundOfIndepVar(),
				  occupation_number,
				  abs_error );
    }
  }

  // Make sure the occupation number is valid
  testPostcondition( occupation_number >= 0.0 );

  return occupation_number;
}
*/
} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_OccupationNumberEvaluator.cpp
//---------------------------------------------------------------------------//
