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
#include "Utility_SortAlgorithms.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
/*! \details The Compton profiles are symmetric so only one half of the 
 * distribution should be passed in. The electron momentum grid should 
 * be in units of me*e^2/h_bar or atomic units and not me*c units. 
 * The Compton profile should have units of h_bar/(me*e^2) and not 1/(me*c)
 * units.
 */
OccupationNumberEvaluator::OccupationNumberEvaluator(
		    const Teuchos::Array<double> electron_momentum_projections,
		    const Teuchos::Array<double> compton_profile )
  : d_compton_profile_norm_constant( 1.0 )
{
  // Make sure the electron momentum projections are valid
  testPrecondition( electron_momentum_projections.front() == 0.0 );
  testPrecondition( electron_momentum_projections.back() >= 100.0 );
  testPrecondition( electron_momentum_projections.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( 
				       electron_momentum_projections.begin(),
				       electron_momentum_projections.end() ) );
  // Make sure the compton profile is valid
  testPrecondition( compton_profile.back() > 0.0 );
  testPrecondition( compton_profile.size() == 
		    electron_momentum_projections.size() );

  // Force the quadrature kernel throw exceptions
  Utility::GaussKronrodQuadratureKernel::throwExceptions( true );

  // Create the complete compton profile and convert to me*c units
  Teuchos::Array<double> complete_electron_momentum_projections;
  Teuchos::Array<double> complete_compton_profile;
  unsigned middle_index;

  // Check if the grid needs to be extended
  if( electron_momentum_projections.back() <  
      Utility::PhysicalConstants::inverse_fine_structure_constant )
  {
    complete_electron_momentum_projections.resize( 
			       (electron_momentum_projections.size()+1)*2 - 1);
    complete_compton_profile.resize( (compton_profile.size()+1)*2 - 1 );

    middle_index = electron_momentum_projections.size();
  }
  else
  {
    complete_electron_momentum_projections.resize( 
				   electron_momentum_projections.size()*2 - 1);
    complete_compton_profile.resize( compton_profile.size()*2 - 1 );

    middle_index = electron_momentum_projections.size() - 1;
  }

  for( unsigned i = 0u; i < electron_momentum_projections.size(); ++i )
  {    
    double scaled_electron_momentum_proj = electron_momentum_projections[i]/
	Utility::PhysicalConstants::inverse_fine_structure_constant;

    double scaled_compton_profile = compton_profile[i]*
	Utility::PhysicalConstants::inverse_fine_structure_constant;      
    
    if( i != 0u )
    {
      // Positive side of profile
      complete_electron_momentum_projections[middle_index+i] = 
	scaled_electron_momentum_proj;
    
      complete_compton_profile[middle_index+i] = scaled_compton_profile;

      // Negative side of profile
      complete_electron_momentum_projections[middle_index-i] = 
	-scaled_electron_momentum_proj;
    
      complete_compton_profile[middle_index-i] = scaled_compton_profile;
    }
    else // Middle of profile (pz = 0.0)
    {
      complete_electron_momentum_projections[middle_index] = 0.0;	
      
      complete_compton_profile[middle_index] = scaled_compton_profile;
    }
  }

  // Check if the grid needs to be extended
  if( electron_momentum_projections.back() <  
      Utility::PhysicalConstants::inverse_fine_structure_constant )
  {
    double profile_0 = 
      complete_compton_profile[complete_compton_profile.size()-3];
    double profile_1 = 
      complete_compton_profile[complete_compton_profile.size()-2];
    double projection_0 = 
      complete_electron_momentum_projections[complete_electron_momentum_projections.size()-3];
    double projection_1 = 
      complete_electron_momentum_projections[complete_electron_momentum_projections.size()-2];

    double processed_slope = (log(profile_1)-log(profile_0))/
      (projection_1-projection_0);

    double extrapolated_profile = exp( log(profile_0) + 
				       processed_slope*(1.0-projection_0) );
    
    complete_electron_momentum_projections.front() = -1.0;
    complete_compton_profile.front() = extrapolated_profile;
        
    complete_electron_momentum_projections.back() = 1.0;
    complete_compton_profile.back() = extrapolated_profile;
  }
  
  // Store the profile in a tabular distribution for quick interpolation
  d_compton_profile.reset( new Utility::TabularDistribution<Utility::LogLin>(
					complete_electron_momentum_projections,
					complete_compton_profile ) );
  
  // Roundoff errors are common in the available Compton profile tables - 
  // renormalize the table
  d_compton_profile_norm_constant = this->evaluateOccupationNumber( 
			 complete_electron_momentum_projections.back(), 1e-4 );
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
    
    Utility::GaussKronrodQuadratureKernel quadrature_kernel( precision );

    if( electron_momentum_projection < 
	d_compton_profile->getUpperBoundOfIndepVar() )
    {
      quadrature_kernel.integrateAdaptively<15>(
				  compton_profile_wrapper,
				  d_compton_profile->getLowerBoundOfIndepVar(),
				  electron_momentum_projection,
				  occupation_number,
				  abs_error );
    }
    else
    {
      quadrature_kernel.integrateAdaptively<15>(
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


} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_OccupationNumberEvaluator.cpp
//---------------------------------------------------------------------------//
