//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledYieldBasePhotonProductionReaction.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  The photon production reaction with yield data definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DecoupledYieldBasedPhotonProductionReaction.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
DecoupledYieldBasedPhotonProductionReaction::DecoupledYieldBasedPhotonProductionReaction(
    const NuclearReactionType base_reaction_type,
    const unsigned photon_production_id,
    const double temperature,
    const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
    total_mt_yield_array,
    const std::shared_ptr<const Utility::UnivariateDistribution>& mtp_yield,
    const std::shared_ptr<NeutronNuclearReaction>& base_reaction,
    const std::shared_ptr<const ScatteringDistribution>&
    photon_production_distribution,
    const std::shared_ptr<NeutronNuclearReaction>& total_reaction )
  : DecoupledPhotonProductionReaction( base_reaction_type,
                                       photon_production_id,
                                       temperature,
                                       photon_production_distribution,
                                       total_reaction,
                                       total_mt_yield_array ),
    d_mtp_yield( mtp_yield ),
    d_base_reaction( base_reaction )
{
  // Make sure the base reaction is valid
  testPrecondition( base_reaction.get() != NULL );
  testPrecondition( base_reaction->getReactionType() == base_reaction_type );
}

// Return the base nuclear reaction type
NuclearReactionType DecoupledYieldBasedPhotonProductionReaction::getReactionType() const
{
  return d_base_reaction->getReactionType();
}

// Test if two Atomic reactions share the same energy grid
/*! \details Since the base reaction stores the energy grid, it will be used
 * to conduct the test.
 */
bool DecoupledYieldBasedPhotonProductionReaction::isEnergyGridShared(
                                         const Reaction& other_reaction ) const
{
  return d_base_reaction->isEnergyGridShared( other_reaction );
}

// Test if the energy falls within the energy grid
bool DecoupledYieldBasedPhotonProductionReaction::isEnergyWithinEnergyGrid(
                                                    const double energy ) const
{
  return d_base_reaction->isEnergyWithinEnergyGrid( energy );
}

// Return the threshold energy
double DecoupledYieldBasedPhotonProductionReaction::getThresholdEnergy() const
{
  return d_mtp_yield->getLowerBoundOfIndepVar();
}

// Return the max energy
double DecoupledYieldBasedPhotonProductionReaction::getMaxEnergy() const
{
  return d_mtp_yield->getUpperBoundOfIndepVar();
}

// Return the base reaction cross section at a given energy
/*! \details The photon production cross section is the base cross section
 * multiplied by the yield.
 */
double DecoupledYieldBasedPhotonProductionReaction::getReactionCrossSection(
						    const double energy ) const
{
  return d_base_reaction->getCrossSection( energy );
}

// Return the cross section at a given energy
/*! \details The photon production cross section is the base cross section
 * multiplied by the yield.
 */
double DecoupledYieldBasedPhotonProductionReaction::getCrossSection(
						    const double energy ) const
{
  // Evaluate the yield at a given energy
  double yield = d_mtp_yield->evaluate( energy );

  // Evaluate the cross section at a given energy
  return d_base_reaction->getCrossSection( energy )*yield;
}

// Return the cross section at a given energy
/*! \details The photon production cross section is the base cross section
 * multiplied by the yield.
 */
double DecoupledYieldBasedPhotonProductionReaction::getCrossSection(
                                                 const double energy,
                                                 const size_t bin_index ) const
{
  // Evaluate the yield at a given energy
  double yield = d_mtp_yield->evaluate( energy );

  // Evaluate the cross section at a given energy
  return d_base_reaction->getCrossSection( energy, bin_index )*yield;
}

// Return the average number of emitted photons
double DecoupledYieldBasedPhotonProductionReaction::getAverageNumberOfEmittedParticles(
                                                    const double energy ) const
{
  return d_mtp_yield->evaluate( energy );
}

// Return the head of the energy grid
/*! \details We don't have access to the energy grid head - it's stored in the 
 * base reaction.
 */
const double* DecoupledYieldBasedPhotonProductionReaction::getEnergyGridHead() const
{
  return NULL;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledYieldBasedPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
