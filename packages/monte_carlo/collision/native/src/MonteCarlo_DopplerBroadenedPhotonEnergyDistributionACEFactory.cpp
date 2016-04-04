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
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_InverseAtomicMomentumUnit.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Create a coupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution(
		  const Data::XSSEPRDataExtractor& raw_photoatom_data,
		  std::shared_ptr<const DopplerBroadenedPhotonEnergyDistribution>&
		  doppler_broadened_dist,
		  const bool use_full_profile )
{
  // Create the subshell order array
  Teuchos::Array<SubshellType> subshell_order;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellOrderArray(
							    raw_photoatom_data,
							    subshell_order );

  // Create the Compton profile subshell converter
  std::shared_ptr<ComptonProfileSubshellConverter> converter;
  
  ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );
  
  // Create the compton profile distributions
  DopplerBroadenedPhotonEnergyDistribution::ElectronMomentumDistArray
    compton_profiles;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDistArray(
							    raw_photoatom_data,
							    use_full_profile,
							    compton_profiles );

  if( use_full_profile )
  {
    doppler_broadened_dist.reset( 
      new CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy>( 
			   raw_photoatom_data.extractSubshellBindingEnergies(),
			   raw_photoatom_data.extractSubshellOccupancies(),
			   subshell_order,
			   converter,
			   compton_profiles ) );
  }
  // ACE Compton profiles are halved and then doubled so they remain normalized
  else
  {
    doppler_broadened_dist.reset( 
      new CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy>( 
			   raw_photoatom_data.extractSubshellBindingEnergies(),
			   raw_photoatom_data.extractSubshellOccupancies(),
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
  // Create the subshell order array
  Teuchos::Array<SubshellType> subshell_order;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellOrderArray(
							    raw_photoatom_data,
							    subshell_order );

  // Create the Compton profile subshell converter
  std::shared_ptr<ComptonProfileSubshellConverter> converter;
  
  ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );

  // Create the compton profile distributions
  DopplerBroadenedPhotonEnergyDistribution::ElectronMomentumDistArray
    compton_profiles;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDistArray(
							    raw_photoatom_data,
							    use_full_profile,
							    compton_profiles );
  
  if( use_full_profile )
  {
    doppler_broadened_dist.reset(
       new DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy>( 
			   raw_photoatom_data.extractSubshellOccupancies(),
			   subshell_order,
			   raw_photoatom_data.extractLBEPSBlock(),
			   raw_photoatom_data.extractLNEPSBlock(),
                           converter,
			   compton_profiles ) );
  }
  // ACE Compton profiles are halved and then doubled so they remain normalized
  else
  {
    doppler_broadened_dist.reset( 
      new DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy>( 
			   raw_photoatom_data.extractSubshellOccupancies(),
			   subshell_order,
			   raw_photoatom_data.extractLBEPSBlock(),
			   raw_photoatom_data.extractLNEPSBlock(),
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
  SubshellType subshell = convertENDFDesignatorToSubshellEnum( endf_subshell );
  
  TEST_FOR_EXCEPTION( subshell == INVALID_SUBSHELL,
		      std::logic_error,
		      "Error: the requested endf subshell " << 
		      endf_subshell << " is invalid! " );

  // Create the Compton profile subshell converter
  std::shared_ptr<ComptonProfileSubshellConverter> converter;
  
  ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );

  // Get the Compton profile index corresponding to the ENDF subshell
  unsigned compton_index;
  
  try{
    compton_index = converter->convertSubshellToIndex( subshell );
  }
  EXCEPTION_CATCH_RETHROW( std::logic_error,
			   "Error: the requested endf subshell " 
			   << endf_subshell << " is invalid!" );

  // Extract the Compton profile
  Teuchos::ArrayView<const double> lswd_block = 
    raw_photoatom_data.extractLSWDBlock();
  
  Teuchos::ArrayView<const double> swd_block = 
    raw_photoatom_data.extractSWDBlock(); 

  unsigned subshell_index = lswd_block[compton_index]; 
    
  unsigned num_momentum_points = swd_block[subshell_index];
    
  Teuchos::Array<double> half_momentum_grid( 
			swd_block( subshell_index + 1, num_momentum_points ) );

  Teuchos::Array<double> half_profile(
                           swd_block( subshell_index + 1 + num_momentum_points,
				      num_momentum_points ) );

  std::shared_ptr<const ComptonProfile> compton_profile;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDist(
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
			   Teuchos::Array<SubshellType>& subshell_order )
{
  Teuchos::ArrayView<const double> subshell_endf_designators = 
    raw_photoatom_data.extractSubshellENDFDesignators();
  
  subshell_order.resize( subshell_endf_designators.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
  }
}

// Create the Compton profile distribution
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDistArray(
	 const Data::XSSEPRDataExtractor& raw_photoatom_data,
	 const bool use_full_profile,
	 DopplerBroadenedPhotonEnergyDistribution::ElectronMomentumDistArray&
         compton_profiles )
{
  Teuchos::ArrayView<const double> lswd_block = 
    raw_photoatom_data.extractLSWDBlock();
  
  Teuchos::ArrayView<const double> swd_block = 
    raw_photoatom_data.extractSWDBlock(); 

  compton_profiles.resize( lswd_block.size() );
  
  for( unsigned subshell = 0; subshell < lswd_block.size(); ++subshell )
  {
    unsigned subshell_index = lswd_block[subshell]; 
    
    unsigned num_momentum_points = swd_block[subshell_index];
    
    Teuchos::Array<double> half_momentum_grid( 
			swd_block( subshell_index + 1, num_momentum_points ) );

    Teuchos::Array<double> half_profile(
                           swd_block( subshell_index + 1 + num_momentum_points,
				      num_momentum_points ) );

    DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDist(
						  half_momentum_grid,
						  half_profile,
						  use_full_profile,
						  compton_profiles[subshell] );
  }
}

// Create the Compton profile distribution
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDist(
		       Teuchos::Array<double>& raw_half_momentum_grid,
                       Teuchos::Array<double>& raw_half_profile,
                       const bool use_full_profile,
                       std::shared_ptr<const ComptonProfile>& compton_profile )
{
  // Make sure the half grid and profile are valid
  testPrecondition( raw_half_momentum_grid.size() > 1 );
  testPrecondition( raw_half_profile.size() ==
		    raw_half_momentum_grid.size() );
  
  std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::AtomicMomentum,Utility::Units::InverseAtomicMomentum> > raw_compton_profile;

  if( use_full_profile )
  {
    Teuchos::Array<double> full_momentum_grid, full_profile;
    
    MonteCarlo::createFullProfileFromHalfProfile( raw_half_momentum_grid.begin(),
						  raw_half_momentum_grid.end(),
						  raw_half_profile.begin(),
						  raw_half_profile.end(),
						  full_momentum_grid,
						  full_profile,
                                                  true );
    
    // Ignore interp parameter (always assume lin-lin inerpolation)
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
