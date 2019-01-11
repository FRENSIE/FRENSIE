//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution ACE factory def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedHybridIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "Data_SubshellType.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create the requested incoherent distribution
void IncoherentPhotonScatteringDistributionACEFactory::createDistribution(
		    const Data::XSSEPRDataExtractor& raw_photoatom_data,
		    std::shared_ptr<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const IncoherentModelType incoherent_model,
		    const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  TEST_FOR_EXCEPTION( kahn_sampling_cutoff_energy <
                      SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy(),
                      std::runtime_error,
                      "The kahn sampling cutoff energy must be greater than "
                      << Utility::toString(SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy()) << " MeV!" );

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
      std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>
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
      std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>
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
      std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>
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
      std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>
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
		       "incoherent model " << incoherent_model <<
		       " cannot be constructed with ACE data!" );
    }
  }
}

// Create a Waller-Hartree incoherent distribution
void IncoherentPhotonScatteringDistributionACEFactory::createWallerHartreeDistribution(
		    const Data::XSSEPRDataExtractor& raw_photoatom_data,
		    std::shared_ptr<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );

  // Create the scattering function
  std::shared_ptr<const ScatteringFunction> scattering_function;

  IncoherentPhotonScatteringDistributionACEFactory::createScatteringFunction(
							 raw_photoatom_data,
							 scattering_function );

  // Create the subshell occupancy array
  std::vector<double> subshell_occupancies( 
                       raw_photoatom_data.extractSubshellOccupancies().begin(),
                       raw_photoatom_data.extractSubshellOccupancies().end() );
  
  // Create the subshell order array
  std::vector<Data::SubshellType> subshell_order;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellOrderArray(
							    raw_photoatom_data,
							    subshell_order );

  incoherent_distribution.reset(
			 new DetailedWHIncoherentPhotonScatteringDistribution(
			   scattering_function,
			   subshell_occupancies,
			   subshell_order,
			   kahn_sampling_cutoff_energy ) );
}

// Create a Doppler broadened hybrid incoherent distribution
void IncoherentPhotonScatteringDistributionACEFactory::createDopplerBroadenedHybridDistribution(
 const Data::XSSEPRDataExtractor& raw_photoatom_data,
 const std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
 doppler_broadened_dist,
 std::shared_ptr<const IncoherentPhotonScatteringDistribution>&
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
	  std::shared_ptr<const ScatteringFunction>& scattering_function )
{
  Utility::ArrayView<const double> jince_block =
    raw_photoatom_data.extractJINCEBlock();

  unsigned scatt_func_size = jince_block.size()/2;

  std::vector<double> recoil_momentum( jince_block( 0, scatt_func_size ) );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<Utility::Units::InverseAngstrom,void> > raw_scattering_function;

  std::vector<double> scattering_function_values(
                             jince_block( scatt_func_size, scatt_func_size ) );
			     

  raw_scattering_function.reset(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseAngstrom,void>(
						recoil_momentum,
						scattering_function_values ) );

  scattering_function.reset(
	       new StandardScatteringFunction<Utility::Units::InverseAngstrom>(
						   raw_scattering_function ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//

