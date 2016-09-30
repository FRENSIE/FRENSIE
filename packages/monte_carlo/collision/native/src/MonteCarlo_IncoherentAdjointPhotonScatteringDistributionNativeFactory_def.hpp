//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory_def.hpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution native
//!         factory class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a subshell incoherent adjoint distribution
template<typename BaseDistributionType>
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
                      const Data::AdjointElectronPhotonRelaxationDataContainer&
                      raw_adjoint_photoatom_data,
                      const unsigned endf_subshell,
                      const double max_energy,
                      std::shared_ptr<BaseDistributionType>&
                      incoherent_adjoint_distribution )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy <= SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy() );
  testPrecondition( max_energy > SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy() );

  // Convert the endf subshell to a subshell type
  Data::SubshellType subshell =
    Data::convertENDFDesignatorToSubshellEnum( endf_subshell );

  TEST_FOR_EXCEPTION( subshell == Data::INVALID_SUBSHELL,
                      std::logic_error,
                      "Error: the requested endf subshell " << endf_subshell <<
                      " is invalid!" );

  // Create the occupation number
  std::shared_ptr<const OccupationNumber> occupation_number;

  ThisType::createOccupationNumber( raw_adjoint_photoatom_data,
                                    endf_subshell,
                                    occupation_number );

  // Create the distribution
  incoherent_adjoint_distribution.reset(
     new SubshellIncoherentAdjointPhotonScatteringDistribution(
          max_energy,
          subshell,
          raw_adjoint_photoatom_data.getSubshellOccupancy( endf_subshell ),
          raw_adjoint_photoatom_data.getSubshellBindingEnergy( endf_subshell ),
          occupation_number ) );                 
}

// Create a Doppler broadened subshell incoherent adjoint distribution
template<typename BaseDistributionType>
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDopplerBroadenedSubshellDistribution(
                      const Data::AdjointElectronPhotonRelaxationDataContainer&
                      raw_adjoint_photoatom_data,
                      const unsigned endf_subshell,
                      const double max_energy,
                      std::shared_ptr<BaseDistributionType>&
                      incoherent_adjoint_distribution )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy <= SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy() );
  testPrecondition( max_energy > SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy() );

  // Convert the endf subshell to a subshell type
  Data::SubshellType subshell =
    Data::convertENDFDesignatorToSubshellEnum( endf_subshell );

  TEST_FOR_EXCEPTION( subshell == Data::INVALID_SUBSHELL,
                      std::logic_error,
                      "Error: the requested endf subshell " << endf_subshell <<
                      " is invalid!" );

  // Create the occupation number
  std::shared_ptr<const OccupationNumber> occupation_number;

  ThisType::createOccupationNumber( raw_adjoint_photoatom_data,
                                    endf_subshell,
                                    occupation_number );

  // Create the Compton profile
  std::shared_ptr<const ComptonProfile> compton_profile;

  ThisType::createComptonProfile( raw_adjoint_photoatom_data,
                                  endf_subshell,
                                  compton_profile );

  // Create the distribution
  incoherent_adjoint_distribution.reset(
     new DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution(
          max_energy,
          subshell,
          raw_adjoint_photoatom_data.getSubshellOccupancy( endf_subshell ),
          raw_adjoint_photoatom_data.getSubshellBindingEnergy( endf_subshell ),
          occupation_number,
          compton_profile ) );                 
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//
