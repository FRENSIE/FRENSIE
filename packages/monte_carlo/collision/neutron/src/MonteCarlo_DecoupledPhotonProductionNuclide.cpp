//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledPhotonProductionNuclide.cpp
//! \author Eli Moll
//! \brief  The decoupled photon production nuclide class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>
#include <sstream>

#include <iomanip>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionNuclide.hpp"
#include "MonteCarlo_NeutronAbsorptionReaction.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
DecoupledPhotonProductionNuclide::DecoupledPhotonProductionNuclide(
          const std::string& name,
          const unsigned atomic_number,
          const unsigned atomic_mass_number,
          const unsigned isomer_number,
          const double atomic_weight_ratio,
          const double temperature,
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const ConstReactionMap& standard_scattering_reactions,
          const ConstReactionMap& standard_absorption_reactions,
          const ConstPhotonProductionReactionMap& photon_production_reactions )
  : Nuclide( name,
             atomic_number,
             atomic_mass_number,
             isomer_number,
             atomic_weight_ratio,
             temperature,
             energy_grid,
             grid_searcher,
             standard_scattering_reactions,
             standard_absorption_reactions )
{
  // Place the photon production reactions into the member data
  ConstPhotonProductionReactionMap::const_iterator reaction_type_pointer, end_reaction_type_pointer;

  reaction_type_pointer = photon_production_reactions.begin();
  end_reaction_type_pointer = photon_production_reactions.end();

  while( reaction_type_pointer != end_reaction_type_pointer )
  {
    d_photon_production_reactions.insert( *reaction_type_pointer );

    ++reaction_type_pointer;
  }
}

// Get the photon production reaction cross section
double DecoupledPhotonProductionNuclide::getPhotonProductionCrossSection(
                                                     const double energy,
                                                     const unsigned reaction )
{
  return d_photon_production_reactions[reaction]->getCrossSection( energy );
}

// Collide with a neutron
void DecoupledPhotonProductionNuclide::collideAnalogue(
                                                     NeutronState& neutron,
                                                     ParticleBank& bank ) const
{
  // Sample photon production stochastically before the neutron's state changes
  this->samplePhotonProductionReaction( neutron, bank );

  // Call the base class implementation for the neutron
  Nuclide::collideAnalogue( neutron, bank );
}

// Collide with a neutron and survival bias
void DecoupledPhotonProductionNuclide::collideSurvivalBias(
                                                      NeutronState& neutron,
                                                      ParticleBank& bank) const
{
  // Sample photon production stochastically before the neutron's state changes
  this->samplePhotonProductionReaction( neutron, bank );
  
  // Call the base class implementation for the neutron
  Nuclide::collideSurvivalBias( neutron, bank );
}

// Sample a decoupled photon production reaction
void DecoupledPhotonProductionNuclide::samplePhotonProductionReaction(
                                                   const NeutronState& neutron,
                                                   ParticleBank& bank ) const
{
  double total_cross_section =
    this->getTotalPhotonProductionCrossSection( neutron.getEnergy() );

  double scaled_random_number = total_cross_section*
    Utility::RandomNumberGenerator::getRandomNumber<double>();
  
  double partial_cross_section = 0.0;

  ConstPhotonProductionReactionMap::const_iterator nuclear_reaction, nuclear_reaction_end;

  nuclear_reaction = d_photon_production_reactions.begin();
  nuclear_reaction_end = d_photon_production_reactions.end();

  while( nuclear_reaction != nuclear_reaction_end )
  {
    partial_cross_section +=
      nuclear_reaction->second->getCrossSection( neutron.getEnergy() );

    if( scaled_random_number < partial_cross_section )
      break;

    ++nuclear_reaction;
  }

  // Make sure a reaction was selected
  testPostcondition( nuclear_reaction != nuclear_reaction_end );

  // Undergo the reaction selected
  nuclear_reaction->second->react( neutron, bank, total_cross_section );
}

// Get total photon production cross section
double DecoupledPhotonProductionNuclide::getTotalPhotonProductionCrossSection(
                                                   const double energy ) const
{
  // Loop over all photon production reactions to get total cross section
  ConstPhotonProductionReactionMap::const_iterator reaction_type_pointer, end_reaction_type_pointer;

  reaction_type_pointer = d_photon_production_reactions.begin();
  end_reaction_type_pointer = d_photon_production_reactions.end();

  double total_cross_section = 0.0;

  while( reaction_type_pointer != end_reaction_type_pointer )
  {
    total_cross_section +=
                      reaction_type_pointer->second->getCrossSection( energy );

    ++reaction_type_pointer;
  }

  return total_cross_section;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Nuclide.cpp
//---------------------------------------------------------------------------//
