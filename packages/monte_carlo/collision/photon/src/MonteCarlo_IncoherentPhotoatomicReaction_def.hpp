//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The incoherent photoatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_INCOHERENT_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic constructor
template<typename InterpPolicy, bool processed_cross_section>
IncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::IncoherentPhotoatomicReaction(
              const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
	      const std::shared_ptr<const std::vector<double> >& cross_section,
	      const unsigned threshold_energy_index,
              const std::shared_ptr<const IncoherentPhotonScatteringDistribution>&
	      scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
   d_scattering_distribution( scattering_distribution )
{
  // Make sure the scattering distribution is valid
  testPrecondition( scattering_distribution.get() );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
IncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::IncoherentPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const unsigned threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher>& grid_searcher,
       const std::shared_ptr<const IncoherentPhotonScatteringDistribution>&
       scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
   d_scattering_distribution( scattering_distribution )
{
  // Make sure the scattering function is valid
  testPrecondition( scattering_distribution.get() );
  // Make sure the grid searcher is valid
  testPrecondition( grid_searcher.get() );
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned IncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
/*! \details This does not include electrons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned IncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType IncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return TOTAL_INCOHERENT_PHOTOATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void IncoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
				     PhotonState& photon,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterPhoton(photon, bank, shell_of_interaction);

  photon.incrementCollisionNumber();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
