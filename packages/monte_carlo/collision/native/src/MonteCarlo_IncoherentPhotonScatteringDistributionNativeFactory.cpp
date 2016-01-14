//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution native factor def.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.hpp"
#include "MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedHybridIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_VoidComptonProfileSubshellConverter.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create an incoherent distribution
void IncoherentPhotonScatteringDistributionNativeFactory::createDistribution( 
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
	 incoherent_distribution,
	 const IncoherentModelType incoherent_model,
	 const double kahn_sampling_cutoff_energy,
	 const unsigned endf_subshell )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );
  
  switch( incoherent_model )
  {
    case KN_INCOHERENT_MODEL:
    {
      IncoherentPhotonScatteringDistributionNativeFactory::createKleinNishinaDistribution( 
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    case WH_INCOHERENT_MODEL:
    {
      IncoherentPhotonScatteringDistributionNativeFactory::createWallerHartreeDistribution(
						 raw_photoatom_data,
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    case COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL:
    {
      std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>
	doppler_broadened_dist;
      
      MonteCarlo::DopplerBroadenedPhotonEnergyDistributionNativeFactory::createCoupledCompleteDistribution(
					              raw_photoatom_data,
						      doppler_broadened_dist );

      MonteCarlo::IncoherentPhotonScatteringDistributionNativeFactory::createDopplerBroadenedHybridDistribution(
						 raw_photoatom_data,
						 doppler_broadened_dist,
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    case IMPULSE_INCOHERENT_MODEL:
    {
      IncoherentPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
						 raw_photoatom_data,
						 endf_subshell,
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    case FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL:
    {
      std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution>
	doppler_broadened_dist;
      
      MonteCarlo::DopplerBroadenedPhotonEnergyDistributionNativeFactory::createSubshellDistribution(
					              raw_photoatom_data,
						      endf_subshell,
						      doppler_broadened_dist );

      IncoherentPhotonScatteringDistributionNativeFactory::createDopplerBroadenedSubshellDistribution(
					         raw_photoatom_data,
						 endf_subshell,
						 doppler_broadened_dist,
						 incoherent_distribution,
						 kahn_sampling_cutoff_energy );
      break;
    }
    default:
    {
      THROW_EXCEPTION( std::logic_error,
		       "Error: incoherent model " << incoherent_model <<
		       " cannot be constructed with native data!" );
    }
  }
}

// Create a Waller-Hartree incoherent distribution
void IncoherentPhotonScatteringDistributionNativeFactory::createWallerHartreeDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
	 incoherent_distribution,
	 const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );
  
  // Create the scattering function
  std::shared_ptr<const ScatteringFunction> scattering_function;

  IncoherentPhotonScatteringDistributionNativeFactory::createScatteringFunction(
							 raw_photoatom_data,
							 scattering_function );

  // Create the subshell binding energy, occupancy and order arrays
  const std::set<unsigned>& subshells = raw_photoatom_data.getSubshells();

  std::set<unsigned>::const_iterator subshell_it = subshells.begin();

  Teuchos::Array<double> occupancy_numbers;

  Teuchos::Array<SubshellType> subshell_order;
  
  while( subshell_it != subshells.end() )
  {
    occupancy_numbers.push_back(
		     raw_photoatom_data.getSubshellOccupancy( *subshell_it ) );

    subshell_order.push_back( 
			 convertENDFDesignatorToSubshellEnum( *subshell_it ) );
    
    ++subshell_it;
  }

  incoherent_distribution.reset( 
			 new DetailedWHIncoherentPhotonScatteringDistribution( 
					       scattering_function,
					       occupancy_numbers,
					       subshell_order,
					       kahn_sampling_cutoff_energy ) );
}

// Create a Doppler broadened hybrid incoherent distribution
void IncoherentPhotonScatteringDistributionNativeFactory::createDopplerBroadenedHybridDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
    const std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
    doppler_broadened_dist,
    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
    incoherent_distribution,     
    const double kahn_sampling_cutoff_energy )
{
  // Make sure the Doppler broadened distribution is valid
  testPrecondition( doppler_broadened_dist.get() );
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );

  // Create the scattering function
  std::shared_ptr<const ScatteringFunction> scattering_function;

  IncoherentPhotonScatteringDistributionNativeFactory::createScatteringFunction(
							 raw_photoatom_data,
							 scattering_function );

  incoherent_distribution.reset(
	      new DopplerBroadenedHybridIncoherentPhotonScatteringDistribution(
					       scattering_function,
					       doppler_broadened_dist,
					       kahn_sampling_cutoff_energy ) );
}
  

// Create a basic subshell incoherent distribution
void IncoherentPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const unsigned endf_subshell,
	 Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
	 incoherent_distribution,
	 const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );

  // Convert the endf subshell to a subshell type
  SubshellType subshell = convertENDFDesignatorToSubshellEnum( endf_subshell );
  
  TEST_FOR_EXCEPTION( subshell == INVALID_SUBSHELL,
		      std::logic_error,
		      "Error: the requested endf subshell " << 
		      endf_subshell << " is invalid! " );
  
  // Create the occupation number distribution
  Teuchos::RCP<Utility::OneDDistribution> occupation_number(
     new Utility::TabularDistribution<Utility::LinLin>( 
	   raw_photoatom_data.getOccupationNumberMomentumGrid( endf_subshell ),
	   raw_photoatom_data.getOccupationNumber( endf_subshell ) ) );

  incoherent_distribution.reset( 
	   new SubshellIncoherentPhotonScatteringDistribution(
		  subshell,
		  raw_photoatom_data.getSubshellOccupancy( endf_subshell ),
		  raw_photoatom_data.getSubshellBindingEnergy( endf_subshell ),
		  occupation_number,
		  kahn_sampling_cutoff_energy ) );
 }

// Create a Doppler broadened subshell incoherent distribution
void IncoherentPhotonScatteringDistributionNativeFactory::createDopplerBroadenedSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
    const unsigned endf_subshell,
    const std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution>&
    doppler_broadened_dist,
    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
    incoherent_distribution,
    const double kahn_sampling_cutoff_energy )
{
  // Make sure the Doppler broadened energy distribution is valid
  testPrecondition( doppler_broadened_dist.get() );
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );

  // Convert the endf subshell to a subshell type
  SubshellType subshell = convertENDFDesignatorToSubshellEnum( endf_subshell );
  
  TEST_FOR_EXCEPTION( subshell == INVALID_SUBSHELL,
		      std::logic_error,
		      "Error: the requested endf subshell " << 
		      endf_subshell << " is invalid! " );
  
  // Create the occupation number distribution
  Teuchos::RCP<Utility::OneDDistribution> occupation_number(
     new Utility::TabularDistribution<Utility::LinLin>( 
	   raw_photoatom_data.getOccupationNumberMomentumGrid( endf_subshell ),
	   raw_photoatom_data.getOccupationNumber( endf_subshell ) ) );

  incoherent_distribution.reset( 
	    new DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution(
		  doppler_broadened_dist,
		  occupation_number, 
		  kahn_sampling_cutoff_energy ) );
}

// Create the scattering function
void IncoherentPhotonScatteringDistributionNativeFactory::createScatteringFunction( 
	const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	std::shared_ptr<const ScatteringFunction>& scattering_function )
{
  std::shared_ptr<Utility::UnitAwareOneDDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
     new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseCentimeter,void>( 
	   raw_photoatom_data.getWallerHartreeScatteringFunctionMomentumGrid(),
	   raw_photoatom_data.getWallerHartreeScatteringFunction() ) );

  scattering_function.reset(
	     new StandardScatteringFunction<Utility::Units::InverseCentimeter>(
						   raw_scattering_function ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
