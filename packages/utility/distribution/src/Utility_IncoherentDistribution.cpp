//---------------------------------------------------------------------------//
//!
//! \file   Utility_IncoherentDistribution.cpp
//! \author Alex Robinson
//! \brief  Incoherent photon scattering distribution class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_IncoherentDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
IncoherentDistribution::IncoherentDistribution()
  : KleinNishinaDistribution(),
    d_scattering_function.reset( 
	new UniformDistribution( 0, std::numeric_limits<double>::max(), 1.0 ) )
{ /* ... */ }

// Constructor
IncoherentDistribution::IncoherentDistribution(
	       const Teuchos::RCP<const OneDDistribution>& scattering_function,
	       const double energy,
	       const bool use_kahn_sampling_only,
	       const bool use_exact_integrated_cross_sec )
  : KleinNishinaDistribution( energy, 
			      use_kahn_sampling_only,
			      use_exact_integrated_cross_sec ),
    d_scattering_function( scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
  testPrecondition( scattering_function->isContinuous() );
}

// Copy constructor
IncoherentDistribution::IncoherentDistribution( 
				  const IncoherentDistribution& dist_instance )
  : KleinNishinaDistribution( dist_instance ),
    d_scattering_function( dist_instance.d_scattering_function )
{ /* ... */ }

// Assignment operator
IncoherentDistribution& operator=( 
				  const IncoherentDistribution& dist_instance )
{
  KleinNishinaDistribution::operator=( dist_instance );
  
  if( this != &dist_instance )
  {
    d_scattering_function = dist_instance.d_scattering_function;
  }
  
  return *this;
}

// Evaluate the distribution
double IncoherentDistribution::evaluate( const double indep_var_value ) const
{
  double value = KleinNishinaDistribution::evaluate( indep_var_value );
  
  
}

// Evaluate the PDF
double IncoherentDistribution::evalautePDF( const double indep_var_value) const
{

}

// Return a sample from the distribution
double IncoherentDistribution::sample() const
{
  
}

// Return a random sample and record the number of trials
double IncoherentDistribution::sampleAndRecordTrials( unsigned& trials ) const
{

}

// Return the distribution type
OneDDistributionType IncoherentDistribution::getDistributionType() const
{
  return IncoherentDistribution::distribution_type;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_IncoherentDistribution.cpp
//---------------------------------------------------------------------------//
