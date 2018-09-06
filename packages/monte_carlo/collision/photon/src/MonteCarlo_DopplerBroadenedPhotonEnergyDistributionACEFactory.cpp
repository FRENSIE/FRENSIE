//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  The Doppler broadened photon energy distribution ACE factory def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ComptonProfilePolicy.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_InverseAtomicMomentumUnit.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

//! Create a coupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution(
		  const Data::XSSEPRDataExtractor& raw_photoatom_data,
		  std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
		  doppler_broadened_dist,
		  const bool use_full_profile )
{
  // Create subshell binding energies array
  std::vector<double> subshell_binding_energies(
                   raw_photoatom_data.extractSubshellBindingEnergies().begin(),
                   raw_photoatom_data.extractSubshellBindingEnergies().end() );

  // Create the occupancies array
  std::vector<double> subshell_occupancies(
                       raw_photoatom_data.extractSubshellOccupancies().begin(),
                       raw_photoatom_data.extractSubshellOccupancies().end() );
  
  // Create the subshell order array
  std::vector<Data::SubshellType> subshell_order;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellOrderArray(
							    raw_photoatom_data,
							    subshell_order );

  // Create the Compton profile subshell converter
  std::shared_ptr<const ComptonProfileSubshellConverter> converter;

  ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );

  // Create the compton profile distributions
  CompleteDopplerBroadenedPhotonEnergyDistribution::ComptonProfileArray
    compton_profiles;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileArray(
							    raw_photoatom_data,
							    use_full_profile,
							    compton_profiles );

  if( use_full_profile )
  {
    doppler_broadened_dist.reset(
      new CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy>(
                                                     subshell_binding_energies,
                                                     subshell_occupancies,
                                                     subshell_order,
                                                     converter,
                                                     compton_profiles ) );
  }
  // ACE Compton profiles are halved and then doubled so they remain normalized
  else
  {
    doppler_broadened_dist.reset(
      new CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy>(
                                                     subshell_binding_energies,
                                                     subshell_occupancies,
                                                     subshell_order,
                                                     converter,
                                                     compton_profiles ) );
  }
}

// Create a coupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution(
	  const Data::XSSEPRDataExtractor& raw_photoatom_data,
	  std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
	  doppler_broadened_dist,
	  const bool use_full_profile )
{
  std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution> dist;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution(
							    raw_photoatom_data,
							    dist,
							    use_full_profile );

  doppler_broadened_dist =
    std::dynamic_pointer_cast<const CompleteDopplerBroadenedPhotonEnergyDistribution>( dist );
}

// Create a decoupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution(
		  const Data::XSSEPRDataExtractor& raw_photoatom_data,
		  std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
		  doppler_broadened_dist,
		  const bool use_full_profile )
{
  // Create the occupancies array
  std::vector<double> subshell_occupancies( 
                       raw_photoatom_data.extractSubshellOccupancies().begin(),
                       raw_photoatom_data.extractSubshellOccupancies().end() );

  // Create the old subshell binding energy array
  std::vector<double> old_subshell_binding_energies(
                                raw_photoatom_data.extractLBEPSBlock().begin(),
                                raw_photoatom_data.extractLBEPSBlock().end() );

  // Create the old subshell occupancy array
  std::vector<double> old_subshell_occupancies(
                                raw_photoatom_data.extractLNEPSBlock().begin(),
                                raw_photoatom_data.extractLNEPSBlock().end() );
  
  // Create the subshell order array
  std::vector<Data::SubshellType> subshell_order;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellOrderArray(
							    raw_photoatom_data,
							    subshell_order );

  // Create the Compton profile subshell converter
  std::shared_ptr<const ComptonProfileSubshellConverter> converter;

  ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );

  // Create the compton profile distributions
  CompleteDopplerBroadenedPhotonEnergyDistribution::ComptonProfileArray
    compton_profiles;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileArray(
							    raw_photoatom_data,
							    use_full_profile,
							    compton_profiles );

  if( use_full_profile )
  {
    doppler_broadened_dist.reset(
       new DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy>(
                           subshell_occupancies,
			   subshell_order,
                           old_subshell_binding_energies,
                           old_subshell_occupancies,
                           converter,
			   compton_profiles ) );
  }
  // ACE Compton profiles are halved and then doubled so they remain normalized
  else
  {
    doppler_broadened_dist.reset(
      new DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy>(
                           subshell_occupancies,
			   subshell_order,
                           old_subshell_binding_energies,
                           old_subshell_occupancies,
                           converter,
			   compton_profiles ) );
  }
}

// Create a decoupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution(
	  const Data::XSSEPRDataExtractor& raw_photoatom_data,
	  std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
	  doppler_broadened_dist,
	  const bool use_full_profile )
{
  std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution> dist;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution(
							    raw_photoatom_data,
							    dist,
							    use_full_profile );

  doppler_broadened_dist =
    std::dynamic_pointer_cast<const CompleteDopplerBroadenedPhotonEnergyDistribution>( dist );
}

// Create a subshell Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellDistribution(
		  const Data::XSSEPRDataExtractor& raw_photoatom_data,
		  const unsigned endf_subshell,
		  std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
		  doppler_broadened_dist,
		  const bool use_full_profile )
{
  // Convert the endf subshell to a subshell type
  Data::SubshellType subshell =
    Data::convertENDFDesignatorToSubshellEnum( endf_subshell );

  TEST_FOR_EXCEPTION( subshell == Data::INVALID_SUBSHELL,
		      std::logic_error,
		      "the requested endf subshell " <<
		      endf_subshell << " is invalid! " );

  // Create the Compton profile subshell converter
  std::shared_ptr<const ComptonProfileSubshellConverter> converter;

  ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );

  // Get the Compton profile index corresponding to the ENDF subshell
  unsigned compton_index;

  try{
    compton_index = converter->convertSubshellToIndex( subshell );
  }
  EXCEPTION_CATCH_RETHROW( std::logic_error,
			   "the requested endf subshell "
			   << endf_subshell << " is invalid!" );

  // Extract the Compton profile
  Utility::ArrayView<const double> lswd_block =
    raw_photoatom_data.extractLSWDBlock();

  Utility::ArrayView<const double> swd_block =
    raw_photoatom_data.extractSWDBlock();

  unsigned subshell_index = lswd_block[compton_index];

  unsigned num_momentum_points = swd_block[subshell_index];

  Utility::ArrayView<const double> raw_half_momentum_grid =
    swd_block( subshell_index + 1, num_momentum_points );
  
  std::vector<double> half_momentum_grid( raw_half_momentum_grid.begin(),
                                          raw_half_momentum_grid.end() );

  Utility::ArrayView<const double> raw_half_profile =
    swd_block( subshell_index + 1 + num_momentum_points,
               num_momentum_points );

  std::vector<double> half_profile( raw_half_profile.begin(),
                                    raw_half_profile.end() );
  
  std::shared_ptr<const ComptonProfile> compton_profile;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfile(
							    half_momentum_grid,
							    half_profile,
							    use_full_profile,
							    compton_profile );

  if( use_full_profile )
  {
    doppler_broadened_dist.reset(
        new StandardSubshellDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy>(
			 subshell,
			 raw_photoatom_data.extractLNEPSBlock()[compton_index],
		         raw_photoatom_data.extractLBEPSBlock()[compton_index],
			 compton_profile ) );
  }
  else
  {
    doppler_broadened_dist.reset(
        new StandardSubshellDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy>(
			 subshell,
			 raw_photoatom_data.extractLNEPSBlock()[compton_index],
		         raw_photoatom_data.extractLBEPSBlock()[compton_index],
			 compton_profile ) );
  }
}

// Create a subshell Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellDistribution(
	  const Data::XSSEPRDataExtractor& raw_photoatom_data,
	  const unsigned endf_subshell,
	  std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution>&
	  doppler_broadened_dist,
	  const bool use_full_profile )
{
  std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution> dist;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellDistribution(
							    raw_photoatom_data,
							    endf_subshell,
							    dist,
							    use_full_profile );

  doppler_broadened_dist =
    std::dynamic_pointer_cast<const SubshellDopplerBroadenedPhotonEnergyDistribution>( dist );
}

// Create the subshell order array
void
DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellOrderArray(
			   const Data::XSSEPRDataExtractor& raw_photoatom_data,
			   std::vector<Data::SubshellType>& subshell_order )
{
  Utility::ArrayView<const double> subshell_endf_designators =
    raw_photoatom_data.extractSubshellENDFDesignators();

  subshell_order.resize( subshell_endf_designators.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] =Data::convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
  }
}

// Create the Compton profile distribution
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileArray(
	 const Data::XSSEPRDataExtractor& raw_photoatom_data,
	 const bool use_full_profile,
	 CompleteDopplerBroadenedPhotonEnergyDistribution::ComptonProfileArray&
         compton_profiles )
{
  Utility::ArrayView<const double> lswd_block =
    raw_photoatom_data.extractLSWDBlock();

  Utility::ArrayView<const double> swd_block =
    raw_photoatom_data.extractSWDBlock();

  compton_profiles.resize( lswd_block.size() );

  for( unsigned subshell = 0; subshell < lswd_block.size(); ++subshell )
  {
    unsigned subshell_index = lswd_block[subshell];

    unsigned num_momentum_points = swd_block[subshell_index];

    Utility::ArrayView<const double> raw_half_momentum_grid =
      swd_block( subshell_index + 1, num_momentum_points );

    std::vector<double> half_momentum_grid( raw_half_momentum_grid.begin(),
                                            raw_half_momentum_grid.end() );

    Utility::ArrayView<const double> raw_half_profile =
      swd_block( subshell_index + 1 + num_momentum_points,
                 num_momentum_points );
    
    std::vector<double> half_profile( raw_half_profile.begin(),
                                      raw_half_profile.end() );
    
    DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfile(
						  half_momentum_grid,
						  half_profile,
						  use_full_profile,
						  compton_profiles[subshell] );
  }
}

// Create the Compton profile distribution
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfile(
		       std::vector<double>& raw_half_momentum_grid,
                       std::vector<double>& raw_half_profile,
                       const bool use_full_profile,
                       std::shared_ptr<const ComptonProfile>& compton_profile )
{
  // Make sure the half grid and profile are valid
  testPrecondition( raw_half_momentum_grid.size() > 1 );
  testPrecondition( raw_half_profile.size() ==
		    raw_half_momentum_grid.size() );

  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> > raw_compton_profile;

  if( use_full_profile )
  {
    std::vector<double> full_momentum_grid, full_profile;

    MonteCarlo::createFullProfileFromHalfProfile( raw_half_momentum_grid.begin(),
						  raw_half_momentum_grid.end(),
						  raw_half_profile.begin(),
						  raw_half_profile.end(),
						  full_momentum_grid,
						  full_profile,
                                                  true );

    // Ignore interp parameter (always assume lin-lin interpolation)
    // The Compton profile momentum grid in the ACE tables use atomic units.
    // The Compton profiles in the ACE tables use inverse atomic units.
    raw_compton_profile.reset(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>(
                                                        full_momentum_grid,
                                                        full_profile ) );
  }
  else
  {
    // Ignore interp parameter (always assume lin-lin interpolation)
    raw_compton_profile.reset(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum>(
                                                        raw_half_momentum_grid,
							raw_half_profile ) );
  }

  compton_profile.reset(
                   new StandardComptonProfile<Utility::Units::AtomicMomentum>(
                                                       raw_compton_profile ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
