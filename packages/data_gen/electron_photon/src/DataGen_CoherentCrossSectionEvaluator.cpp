//---------------------------------------------------------------------------//
//!
//! \file   DataGen_CoherentCrossSectionEvaluator.cpp
//! \author Alex Robinson
//! \brief  Coherent cross section evaluator definition
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
#include "DataGen_CoherentCrossSectionEvaluator.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Default constructor (free electron)
CoherentCrossSectionEvaluator::CoherentCrossSectionEvaluator()
  : d_atomic_form_factor( new Utility::UniformDistribution( 
			       0.0, std::numeric_limits<double>::max(), 1.0 ) )
{ /* ... */ }

// Constructor (bound electron)
CoherentCrossSectionEvaluator::CoherentCrossSectionEvaluator(
			   const Teuchos::RCP<const Utility::OneDDistribution>&
			   atomic_form_factor )
  : d_atomic_form_factor( atomic_form_factor )
{
  // Make sure the atomic form factor is valid
  testPrecondition( !atomic_form_factor.is_null() );
  
  // Force the quadrature kernel to throw exceptions
  Utility::GaussKronrodQuadratureKernel::throwExceptions( true );
}

// Evaluate the differential coherent cross section (dc/dmu)
/*! \details The returned cross section will have units of barns
 */
double CoherentCrossSectionEvaluator::evaluateDifferentialCrossSection(
				   const double energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // The inverse wavelength of the incoming energy must be calculated
  const double inverse_wavelength = energy/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);

  const double atomic_form_factor_arg = 
    sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength;

  double atomic_form_factor_value;

  if( atomic_form_factor_arg == 0.0 ) 
  {
    atomic_form_factor_value = d_atomic_form_factor->evaluate(
			     d_atomic_form_factor->getLowerBoundOfIndepVar() );
  }
  else
  {
    atomic_form_factor_value = 
      d_atomic_form_factor->evaluate( atomic_form_factor_arg );
  }

  // Make sure the atomic form factor is valid
  testPostcondition( atomic_form_factor_value >= 0.0 );
  testPostcondition( atomic_form_factor_value <= 100.0 );

  return Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius*
    (1.0+scattering_angle_cosine*scattering_angle_cosine)*
    atomic_form_factor_value*
    atomic_form_factor_value/1e-24;
}

// Evaluate the coherent cross section
/*! \details The returned cross section will have units of barns
 */
double CoherentCrossSectionEvaluator::evaluateCrossSection( 
                                                 const double energy,
                                                 const double precision ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  boost::function<double (double mu)> diff_cs_wrapper = 
    boost::bind<double>( &CoherentCrossSectionEvaluator::evaluateDifferentialCrossSection,
			 boost::cref( *this ),
			 energy,
			 _1 );

  double abs_error;

  Utility::GaussKronrodQuadratureKernel quadrature_kernel( precision );

  quadrature_kernel.integrateAdaptively<15>( diff_cs_wrapper,
					     -1.0, 
					     1.0,
					     cross_section,
					     abs_error );

  return cross_section;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_CoherentCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
