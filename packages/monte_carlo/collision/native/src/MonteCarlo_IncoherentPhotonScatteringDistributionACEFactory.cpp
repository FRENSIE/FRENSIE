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
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedHybridIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the requested incoherent distribution
void IncoherentPhotonScatteringDistributionACEFactory::createDistribution(
		    const Data::XSSEPRDataExtractor& raw_photoatom_data,
		    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const IncoherentModelType incoherent_model,
		    const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );

  switch( incoherent_model )
  {
    case KN_INCOHERENT_MODEL:
    {
      IncoherentPhotonScatteringDistributionACEFactory::createKleinNishinaDistribution( 
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    case WH_INCOHERENT_MODEL:
    {
      IncoherentPhotonScatteringDistributionACEFactory::createWallerHartreeDistribution(
						 raw_photoatom_data,
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    case DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    {
      Teuchos::RCP<const CompleteDopplerBroadenedPhotonEnergyDistribution>
	doppler_broadened_dist;
      
      DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution(
							raw_photoatom_data,
							doppler_broadened_dist,
							false );
      
      IncoherentPhotonScatteringDistributionACEFactory::createDopplerBroadenedHybridDistribution(
						 raw_photoatom_data,
						 doppler_broadened_dist,
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    case DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    {
      Teuchos::RCP<const CompleteDopplerBroadenedPhotonEnergyDistribution>
	doppler_broadened_dist;
      
      DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution(
							raw_photoatom_data,
							doppler_broadened_dist,
							true );
      
      IncoherentPhotonScatteringDistributionACEFactory::createDopplerBroadenedHybridDistribution(
						 raw_photoatom_data,
						 doppler_broadened_dist,
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    case COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    {
      Teuchos::RCP<const CompleteDopplerBroadenedPhotonEnergyDistribution>
	doppler_broadened_dist;
      
      DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution(
							raw_photoatom_data,
							doppler_broadened_dist,
							false );
      
      IncoherentPhotonScatteringDistributionACEFactory::createDopplerBroadenedHybridDistribution(
						 raw_photoatom_data,
						 doppler_broadened_dist,
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    case COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    {
      Teuchos::RCP<const CompleteDopplerBroadenedPhotonEnergyDistribution>
	doppler_broadened_dist;
      
      DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution(
							raw_photoatom_data,
							doppler_broadened_dist,
							true );
      
      IncoherentPhotonScatteringDistributionACEFactory::createDopplerBroadenedHybridDistribution(
						 raw_photoatom_data,
						 doppler_broadened_dist,
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    default:
    {
      THROW_EXCEPTION( std::logic_error,
		       "Error: incoherent model " << incoherent_model <<
		       " cannot be constructed with ACE data!" );
    }
  }
}

// Create a Waller-Hartree incoherent distribution
void IncoherentPhotonScatteringDistributionACEFactory::createWallerHartreeDistribution( 
		    const Data::XSSEPRDataExtractor& raw_photoatom_data,
		    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );
  
  // Create the scattering function
  Teuchos::RCP<const Utility::OneDDistribution> scattering_function;

  IncoherentPhotonScatteringDistributionACEFactory::createScatteringFunction( 
							 raw_photoatom_data,
							 scattering_function );

  // Create the subshell order array
  Teuchos::Array<SubshellType> subshell_order;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellOrderArray(
							    raw_photoatom_data,
							    subshell_order );

  incoherent_distribution.reset( 
			 new DetailedWHIncoherentPhotonScatteringDistribution( 
			   scattering_function,
			   raw_photoatom_data.extractSubshellOccupancies(),
			   subshell_order,
			   kahn_sampling_cutoff_energy ) );
}

// Create a Doppler broadened hybrid incoherent distribution
void IncoherentPhotonScatteringDistributionACEFactory::createDopplerBroadenedHybridDistribution(
    const Data::XSSEPRDataExtractor& raw_photoatom_data,
    const Teuchos::RCP<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
    doppler_broadened_dist,
    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
    incoherent_distribution,     
    const double kahn_sampling_cutoff_energy )
{
  // Make sure the Doppler broadened distribution is valid
  testPrecondition( !doppler_broadened_dist.is_null() );
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );
  
  // Create the scattering function
  Teuchos::RCP<const Utility::OneDDistribution> scattering_function;

  IncoherentPhotonScatteringDistributionACEFactory::createScatteringFunction( 
							 raw_photoatom_data,
							 scattering_function );

  incoherent_distribution.reset(
	      new DopplerBroadenedHybridIncoherentPhotonScatteringDistribution(
					       scattering_function,
					       doppler_broadened_dist,
					       kahn_sampling_cutoff_energy ) );
}	

// Create the scattering function
void IncoherentPhotonScatteringDistributionACEFactory::createScatteringFunction( 
	  const Data::XSSEPRDataExtractor& raw_photoatom_data,
	  Teuchos::RCP<const Utility::OneDDistribution>& scattering_function )
{
  Teuchos::ArrayView<const double> jince_block = 
    raw_photoatom_data.extractJINCEBlock();
  
  unsigned scatt_func_size = jince_block.size()/2;
  
  Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ));
  
  // The stored recoil momemtum has units of inverse Angstroms - convert to
  // inverse cm
  for( unsigned i = 0; i < scatt_func_size; ++i )
    recoil_momentum[i] *= 1e8;
  
  Teuchos::Array<double> scattering_function_values( 
			     jince_block( scatt_func_size, scatt_func_size ) );
  
  scattering_function.reset(
		     new Utility::TabularDistribution<Utility::LinLin>(
						recoil_momentum,
						scattering_function_values ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

