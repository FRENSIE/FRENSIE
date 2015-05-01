//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution ACE factory def.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_BasicDopplerBroadenedIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdvancedDopplerBroadenedIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_VoidComptonProfileSubshellConverter.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HydrogenFormFactorDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a basic incoherent distribution
void IncoherentPhotonScatteringDistributionACEFactory::createIncoherentDistribution( 
		    const Data::XSSEPRDataExtractor& raw_photoatom_data,
		    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    IncoherentPhotonScatteringDistribution::getMinKahnCutoffEnergy() );
  
  // Create the scattering function
  Teuchos::RCP<const Utility::OneDDistribution> scattering_function;

  createScatteringFunction( scattering_function );

  incoherent_distribution.reset( new IncoherentPhotonScatteringDistribution( 
					       scattering_function,
					       kahn_sampling_cutoff_energy ) );
}

// Create a basic Doppler broadened incoherent distribution
void IncoherentPhotonScatteringDistributionACEFactory::createBasicDopplerBroadenedIncoherentDistribution(
		    const Data::XSSEPRDataExtractor& raw_photoatom_data,
		    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    IncoherentPhotonScatteringDistribution::getMinKahnCutoffEnergy() );
  
  // Create the scattering function
  Teuchos::RCP<const Utility::OneDDistribution> scattering_function;

  createScatteringFunction( scattering_function );

  // Create the subshell order array
  Teuchos::ArrayView<const double> subshell_endf_designators = 
    raw_photoatom_data.extractSubshellENDFDesignators();
  
  Teuchos::Array<SubshellType> subshell_order(
					    subshell_endf_designators.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
  }
    
  // Create the Compton profile subshell converter
  Teuchos::RCP<ComptonProfileSubshellConverter> converter;
  
  ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );
  
  // Create the compton profile distributions
  Teuchos::ArrayView<const double> lswd_block = 
    raw_photoatom_data.extractLSWDBlock();
  
  Teuchos::ArrayView<const double> swd_block = 
    raw_photoatom_data.extractSWDBlock();
  
  Teuchos::Array<Teuchos::RCP<const Utility::TabularOneDDistribution> >
    compton_profiles( lswd_block.size() );
  
  for( unsigned subshell = 0; subshell < lswd_block.size(); ++subshell )
  {
    unsigned subshell_index = lswd_block[subshell]; 
    
    unsigned num_momentum_points = swd_block[subshell_index];
    
    Teuchos::Array<double> half_momentum_grid( 
			swd_block( subshell_index + 1, num_momentum_points ) );

    Teuchos::Array<double> half_profile(
                           swd_block( subshell_index + 1 + num_momentum_points,
				      num_momentum_points ) );

    MonteCarlo::convertMomentumGridToMeCUnits( half_momentum_grid.begin(),
					       half_momentum_grid.end() );
    
    MonteCarlo::convertProfileToInverseMeCUnits( half_profile.begin(),
						 half_profile.end() );
    
    // Ignore interp parameter (always assume log-lin inerpolation)
    compton_profiles[subshell].reset(
	 new Utility::TabularDistribution<Utility::LogLin>( half_momentum_grid,
							    half_profile ) );
  }

  incoherent_distribution.reset( 
	      new BasicDopplerBroadenedIncoherentPhotonScatteringDistribution( 
			   scattering_function,
			   raw_photoatom_data.extractSubshellBindingEnergies(),
			   raw_photoatom_data.extractSubshellOccupancies(),
			   subshell_order,
			   converter,
			   compton_profiles,
			   kahn_sampling_cutoff_energy ) );
}

// Create an advanced Doppler broadened incoherent distribution
void IncoherentPhotonScatteringDistributionACEFactory::createAdvancedDopplerBroadenedIncoherentDistribution(
		    const Data::XSSEPRDataExtractor& raw_photoatom_data,
		    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    IncoherentPhotonScatteringDistribution::getMinKahnCutoffEnergy() );
  
  // Create the scattering function
  Teuchos::RCP<const Utility::OneDDistribution> scattering_function;

  createScatteringFunction( scattering_function );

  // Create the subshell order array
  Teuchos::ArrayView<const double> subshell_endf_designators = 
    raw_photoatom_data.extractSubshellENDFDesignators();
  
  Teuchos::Array<SubshellType> subshell_order(
					    subshell_endf_designators.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
  }
    
  // Create the Compton profile subshell converter
  Teuchos::RCP<ComptonProfileSubshellConverter> converter;
  
  ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );
  
  // Create the compton profile distributions
  Teuchos::ArrayView<const double> lswd_block = 
    raw_photoatom_data.extractLSWDBlock();
  
  Teuchos::ArrayView<const double> swd_block = 
    raw_photoatom_data.extractSWDBlock();
  
  Teuchos::Array<Teuchos::RCP<const Utility::TabularOneDDistribution> >
    compton_profiles( lswd_block.size() );
  
  for( unsigned subshell = 0; subshell < lswd_block.size(); ++subshell )
  {
    unsigned subshell_index = lswd_block[subshell]; 
    
    unsigned num_momentum_points = swd_block[subshell_index];
    
    Teuchos::Array<double> half_momentum_grid( 
			swd_block( subshell_index + 1, num_momentum_points ) );

    Teuchos::Array<double> half_profile(
                           swd_block( subshell_index + 1 + num_momentum_points,
				      num_momentum_points ) );

    Teuchos::Array<double> full_momentum_grid, full_profile;

    MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						  half_momentum_grid.end(),
						  half_profile.begin(),
						  half_profile.end(),
						  full_momentum_grid,
						  full_profile );

    MonteCarlo::convertMomentumGridToMeCUnits( full_momentum_grid.begin(),
					       full_momentum_grid.end() );
    
    MonteCarlo::convertProfileToInverseMeCUnits( full_profile.begin(),
						 full_profile.end() );
    
    // Ignore interp parameter (always assume log-lin inerpolation)
    compton_profiles[subshell].reset(
	 new Utility::TabularDistribution<Utility::LogLin>( full_momentum_grid,
							    full_profile ) );
  }

  incoherent_distribution.reset( 
	   new AdvancedDopplerBroadenedIncoherentPhotonScatteringDistribution( 
			   scattering_function,
			   raw_photoatom_data.extractSubshellBindingEnergies(),
			   raw_photoatom_data.extractSubshellOccupancies(),
			   subshell_order,
			   converter,
			   compton_profiles,
			   kahn_sampling_cutoff_energy ) );
}

// Create the scattering function
void IncoherentPhotonScatteringDistributionACEFactory::createScatteringFunction( 
	  const Data::XSSEPRDataExtractor& raw_photoatom_data,
	  Teuchos::RCP<const Utility::OneDDistribution>& scattering_function )
{
  if( raw_photoatom_data.extractAtomicNumber() != 1 )
  {
    Teuchos::ArrayView<const double> jince_block = 
      raw_photoatom_data.extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;

    Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ));
  
    // The stored recoil momemtum has units of inverse Angstroms - convert to
    // inverse cm
    for( unsigned i = 0; i < scatt_func_size; ++i )
      recoil_momentum[i] *= 1e8;

    // Log-Log interpolation is required but first recoil momentum may be 0.0
    if( recoil_momentum.front() == 0.0 )
      recoil_momentum.front() = std::numeric_limits<double>::min();
    
    Teuchos::Array<double> scattering_function_values( 
			     jince_block( scatt_func_size, scatt_func_size ) );

    // Log-Log interpolation is required but first value may be 0.0
    if( scattering_function_values.front() == 0.0 )
      scattering_function_values.front() = std::numeric_limits<double>::min();

    scattering_function.reset(
		     new Utility::TabularDistribution<Utility::LogLog>(
						recoil_momentum,
						scattering_function_values ) );
  }
  else // Hydrogen - use analytic scattering function
    scattering_function.reset( new Utility::HydrogenFormFactorDistribution() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

