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
#include "Utility_GaussKronrodQuadratureKernel.hpp"
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
			      0.0, std::numeric_limits<double>::max(), 1.0 ) )
{ 
  // Force the quadrature kernel throw exceptions
  Utility::GaussKronrodQuadratureKernel::throwExceptions( true );
}

// Constructor
/*! \details The scattering function must have the electrom recoil momentum,
 * in units of inverse cm (not inverse Angstroms), as the independent
 * variable.
 */
AdjointIncoherentCrossSectionEvaluator::AdjointIncoherentCrossSectionEvaluator(
    const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function )
  : d_scattering_function( scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );

  // Force the quadrature kernel to throw exceptions
  Utility::GaussKronrodQuadratureKernel::throwExceptions( true );
}

// Evaluate the differential adjoint incoherent cross section (dc/dx)
/*! \details The returned cross section will have units of barns.
 */
double 
AdjointIncoherentCrossSectionEvaluator::evaluateDifferentialCrossSection(
	   const double inverse_energy_gain_ratio, 
	   const Utility::AdjointKleinNishinaDistribution& distribution ) const
{
  // Make sure the inverse energy gain ratio is valid
  testPrecondition( inverse_energy_gain_ratio >=
		    distribution.getLowerBoundOfIndepVar() );
  testPrecondition( inverse_energy_gain_ratio <=
		    distribution.getUpperBoundOfIndepVar() );
  // The inverse wavelength of the outgoing energy must be calculated
  const double outgoing_energy = 
    distribution.getEnergy()/inverse_energy_gain_ratio;
  
  const double inverse_wavelength = outgoing_energy/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);
  
  double scattering_angle_cosine = 
    1.0 - (1.0 - inverse_energy_gain_ratio)/distribution.getAlpha();
  
  // Check for roundoff error
  if( Teuchos::ScalarTraits<double>::magnitude(scattering_angle_cosine) >1.0 )
    scattering_angle_cosine = copysign( 1.0, scattering_angle_cosine );

  const double scattering_function_arg = 
    sqrt( (1.0 - scattering_angle_cosine)/2.0 )*inverse_wavelength;
  
  const double scattering_function_value = 
    d_scattering_function->evaluate( scattering_function_arg );
  
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  // Make sure the scattering function value is valid
  testPostcondition( scattering_function_value >= 0.0 );
  testPostcondition( scattering_function_value <= 100.0 );

  return distribution.evaluate( inverse_energy_gain_ratio )*
    scattering_function_value/1e-24;
}

// Return the cross section value at a given energy and max energy
/*! \details The returned cross section will have units of barns.
 */
double AdjointIncoherentCrossSectionEvaluator::evaluateCrossSection( 
						 const double energy, 
						 const double max_energy,
						 const double precision ) const
{
  // Make sure the energies are valid
  testPrecondition( energy > 0.0 );
  testPrecondition( energy <= max_energy );

  double cross_section = 0.0;

  if( energy < max_energy )
  {
    Utility::AdjointKleinNishinaDistribution distribution( energy, max_energy);

    boost::function<double (double x)> diff_adjoint_incoh_wrapper = 
      boost::bind<double>( &AdjointIncoherentCrossSectionEvaluator::evaluateDifferentialCrossSection,
			   boost::cref( *this ),
			   _1,
			   distribution );

    double abs_error;
    
    Utility::GaussKronrodQuadratureKernel quadrature_kernel( precision );

    quadrature_kernel.integrateAdaptively<15>(
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

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
