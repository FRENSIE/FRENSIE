//---------------------------------------------------------------------------//
//!
//! \file  MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The Doppler broadened photon energy dist. native factory def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.hpp"
#include "MonteCarlo_CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ComptonProfilePolicy.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_BasicComptonProfileSubshellConverter.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a coupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionNativeFactory::createCoupledCompleteDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
	 doppler_broadened_dist )
{
  // Extract the binding energies, occupancies and order
  std::vector<double> subshell_binding_energies, subshell_occupancies;
  std::vector<Data::SubshellType> subshell_order;

  std::set<unsigned>::const_iterator subshell_it =
    raw_photoatom_data.getSubshells().begin();

  while( subshell_it != raw_photoatom_data.getSubshells().end() )
  {
    subshell_order.push_back(
		   Data::convertENDFDesignatorToSubshellEnum( *subshell_it ) );

    subshell_binding_energies.push_back(
		 raw_photoatom_data.getSubshellBindingEnergy( *subshell_it ) );

    subshell_occupancies.push_back(
		     raw_photoatom_data.getSubshellOccupancy( *subshell_it ) );

    ++subshell_it;
  }

  // Create the Compton profile subshell converter
  std::shared_ptr<ComptonProfileSubshellConverter> converter =
    std::make_shared<BasicComptonProfileSubshellConverter>( subshell_order );

  // Create the compton profile distributions
  CompleteDopplerBroadenedPhotonEnergyDistribution::ComptonProfileArray
    compton_profiles( subshell_order.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum> > raw_compton_profile(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
      raw_photoatom_data.getComptonProfileMomentumGrid(subshell_order[i]),
      raw_photoatom_data.getComptonProfile(subshell_order[i]) ) );

    compton_profiles[i].reset(
                      new StandardComptonProfile<Utility::Units::MeCMomentum>(
                                                       raw_compton_profile ) );

  }

  doppler_broadened_dist.reset(
     new CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy>(
						subshell_binding_energies,
						subshell_occupancies,
						subshell_order,
						converter,
						compton_profiles ) );
}

// Create a coupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionNativeFactory::createCoupledCompleteDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
	 doppler_broadened_dist )
{
  std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution> dist;

  DopplerBroadenedPhotonEnergyDistributionNativeFactory::createCoupledCompleteDistribution(
							    raw_photoatom_data,
							    dist );

  doppler_broadened_dist =
    std::dynamic_pointer_cast<const CompleteDopplerBroadenedPhotonEnergyDistribution>( dist );
}

// Create a subshell Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionNativeFactory::createSubshellDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const unsigned endf_subshell,
	 std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
	 doppler_broadened_dist )
{
  // Convert the endf subshell to a subshell type
  Data::SubshellType subshell =Data::convertENDFDesignatorToSubshellEnum( endf_subshell );

  TEST_FOR_EXCEPTION( subshell == Data::INVALID_SUBSHELL,
		      std::logic_error,
		      "the requested endf subshell " <<
		      endf_subshell << " is invalid! " );

  // Create the Compton profile
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum> > raw_compton_profile(
      new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
	     raw_photoatom_data.getComptonProfileMomentumGrid( endf_subshell ),
	     raw_photoatom_data.getComptonProfile( endf_subshell ) ) );

  std::shared_ptr<ComptonProfile> compton_profile(
                      new StandardComptonProfile<Utility::Units::MeCMomentum>(
                                                       raw_compton_profile ) );

  doppler_broadened_dist.reset(
    new StandardSubshellDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy>(
		  subshell,
		  raw_photoatom_data.getSubshellOccupancy( endf_subshell ),
		  raw_photoatom_data.getSubshellBindingEnergy( endf_subshell ),
		  compton_profile ) );
}

// Create a subshell Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionNativeFactory::createSubshellDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const unsigned endf_subshell,
	 std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution>&
	 doppler_broadened_dist )
{
  std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution> dist;

  DopplerBroadenedPhotonEnergyDistributionNativeFactory::createSubshellDistribution(
							    raw_photoatom_data,
							    endf_subshell,
							    dist );

  doppler_broadened_dist =
    std::dynamic_pointer_cast<const SubshellDopplerBroadenedPhotonEnergyDistribution>( dist );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
