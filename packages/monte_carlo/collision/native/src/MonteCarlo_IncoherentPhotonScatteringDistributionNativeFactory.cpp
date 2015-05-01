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
#include "MonteCarlo_BasicDopplerBroadenedIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdvancedDopplerBroadenedIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_VoidComptonProfileSubshellConverter.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HydrogenFormFactorDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a basic incoherent distribution
void IncoherentPhotonScatteringDistributionNativeFactory::createIncoherentDistribution( 
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
	 incoherent_distribution,
	 const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    IncoherentPhotonScatteringDistribution::getMinKahnCutoffEnergy() );
  
  // Create the scattering function
  Teuchos::RCP<const Utility::OneDDistribution> scattering_function;

  IncoherentPhotonScatteringDistributionNativeFactory::createScatteringFunction(
							 raw_photoatom_data,
							 scattering_function );

  incoherent_distribution.reset( new IncoherentPhotonScatteringDistribution( 
					       scattering_function,
					       kahn_sampling_cutoff_energy ) );
}

// Create an advanced Doppler broadened incoherent distribution
void IncoherentPhotonScatteringDistributionNativeFactory::createAdvancedDopplerBroadenedIncoherentDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
	 incoherent_distribution,
	 const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    IncoherentPhotonScatteringDistribution::getMinKahnCutoffEnergy() );
  
  // Create the scattering function
  Teuchos::RCP<const Utility::OneDDistribution> scattering_function;

  IncoherentPhotonScatteringDistributionNativeFactory::createScatteringFunction( 
							 raw_photoatom_data,
							 scattering_function );

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

  incoherent_distribution.reset( 
	   new AdvancedDopplerBroadenedIncoherentPhotonScatteringDistribution( 
			   scattering_function,
			   subshell_binding_energies,
			   subshell_occupancies,
			   subshell_order,
			   converter,
			   compton_profiles,
			   kahn_sampling_cutoff_energy ) );
}

// Create the scattering function
void IncoherentPhotonScatteringDistributionNativeFactory::createScatteringFunction( 
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const Utility::OneDDistribution>& scattering_function )
{
  if( raw_photoatom_data.getAtomicNumber() != 1 )
  {
    scattering_function.reset(
       new Utility::TabularDistribution<Utility::LinLin>(
	   raw_photoatom_data.getWallerHartreeScatteringFunctionMomentumGrid(),
	   raw_photoatom_data.getWallerHartreeScatteringFunction() ) );
  }
  else
    scattering_function.reset( new Utility::HydrogenFormFactorDistribution() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
