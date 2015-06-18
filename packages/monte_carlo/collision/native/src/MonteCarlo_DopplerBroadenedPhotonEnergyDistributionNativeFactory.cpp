//---------------------------------------------------------------------------//
//!
//! \file  MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The Doppler broadened photon energy dist. native factory def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.hpp"
#include "MonteCarlo_CoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_VoidComptonProfileSubshellConverter.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a coupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionNativeFactory::createCoupledCompleteDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const DopplerBroadenedPhotonEnergyDistribution>&
	 doppler_broadened_dist )
{
  // Extract the binding energies, occupancies and order
  Teuchos::Array<double> subshell_binding_energies, subshell_occupancies;
  Teuchos::Array<SubshellType> subshell_order;

  std::set<unsigned>::const_iterator subshell_it = 
    raw_photoatom_data.getSubshells().begin();

  while( subshell_it != raw_photoatom_data.getSubshells().end() )
  {
    subshell_order.push_back( 
			 convertENDFDesignatorToSubshellEnum( *subshell_it ) );

    subshell_binding_energies.push_back( 
		 raw_photoatom_data.getSubshellBindingEnergy( *subshell_it ) );

    subshell_occupancies.push_back(
		     raw_photoatom_data.getSubshellOccupancy( *subshell_it ) );

    ++subshell_it;
  }

  // Create the Compton profile subshell converter
  Teuchos::RCP<ComptonProfileSubshellConverter> converter(
				   new VoidComptonProfileSubshellConverter() );

  // Create the compton profile distributions
  Teuchos::Array<Teuchos::RCP<const Utility::TabularOneDDistribution> >
    compton_profiles( subshell_order.size() );

  Teuchos::Array<SubshellType> subshell_order_copy = subshell_order;
  std::sort( subshell_order_copy.begin(), subshell_order_copy.end() );

  for( unsigned i = 0; i < subshell_order_copy.size(); ++i )
  {
    compton_profiles[i].reset(
      new Utility::TabularDistribution<Utility::LinLin>(
      raw_photoatom_data.getComptonProfileMomentumGrid(subshell_order_copy[i]),
      raw_photoatom_data.getComptonProfile( subshell_order_copy[i] ) ) );
  }

  doppler_broadened_dist.reset( 
		   new CoupledCompleteDopplerBroadenedPhotonEnergyDistribution(
						subshell_binding_energies, 
						subshell_occupancies,
						subshell_order,
						converter,
						compton_profiles ) );
}

// Create a coupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionNativeFactory::createCoupledCompleteDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
	 doppler_broadened_dist )
{
  Teuchos::RCP<const DopplerBroadenedPhotonEnergyDistribution> dist;

  DopplerBroadenedPhotonEnergyDistributionNativeFactory::createCoupledCompleteDistribution( 
							    raw_photoatom_data,
							    dist );

  doppler_broadened_dist = 
    Teuchos::rcp_dynamic_cast<const CompleteDopplerBroadenedPhotonEnergyDistribution>( dist );
}
  
// Create a subshell Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionNativeFactory::createSubshellDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const unsigned endf_subshell,
	 Teuchos::RCP<const DopplerBroadenedPhotonEnergyDistribution>&
	 doppler_broadened_dist )
{
  // Convert the endf subshell to a subshell type
  SubshellType subshell = convertENDFDesignatorToSubshellEnum( endf_subshell );
  
  TEST_FOR_EXCEPTION( subshell == INVALID_SUBSHELL,
		      std::logic_error,
		      "Error: the requested endf subshell " << 
		      endf_subshell << " is invalid! " );

  // Create the Compton profile
  Teuchos::RCP<Utility::TabularOneDDistribution> compton_profile(
       new Utility::TabularDistribution<Utility::LinLin>(
	     raw_photoatom_data.getComptonProfileMomentumGrid( endf_subshell ),
	     raw_photoatom_data.getComptonProfile( endf_subshell ) ) );

  doppler_broadened_dist.reset(
	    new SubshellDopplerBroadenedPhotonEnergyDistribution(
		  subshell,
		  raw_photoatom_data.getSubshellOccupancy( endf_subshell ),
		  raw_photoatom_data.getSubshellBindingEnergy( endf_subshell ),
		  compton_profile ) );
}

// Create a subshell Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionNativeFactory::createSubshellDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const unsigned endf_subshell,
	 Teuchos::RCP<const SubshellDopplerBroadenedPhotonEnergyDistribution>&
	 doppler_broadened_dist )
{
  Teuchos::RCP<const DopplerBroadenedPhotonEnergyDistribution> dist;

  DopplerBroadenedPhotonEnergyDistributionNativeFactory::createSubshellDistribution( 
							    raw_photoatom_data,
							    endf_subshell,
							    dist );

  doppler_broadened_dist = 
    Teuchos::rcp_dynamic_cast<const SubshellDopplerBroadenedPhotonEnergyDistribution>( dist );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
