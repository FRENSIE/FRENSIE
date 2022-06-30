//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclideACEFactory.cpp
//! \author Alex Robinson
//! \brief  The nuclide ace factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclideACEFactory.hpp"
#include "MonteCarlo_NeutronNuclearReactionACEFactory.hpp"
#include "MonteCarlo_DecoupledPhotonProductionReactionACEFactory.hpp"
#include "MonteCarlo_DecoupledPhotonProductionNuclide.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_Vector.hpp"
#include "Utility_LoggingMacros.hpp"

namespace MonteCarlo{

void NuclideACEFactory::createNuclide(
			 const Data::XSSNeutronDataExtractor& raw_nuclide_data,
			 const std::string& nuclide_alias,
			 const unsigned atomic_number,
			 const unsigned atomic_mass_number,
			 const unsigned isomer_number,
			 const double atomic_weight_ratio,
			 const double temperature,
       const SimulationProperties& properties,
			 std::shared_ptr<const Nuclide>& nuclide )
{
  // Extract the common energy grid used for this nuclide
  std::shared_ptr<const std::vector<double> > energy_grid(
             new std::vector<double>( raw_nuclide_data.extractEnergyGrid() ) );

  std::shared_ptr<const Utility::HashBasedGridSearcher<double> > grid_searcher(
         new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                               energy_grid,
                               properties.getNumberOfNeutronHashGridBins() ) );

  if( properties.isUnresolvedResonanceProbabilityTableModeOn() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "NuclideACEFactory",
                                "Unresolved resonance data has been "
                                "requested. This feature is not currently "
                                "supported!" );
  }

  if( properties.getParticleMode() == NEUTRON_PHOTON_MODE ||
      properties.getParticleMode() == NEUTRON_PHOTON_ELECTRON_MODE )
  {
    // Create the photon production reaction factory
    DecoupledPhotonProductionReactionACEFactory
      reaction_factory( nuclide_alias,
                        atomic_weight_ratio,
                        temperature,
                        energy_grid,
                        grid_searcher,
                        properties,
                        raw_nuclide_data );
  
    // Create the standard scattering reactions and the standard absorption
    // reactions
    Nuclide::ConstReactionMap standard_scattering_reactions,
      standard_absorption_reactions;

    NuclideACEFactory::createScatteringReactions(
                                               reaction_factory,
                                               standard_scattering_reactions,
                                               standard_absorption_reactions );
    
    // Create the photon production reactions
    DecoupledPhotonProductionNuclide::ConstPhotonProductionReactionMap
      photon_production_reactions;

    reaction_factory.createPhotonProductionReactions(
                                                 photon_production_reactions );

    nuclide.reset( new DecoupledPhotonProductionNuclide(
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
                                               photon_production_reactions ) );
  }
  else
  {
    // Create the photon production reaction factory
    NeutronNuclearReactionACEFactory
      reaction_factory( nuclide_alias,
                        atomic_weight_ratio,
                        temperature,
                        energy_grid,
                        grid_searcher,
                        properties,
                        raw_nuclide_data );
  
    // Create the standard scattering reactions and the standard absorption
    // reactions
    Nuclide::ConstReactionMap standard_scattering_reactions,
      standard_absorption_reactions;

    NuclideACEFactory::createScatteringReactions(
                                               reaction_factory,
                                               standard_scattering_reactions,
                                               standard_absorption_reactions );
    
    nuclide.reset( new Nuclide( nuclide_alias,
			        atomic_number,
			        atomic_mass_number,
			        isomer_number,
			        atomic_weight_ratio,
			        temperature,
			        energy_grid,
                                grid_searcher,
			        standard_scattering_reactions,
			        standard_absorption_reactions ) );
  }
}

// Create the scattering reactions
void NuclideACEFactory::createScatteringReactions(
                      NeutronNuclearReactionACEFactory& reaction_factory,
                      Nuclide::ConstReactionMap& scattering_reactions,
                      Nuclide::ConstReactionMap& absorption_reactions )
{
  reaction_factory.createScatteringReactions( scattering_reactions );
  reaction_factory.createFissionReactions( scattering_reactions );

  reaction_factory.createAbsorptionReactions( absorption_reactions );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideACEFactory.cpp
//---------------------------------------------------------------------------//
