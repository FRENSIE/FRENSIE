//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentCrossSectionEvaluator.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent cross section definition
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
#include "DataGen_AdjointIncoherentCrossSectionEvaluator.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Return the energy of the max cross section value
double AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
						      const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( max_energy ) );
  testPrecondition( max_energy > 0.0 );

  return max_energy/(1.0 + 2.0*max_energy/Utility::PhysicalConstants::electron_rest_mass_energy);
}

// Check if the energy corresponds to the max cross section value at any
// max energy
double AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondToAMaxCrossSectionValue( 
							  const double energy )
{
  return energy < Utility::PhysicalConstants::electron_rest_mass_energy/2.0;
}

// Return the max energy that results in a max cross section value at energy
double AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
							  const double energy )
{
  // Make sure the energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  testPrecondition( energy < 
		    Utility::PhysicalConstants::electron_rest_mass_energy/2.0);
		    
  return energy/(1.0 - 2.0*energy/Utility::PhysicalConstants::electron_rest_mass_energy);
}

// Default constructor
/*! \details This class will just return the integrated adjoint Klein-Nishina
 * cross section when the default constructor is called.
 */
AdjointIncoherentCrossSectionEvaluator::AdjointIncoherentCrossSectionEvaluator()
  : d_scattering_function( new Utility::UniformDistribution( 
			      0.0, std::numeric_limits<double>::max(), 1.0 ) ),
    d_quadrature_kernel( new Utility::GaussKronrodQuadratureKernel( 1e-6 ) )
{ /* ... */ }

// Constructor
AdjointIncoherentCrossSectionEvaluator::AdjointIncoherentCrossSectionEvaluator(
    const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function )
  : d_scattering_function( scattering_function ),
    d_quadrature_kernel( new Utility::GaussKronrodQuadratureKernel( 1e-6 ) )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
}

// Return the cross section value at a given energy and max energy
double AdjointIncoherentCrossSectionEvaluator::evaluateCrossSection( 
						const double energy, 
					        const double max_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( energy <= max_energy );

  double cross_section;

  if( energy < max_energy )
  {
    Utility::AdjointKleinNishinaDistribution distribution( energy, max_energy);

    boost::function<double (double x)> diff_adjoint_incoh_wrapper = 
      boost::bind<double>( &AdjointIncoherentCrossSectionEvaluator::evaluateDifferentialAdjointIncoherentCrossSection,
			   boost::cref( *this ),
			   _1,
			   distribution );

    double abs_error;
    
    d_quadrature_kernel->integrateAdaptively<21>(
					diff_adjoint_incoh_wrapper,
					distribution.getLowerBoundOfIndepVar(),
					distribution.getUpperBoundOfIndepVar(),
					cross_section,
					abs_error );
  }
  else
    cross_section = 0.0;

  return cross_section;
}

// Evaluate the differential adjoint incoherent cross section (dc/dx)
double AdjointIncoherentCrossSectionEvaluator::evaluateDifferentialAdjointIncoherentCrossSection(
	   const double inverse_energy_gain_ratio, 
	   const Utility::AdjointKleinNishinaDistribution& distribution ) const
{
  double inverse_wavelength = distribution.getEnergy()/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);
  
  double scattering_angle_cosine = 
    1.0 - (1.0 - inverse_energy_gain_ratio)/distribution.getAlpha();

  double scat_func_arg = 
    sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength;
  
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );

  return distribution.evaluate( inverse_energy_gain_ratio )*
    d_scattering_function->evaluate( scat_func_arg );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
