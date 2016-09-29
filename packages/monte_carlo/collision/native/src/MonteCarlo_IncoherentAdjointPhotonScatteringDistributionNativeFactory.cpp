//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution native
//!         factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create an incoherent adjoint distribution
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
          incoherent_adjoint_distribution,
          const IncoherentAdjointModelType incoherent_adjoint_model,
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
      ThisType::createKleinNishinaDistribution(incoherent_adjoint_distribution,
                                               max_energy );
      break;
    }
    case WH_INCOHERENT_ADJOINT_MODEL:
    {
      ThisType::createWallerHartreeDistribution(
                                             raw_adjoint_photoatom_data,
                                             max_energy,
                                             incoherent_adjoint_distribution );
      break;
    }
    case IMPULSE_INCOHERENT_ADJOINT_MODEL:
    {
      ThisType::createSubshellDistribution( raw_adjoint_photoatom_data,
                                            endf_subshell,
                                            max_energy,
                                            incoherent_adjoint_distribution );
      break;
                                            
    }
    case DB_IMPULSE_INCOHERENT_ADJOINT_MODEL:
    {
      ThisType::createDopplerBroadenedSubshellDistribution(
                                             raw_adjoint_photoatom_data,
                                             endf_subshell,
                                             max_energy,
                                             incoherent_adjoint_distribution );
      break;
    }
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Error: incoherent adjoint model "
                       << incoherent_adjoint_model <<
                       " cannot be constructed with native data!" );
    }
  }
}

// Create a subshell distribution
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_photoatom_data,
        std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&
        incoherent_adjoint_distribution,
        const IncoherentAdjointModelType incoherent_adjoint_model,
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
      ThisType::createSubshellDistribution( raw_adjoint_photoatom_data,
                                            endf_subshell,
                                            max_energy,
                                            incoherent_adjoint_distribution );
      break;
                                            
    }
    case DB_IMPULSE_INCOHERENT_ADJOINT_MODEL:
    {
      ThisType::createDopplerBroadenedSubshellDistribution(
                                             raw_adjoint_photoatom_data,
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
                         "Error: The KN and WH incoherent adjoint models "
                         "are not impulse (subshell) models. The subshell "
                         "distribution cannot be created." );
      }
      else
      {
        THROW_EXCEPTION( std::logic_error,
                         "Error: incoherent adjoint model "
                         << incoherent_adjoint_model <<
                         " cannot be constructed with native data!" );
      }
    }
  }
}

// Create a Waller-Hartree incoherent adjoint distribution
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createWallerHartreeDistribution(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          const double max_energy,
          std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
          incoherent_adjoint_distribution )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy <= SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy() );
  testPrecondition( max_energy > SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy() );

  // Create the scattering function
  std::shared_ptr<const ScatteringFunction> scattering_function;

  ThisType::createScatteringFunction(
                             raw_adjoint_photoatom_data, scattering_function );

  // Create the distribution
  incoherent_adjoint_distribution.reset(
                          new WHIncoherentAdjointPhotonScatteringDistribution(
                                                       max_energy,
                                                       scattering_function ) );
}

// Create the scattering function
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createScatteringFunction(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          std::shared_ptr<const ScatteringFunction>& scattering_function )
{
  std::shared_ptr<Utility::UnitAwareOneDDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
      new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseCentimeter,void>(
   raw_adjoint_photoatom_data.getWallerHartreeScatteringFunctionMomentumGrid(),
   raw_adjoint_photoatom_data.getWallerHartreeScatteringFunction() ) );

  scattering_function.reset(
             new StandardScatteringFunction<Utility::Units::InverseCentimeter>(
                                                   raw_scattering_function ) );
}

// Create the occupation number
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createOccupationNumber(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          const unsigned endf_subshell,
          std::shared_ptr<const OccupationNumber>& occupation_number )
{
  std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
     raw_adjoint_photoatom_data.getOccupationNumberMomentumGrid(endf_subshell),
     raw_adjoint_photoatom_data.getOccupationNumber( endf_subshell ) ) );

  occupation_number.reset(
                    new StandardOccupationNumber<Utility::Units::MeCMomentum>(
                                                     raw_occupation_number ) );
}

// Create the Compton profile
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createComptonProfile(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          const unsigned endf_subshell,
          std::shared_ptr<const ComptonProfile>& compton_profile )
{
  std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum> > raw_compton_profile(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
       raw_adjoint_photoatom_data.getComptonProfileMomentumGrid(endf_subshell),
       raw_adjoint_photoatom_data.getComptonProfile( endf_subshell ) ) );

  compton_profile.reset(
     new StandardComptonProfile<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
                                                       raw_compton_profile ) );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistibutionNativeFactory.cpp
//---------------------------------------------------------------------------//
