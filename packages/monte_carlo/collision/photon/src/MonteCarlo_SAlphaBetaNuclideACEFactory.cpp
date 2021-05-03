//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SAlphaBetaNuclideACEFactory.cpp
//! \author Eli Moll
//! \brief  The S(a,b) nuclide ace factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclideACEFactory.hpp"
#include "MonteCarlo_NeutronNuclearReactionACEFactory.hpp"
#include "MonteCarlo_SAlphaBetaDecoupledPhotonProductionReactionACEFactory.hpp"
#include "MonteCarlo_DecoupledPhotonProductionNuclide.hpp"
#include "MonteCarlo_SAlphaBetaNuclearReactionACEFactory.hpp"
#include "MonteCarlo_SAlphaBetaNuclideACEFactory.hpp"

namespace MonteCarlo{

SAlphaBetaNuclideACEFactory::SAlphaBetaNuclideACEFactory()
{ /* ... */ }

void SAlphaBetaNuclideACEFactory::createNuclide( 
			 const Data::XSSNeutronDataExtractor& raw_nuclide_data,
			 const std::string& nuclide_alias,
			 const unsigned atomic_number,
			 const unsigned atomic_mass_number,
			 const unsigned isomer_number,
			 const double atomic_weight_ratio,
			 const double temperature,
			 std::shared_ptr<Nuclide>& nuclide,
			 const bool use_unresolved_resonance_data,
			 const bool use_photon_production_data,
			 const std::string& sab_alias,
			 const Data::XSSSabDataExtractor& sab_nuclide_data,
			 const SimulationProperties& properties)
{
  // Extract the common energy grid used for this nuclide
  std::shared_ptr< std::vector< double>> energy_grid;
  energy_grid.reset( new std::vector< double>(raw_nuclide_data.extractEnergyGrid()) );
  
	std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher = std::make_shared<Utility::StandardHashBasedGridSearcher<std::vector<double>,false> >(
						energy_grid,
						properties.getNumberOfAdjointElectronHashGridBins() );

  // Create the nuclear reaction factory
  SAlphaBetaNuclearReactionACEFactory reaction_factory( 
	  					  nuclide_alias,
					      atomic_weight_ratio,
					      temperature,
					      energy_grid,
					      raw_nuclide_data,
					      sab_nuclide_data,
						  grid_searcher,
						  properties );	  
					  
  // Create the standard scattering reactions
  Nuclide::ReactionMap standard_scattering_reactions;
  
  reaction_factory.createScatteringReactions( standard_scattering_reactions );
  reaction_factory.createFissionReactions( standard_scattering_reactions );
  
  // Create the standard absorption reactions
  Nuclide::ReactionMap standard_absorption_reactions;
  
  reaction_factory.createAbsorptionReactions( standard_absorption_reactions );
  
  // Create the S(alpha,beta) reactions
  Nuclide::ReactionMap sab_reactions;
  reaction_factory.createSAlphaBetaReactions( sab_reactions );
  
  // Add the S(alpha,beta) reactions to the scattering reactions
  Nuclide::ReactionMap::const_iterator sab_reaction, sab_reaction_end;
  sab_reaction = sab_reactions.begin();
  sab_reaction_end = sab_reactions.end();
  
  while( sab_reaction != sab_reactions.end() )
  {
    standard_scattering_reactions[sab_reaction->first] = sab_reaction->second;
    ++sab_reaction;
  }
                                                  
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
    SAlphaBetaDecoupledPhotonProductionReactionACEFactory
        photon_production_reaction_factory( nuclide_alias,
											atomic_weight_ratio,
                                           	temperature, 
											energy_grid,
                                           	raw_nuclide_data,
											sab_nuclide_data, 
											grid_searcher, 
											properties);

    // Create the photon production reactions
    DecoupledPhotonProductionNuclide::ConstPhotonProductionReactionMap
        photon_production_reactions;

    photon_production_reaction_factory.createPhotonProductionReactions(
        photon_production_reactions);

    nuclide.reset(new DecoupledPhotonProductionNuclide(
        nuclide_alias, 
		atomic_number, 
		atomic_mass_number, 
		isomer_number,
        atomic_weight_ratio, 
		temperature, 
		energy_grid,
		grid_searcher,
        standard_scattering_reactions, 
		standard_absorption_reactions,
        photon_production_reactions));
  }
  else
  {
    nuclide.reset(new Nuclide( nuclide_alias, 
						       atomic_number, 
							   atomic_mass_number,
                               isomer_number, 
							   atomic_weight_ratio, 
							   temperature,
                               energy_grid,
							   grid_searcher,
							   standard_scattering_reactions,
                               standard_absorption_reactions));
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideACEFactory.cpp
//---------------------------------------------------------------------------//
