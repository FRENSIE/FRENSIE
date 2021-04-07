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
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create an incoherent adjoint distribution
template<typename DataContainer>
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                const DataContainer& data_container,
                std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
                incoherent_adjoint_distribution,
                const IncoherentAdjointModelType incoherent_adjoint_model,
                const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
                const double max_energy,
                const unsigned endf_subshell )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy <= SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy() );
  testPrecondition( max_energy > SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy() );

  switch( incoherent_adjoint_model )
  {
    case KN_INCOHERENT_ADJOINT_MODEL:
    {
      ThisType::createKleinNishinaDistribution(
                                             adjoint_kn_sampling,
                                             max_energy,
                                             incoherent_adjoint_distribution );
      break;
    }
    case WH_INCOHERENT_ADJOINT_MODEL:
    {
      ThisType::createWallerHartreeDistribution(
                                             data_container,
                                             adjoint_kn_sampling,
                                             max_energy,
                                             incoherent_adjoint_distribution );
      break;
    }
    case IMPULSE_INCOHERENT_ADJOINT_MODEL:
    {
      ThisType::createSubshellDistributionImpl(
                                             data_container,
                                             adjoint_kn_sampling,
                                             endf_subshell,
                                             max_energy,
                                             incoherent_adjoint_distribution );
      break;
                                            
    }
    case DB_IMPULSE_INCOHERENT_ADJOINT_MODEL:
    {
      ThisType::createDopplerBroadenedSubshellDistributionImpl(
                                             data_container,
                                             adjoint_kn_sampling,
                                             endf_subshell,
                                             max_energy,
                                             incoherent_adjoint_distribution );
      break;
    }
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "incoherent adjoint model "
                       << incoherent_adjoint_model <<
                       " cannot be constructed with native data!" );
    }
  }
}

// Create a subshell distribution
template<typename DataContainer>
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
        const DataContainer& data_container,
        std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&
        incoherent_adjoint_distribution,
        const IncoherentAdjointModelType incoherent_adjoint_model,
        const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
        const double max_energy,
        const unsigned endf_subshell )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy <= SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy() );
  testPrecondition( max_energy > SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy() );

  switch( incoherent_adjoint_model )
  {
    case IMPULSE_INCOHERENT_ADJOINT_MODEL:
    {
      ThisType::createSubshellDistributionImpl(
                                             data_container,
                                             adjoint_kn_sampling,
                                             endf_subshell,
                                             max_energy,
                                             incoherent_adjoint_distribution );
      break;
                                            
    }
    case DB_IMPULSE_INCOHERENT_ADJOINT_MODEL:
    {
      ThisType::createDopplerBroadenedSubshellDistributionImpl(
                                             data_container,
                                             adjoint_kn_sampling,
                                             endf_subshell,
                                             max_energy,
                                             incoherent_adjoint_distribution );
      break;
    }
    default:
    {
      if( incoherent_adjoint_model == KN_INCOHERENT_ADJOINT_MODEL ||
          incoherent_adjoint_model == WH_INCOHERENT_ADJOINT_MODEL )
      {
        THROW_EXCEPTION( std::logic_error,
                         "The KN and WH incoherent adjoint models "
                         "are not impulse (subshell) models. The subshell "
                         "distribution cannot be created." );
      }
      else
      {
        THROW_EXCEPTION( std::logic_error,
                         "incoherent adjoint model "
                         << incoherent_adjoint_model <<
                         " cannot be constructed with native data!" );
      }
    }
  }
}

// Create a Waller-Hartree incoherent adjoint distribution
template<typename DataContainer>
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createWallerHartreeDistribution(
                const DataContainer& data_container,
                const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
                const double max_energy,
                std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
                incoherent_adjoint_distribution )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy <= SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy() );
  testPrecondition( max_energy > SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy() );

  // Create the scattering function
  std::shared_ptr<const ScatteringFunction> scattering_function;

  ThisType::createScatteringFunction( data_container, scattering_function );

  // Create the distribution
  incoherent_adjoint_distribution.reset(
             new WHIncoherentAdjointPhotonScatteringDistribution(
                                                       max_energy,
                                                       scattering_function,
                                                       adjoint_kn_sampling ) );
}

// Create a subshell incoherent adjoint distribution
template<typename DataContainer, typename BaseDistributionType>
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistributionImpl(
                     const DataContainer& data_container,
                     const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
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
                      "the requested endf subshell " << endf_subshell <<
                      " is invalid!" );

  // Create the occupation number
  std::shared_ptr<const OccupationNumber> occupation_number;

  ThisType::createOccupationNumber( data_container,
                                    endf_subshell,
                                    occupation_number );

  // Create the distribution
  incoherent_adjoint_distribution.reset(
     new SubshellIncoherentAdjointPhotonScatteringDistribution(
                      max_energy,
                      subshell,
                      data_container.getSubshellOccupancy( endf_subshell ),
                      data_container.getSubshellBindingEnergy( endf_subshell ),
                      occupation_number,
                      adjoint_kn_sampling ) );
}

// Create a Doppler broadened subshell incoherent adjoint distribution
template<typename DataContainer, typename BaseDistributionType>
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDopplerBroadenedSubshellDistributionImpl(
                     const DataContainer& data_container,
                     const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
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
                      "the requested endf subshell " << endf_subshell <<
                      " is invalid!" );

  // Create the occupation number
  std::shared_ptr<const OccupationNumber> occupation_number;

  ThisType::createOccupationNumber( data_container,
                                    endf_subshell,
                                    occupation_number );

  // Create the Compton profile
  std::shared_ptr<const ComptonProfile> compton_profile;

  ThisType::createComptonProfile( data_container,
                                  endf_subshell,
                                  compton_profile );

  // Create the distribution
  incoherent_adjoint_distribution.reset(
     new DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution(
                  max_energy,
                  subshell,
                  data_container.getSubshellOccupancy( endf_subshell ),
                  data_container.getSubshellBindingEnergy( endf_subshell ),
                  occupation_number,
                  compton_profile,
                  adjoint_kn_sampling ) );
}

EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution( const Data::AdjointElectronPhotonRelaxationDataContainer&, std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&, const IncoherentAdjointModelType, const AdjointKleinNishinaSamplingType, const double, const unsigned ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution( const Data::ElectronPhotonRelaxationDataContainer&, std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&, const IncoherentAdjointModelType, const AdjointKleinNishinaSamplingType, const double, const unsigned ) );

EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution( const Data::AdjointElectronPhotonRelaxationDataContainer&, std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&, const IncoherentAdjointModelType, const AdjointKleinNishinaSamplingType, const double, const unsigned ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution( const Data::ElectronPhotonRelaxationDataContainer&, std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&, const IncoherentAdjointModelType, const AdjointKleinNishinaSamplingType, const double, const unsigned ) );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//
