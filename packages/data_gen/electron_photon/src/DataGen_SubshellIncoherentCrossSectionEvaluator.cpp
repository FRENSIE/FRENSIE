//---------------------------------------------------------------------------//
//!
//! \file   DataGen_SubshellIncoherentCrossSectionEvaluator.cpp
//! \author Alex Robinson
//! \brief  Subshell incoherent cross section evaluator definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "DataGen_SubshellIncoherentCrossSectionEvaluator.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor (bound electron)
SubshellIncoherentCrossSectionEvaluator::SubshellIncoherentCrossSectionEvaluator(
			   const MonteCarlo::SubshellType subshell,
			   const double num_electrons_in_subshell,
			   const double subshell_binding_energy,
                           const Teuchos::RCP<const Utility::OneDDistribution>&
			   subshell_occupation_number )
  : d_subshell( subshell ),
    d_num_electrons_in_subshell( num_electrons_in_subshell ),
    d_subshell_binding_energy( subshell_binding_energy ),
    d_subshell_occupation_number( subshell_occupation_number )
{
  // Make sure the subshell is valid
  testPrecondition( subshell != MonteCarlo::INVALID_SUBSHELL );
  testPrecondition( subshell != MonteCarlo::UNKNOWN_SUBSHELL );
  // Make sure the number of electrons in the subshell is valid
  testPrecondition( num_electrons_in_subshell > 0.0 );
  // Make sure the subshell binding energy is valid
  testPrecondition( subshell_binding_energy > 0.0 );
  // Make sure the occupation number distribution is valid
  testPrecondition( !subshell_occupation_number.is_null() );
}

// Return the subshell
MonteCarlo::SubshellType 
SubshellIncoherentCrossSectionEvaluator::getSubshell() const
{
  return d_subshell;
}

// Return the number of electrons that occupy the subshell
double 
SubshellIncoherentCrossSectionEvaluator::getNumberOfElectronsInSubshell() const
{
  return d_num_electrons_in_subshell;
}

// Return the binding energy of the subshell
double 
SubshellIncoherentCrossSectionEvaluator::getSubshellBindingEnergy() const
{
  return d_subshell_binding_energy;
}

// Return the maximum electron momentum projection
/*! \details The returned max electron momentum projection is in units of
 * me*c.
 */
double SubshellIncoherentCrossSectionEvaluator::getMaxElectronMomentumProjection(
					      const double energy,
					      const double angle_cosine ) const
{
  // Make sure the energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( energy ) );
  testPrecondition( energy >= d_subshell_binding_energy );
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine >= -1.0 );
  testPrecondition( angle_cosine <= 1.0 );

  double energy_diff = energy - d_subshell_binding_energy;

  double max_electron_momentum_projection = (-d_subshell_binding_energy + 
	  energy*energy_diff*(1.0-angle_cosine)/
	  Utility::PhysicalConstants::electron_rest_mass_energy)/
    sqrt( energy*energy + energy_diff*energy_diff - 
	  2*energy*energy_diff*angle_cosine );

  // Make sure the projection is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( 
					  max_electron_momentum_projection ) );

  return max_electron_momentum_projection;
}

// Evaluate the differential subshell incoherent cross section (dc/dx) 
/*! \details The differential cross section is in units of barns
 */
double 
SubshellIncoherentCrossSectionEvaluator::evaluateDifferentialCrossSection(
		 const double inverse_energy_loss_ratio,
		 const Utility::KleinNishinaDistribution& distribution ) const
{
  // Make sure the inverse energy loss ratio is valid
  testPrecondition( inverse_energy_loss_ratio >=
		    distribution.getLowerBoundOfIndepVar() );
  testPrecondition( inverse_energy_loss_ratio <=
		    distribution.getUpperBoundOfIndepVar() );

  // The max electron momentum projection must be calculated
  double scattering_angle_cosine = 1.0 - (inverse_energy_loss_ratio-1.0)/
    distribution.getAlpha();
  
  // Check for roundoff error
  if( Teuchos::ScalarTraits<double>::magnitude(scattering_angle_cosine) >1.0 )
    scattering_angle_cosine = copysign( 1.0, scattering_angle_cosine );

  double max_electron_momentum_projection = 
    this->getMaxElectronMomentumProjection( distribution.getEnergy(),
					    scattering_angle_cosine );
  
  // If the max projection is beyond the table max - use the table max
  // This should be okay since the Compton profiles drop off rapidly
  if( max_electron_momentum_projection > 
      d_subshell_occupation_number->getUpperBoundOfIndepVar() )
  {
    max_electron_momentum_projection = 
      d_subshell_occupation_number->getUpperBoundOfIndepVar();
  }
  
  const double occupation_number = 
    d_subshell_occupation_number->evaluate( max_electron_momentum_projection );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  // Make sure the occupation number is valid
  testPostcondition( occupation_number >= 0.0 );
  testPostcondition( occupation_number <= 1.0 );

  return distribution.evaluate( inverse_energy_loss_ratio )*
    occupation_number*d_num_electrons_in_subshell/1e-24;
}

// Evaluate the subshell incoherent cross section
/*! \details The cross section is in units of barns.
 */ 
double 
SubshellIncoherentCrossSectionEvaluator::evaluateCrossSection( 
					         const double energy,
					         const double precision ) const
{
  // Make sure the energy is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( energy ) );

  double cross_section = 0.0;

  if( energy > d_subshell_binding_energy )
  {
    Utility::KleinNishinaDistribution distribution( energy );

    boost::function<double (double x)> diff_cs_wrapper = 
      boost::bind<double>( &SubshellIncoherentCrossSectionEvaluator::evaluateDifferentialCrossSection,
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
  }
  else
    cross_section = 0.0;

  return cross_section;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_SubshellIncoherentCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
