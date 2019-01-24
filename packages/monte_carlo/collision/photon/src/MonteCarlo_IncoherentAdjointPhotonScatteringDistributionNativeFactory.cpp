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
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create the scattering function
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createScatteringFunction(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          std::shared_ptr<const ScatteringFunction>& scattering_function )
{
  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
      new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseCentimeter,void>(
   raw_adjoint_photoatom_data.getWallerHartreeScatteringFunctionMomentumGrid(),
   raw_adjoint_photoatom_data.getWallerHartreeScatteringFunction() ) );

  scattering_function.reset(
             new StandardScatteringFunction<Utility::Units::InverseCentimeter>(
                                                   raw_scattering_function ) );
}

// Create the scattering function
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createScatteringFunction(
               const Data::ElectronPhotonRelaxationDataContainer&
               raw_photoatom_data,
               std::shared_ptr<const ScatteringFunction>& scattering_function )
{
  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
      new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseCentimeter,void>(
   raw_photoatom_data.getWallerHartreeScatteringFunctionMomentumGrid(),
   raw_photoatom_data.getWallerHartreeScatteringFunction() ) );

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
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
     raw_adjoint_photoatom_data.getOccupationNumberMomentumGrid(endf_subshell),
     raw_adjoint_photoatom_data.getOccupationNumber( endf_subshell ) ) );

  occupation_number.reset(
                    new StandardOccupationNumber<Utility::Units::MeCMomentum>(
                                                     raw_occupation_number ) );
}

// Create the occupation number
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createOccupationNumber(
          const Data::ElectronPhotonRelaxationDataContainer&
          raw_photoatom_data,
          const unsigned endf_subshell,
          std::shared_ptr<const OccupationNumber>& occupation_number )
{
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
     raw_photoatom_data.getOccupationNumberMomentumGrid(endf_subshell),
     raw_photoatom_data.getOccupationNumber( endf_subshell ) ) );

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
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum> > raw_compton_profile(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
       raw_adjoint_photoatom_data.getComptonProfileMomentumGrid(endf_subshell),
       raw_adjoint_photoatom_data.getComptonProfile( endf_subshell ) ) );

  compton_profile.reset(
     new StandardComptonProfile<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
                                                       raw_compton_profile ) );
}

// Create the Compton profile
void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createComptonProfile(
          const Data::ElectronPhotonRelaxationDataContainer&
          raw_photoatom_data,
          const unsigned endf_subshell,
          std::shared_ptr<const ComptonProfile>& compton_profile )
{
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum> > raw_compton_profile(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
       raw_photoatom_data.getComptonProfileMomentumGrid(endf_subshell),
       raw_photoatom_data.getComptonProfile( endf_subshell ) ) );

  compton_profile.reset(
     new StandardComptonProfile<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
                                                       raw_compton_profile ) );
}

EXPLICIT_TEMPLATE_FUNCTION_INST( void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution( const Data::AdjointElectronPhotonRelaxationDataContainer&, std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&, const IncoherentAdjointModelType, const AdjointKleinNishinaSamplingType, const double, const unsigned ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution( const Data::ElectronPhotonRelaxationDataContainer&, std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&, const IncoherentAdjointModelType, const AdjointKleinNishinaSamplingType, const double, const unsigned ) );

EXPLICIT_TEMPLATE_FUNCTION_INST( void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution( const Data::AdjointElectronPhotonRelaxationDataContainer&, std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&, const IncoherentAdjointModelType, const AdjointKleinNishinaSamplingType, const double, const unsigned ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( void IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution( const Data::ElectronPhotonRelaxationDataContainer&, std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&, const IncoherentAdjointModelType, const AdjointKleinNishinaSamplingType, const double, const unsigned ) );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistibutionNativeFactory.cpp
//---------------------------------------------------------------------------//
