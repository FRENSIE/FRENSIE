//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclideACEFactory.cpp
//! \author Alex Robinson
//! \brief  The nuclide ace factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclideACEFactory.hpp"
#include "MonteCarlo_NuclearReactionACEFactory.hpp"
#include "MonteCarlo_DecoupledPhotonProductionReactionACEFactory.hpp"
#include "MonteCarlo_DecoupledPhotonProductionNuclide.hpp"

namespace MonteCarlo{

void NuclideACEFactory::createNuclide( 
			 const Data::XSSNeutronDataExtractor& raw_nuclide_data,
			 const std::string& nuclide_alias,
			 const unsigned atomic_number,
			 const unsigned atomic_mass_number,
			 const unsigned isomer_number,
			 const double atomic_weight_ratio,
			 const double temperature,
			 Teuchos::RCP<Nuclide>& nuclide,
			 const bool use_unresolved_resonance_data,
			 const bool use_photon_production_data )
{
  // Extract the common energy grid used for this nuclide
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( raw_nuclide_data.extractEnergyGrid() );

  // Create the nuclear reaction factory
  NuclearReactionACEFactory reaction_factory( nuclide_alias,
					      atomic_weight_ratio,
					      temperature,
					      energy_grid.getConst(),
					      raw_nuclide_data );
					  
  // Create the standard scattering reactions
  Nuclide::ReactionMap standard_scattering_reactions;
  
  reaction_factory.createScatteringReactions( standard_scattering_reactions );
  reaction_factory.createFissionReactions( standard_scattering_reactions );
  
  // Create the standard absorption reactions
  Nuclide::ReactionMap standard_absorption_reactions;
  
  reaction_factory.createAbsorptionReactions( standard_absorption_reactions );
                                                  
  if( use_unresolved_resonance_data )
  {
    std::cerr << std::endl
	      << "Warning: Unresolved resonance data has been requested. "
	      << "This feature is not currently supported!"
	      << std::endl;
  }

  if( use_photon_production_data )
  {
    // Create the photon production reaction factory
    DecoupledPhotonProductionReactionACEFactory photon_production_reaction_factory( 
                  nuclide_alias,
					        atomic_weight_ratio,
					        temperature,
					        energy_grid.getConst(),
					        raw_nuclide_data ); 
				        
		// Create the photon production reactions 
		DecoupledPhotonProductionNuclide::PhotonProductionReactionMap
		                                               photon_production_reactions;
		                                               
		photon_production_reaction_factory.createPhotonProductionReactions( 
		                                             photon_production_reactions );
   
    nuclide.reset( new DecoupledPhotonProductionNuclide( nuclide_alias,
			        atomic_number,
			        atomic_mass_number,
			        isomer_number,
			        atomic_weight_ratio,
			        temperature,
			        energy_grid,
			        standard_scattering_reactions,
			        standard_absorption_reactions,
			        photon_production_reactions ) );
  }
  else
  {
    nuclide.reset( new Nuclide( nuclide_alias,
			        atomic_number,
			        atomic_mass_number,
			        isomer_number,
			        atomic_weight_ratio,
			        temperature,
			        energy_grid,
			        standard_scattering_reactions,
			        standard_absorption_reactions ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideACEFactory.cpp
//---------------------------------------------------------------------------//
