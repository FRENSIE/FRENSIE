//---------------------------------------------------------------------------//
//!
//! \file   DataGen_IncoherentCrossSectionEvaluator.cpp
//! \author Alex Robinson
//! \brief  Incoherent cross section evaluator definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "DataGen_IncoherentCrossSectionEvaluator.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Default Constructor (free electron)
IncoherentCrossSectionEvaluator::IncoherentCrossSectionEvaluator()
  : d_scattering_function( new Utility::UniformDistribution(
			      0.0, std::numeric_limits<double>::max(), 1.0 ) );

// Constructor (bound electron)
IncoherentCrossSectionEvaluator::IncoherentCrossSectionEvaluator(
			   const Teuchos::RCP<const Utility::OneDDistribution>&
			   scattering_function )
  : d_scattering_function( scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );

  // Force the quadrature kernel to throw exceptions
  Utility::GaussKronrodQuadraturekernel::throwExceptions( true );
}

// Evaluate the differential incoherent cross section (dc/dx)
/*! \details The returned cross section will have units of barns
 */
double IncoherentCrossSectionEvaluator::evaluateDifferentialCrossSection(
		 const double inverse_energy_loss_ratio,
		 const Utility::KleinNishinaDistribution& distribution ) const
{
  // Make sure the inverse energy loss ratio is valid
  testPrecondition( inverse_energy_loss_ratio >=
		    distribution.getLowerBoundOfIndepVar() );
  testPrecondition( inverse_energy_loss_ratio <=
		    distribution.getUpperBoundOfIndepVar() );

  // The inverse wavelength of the incoming energy must be calculated
  const double inverse_wavelength = distribution.getEnergy()/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);

  double scattering_angle_cosine = 
    1.0 - (inverse_energy_gain_ratio-1.0)/distribution.getAlpha();

  // Check for roundoff error
  if( Teuchos::ScalarTraits<double>::magnitude(scattering_angle_cosine) >1.0 )
    scattering_angle_cosine = copysign( 1.0, scattering_angle_cosine );

  const double scattering_function_arg = 
    sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength;

  const double scattering_function_value = 
    d_scattering_function->evaluate( scattering_function_arg );

  // Make sure the scattering angle is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  // Make sure the scattering function is valid
  testPostcondition( scattering_function_value >= 0.0 );
  testPostcondition( scattering_function_value <= 100.0 );

  return distribution.evaluate( inverse_energy_gain_ratio )*
    scattering_function_value/1e-24;
}

// Evaluate the incoherent cross section
/*! \details The returned cross section will have units of barns.
 */
double IncoherentCrossSectionEvaluator::evaluateCrossSection( 
						 const double energy, 
						 const double precision ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  
  double cross_section = 0.0;

  Utility::KleinNishinaDistribution distribution( energy );

  boost::function<double (double x)> diff_cs_wrapper = 
    boost::bind<double>( &IncoherentCrossSectionEvaluator::evaluateDifferentialCrossSection,
			 boost::cref( *this ),
			 _1,
			 distribution );
  
  double abs_error;

  Utility::GaussKronrodQuadratureKernel quadrature_kernel( precision );

  quadrature_kernel.integrateAdaptively<15>(
					diff_cs_wrapper,
					distribution.getLowerBoundOfIndepVar(),
					distribution.getUpperBoundOfIndepVar(),
					cross_section,
					abs_error );

  return cross_section;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_IncoherentCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
