//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentAdjointPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The coherent adjoint photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_CoherentScatteringDistribution.hpp"

namespace MonteCarlo{

//! The coherent adjoint photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class CoherentAdjointPhotoatomicReaction : public StandardReactionBaseImpl<AdjointPhotoatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<AdjointPhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic Constructor
  CoherentAdjointPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const CoherentScatteringDistribution>&
       scattering_distribution );

  //! Constructor
  CoherentAdjointPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const std::shared_ptr<const CoherentScatteringDistribution>&
    scattering_distribution );

  //! Destructor
  ~CoherentAdjointPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of adjoint photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointPhotons( const double energy ) const override;

  //! Return the number of adjoint electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointElectrons( const double energy ) const override;

  //! Return the number of adjoint positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointPositrons( const double energy ) const override;

  //! Return the reaction type
  AdjointPhotoatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  void react( AdjointPhotonState& adjoint_photon,
	      ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const override;

private:

  // The coherent scattering distribution
  std::shared_ptr<const CoherentScatteringDistribution> d_scattering_distribution;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CoherentAdjointPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentAdjointPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
