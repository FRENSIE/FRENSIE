//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The incoherent photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_CoherentScatteringDistribution.hpp"

namespace MonteCarlo{

//! The coherent photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class CoherentPhotoatomicReaction : public StandardReactionBaseImpl<PhotoatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<PhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic Constructor
  CoherentPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const CoherentScatteringDistribution>&
       scattering_distribution );

  //! Constructor
  CoherentPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const std::shared_ptr<const CoherentScatteringDistribution>&
    scattering_distribution );

  //! Destructor
  virtual ~CoherentPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const override;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const override;

  //! Return the reaction type
  PhotoatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  void react( PhotonState& photon,
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

#include "MonteCarlo_CoherentPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
