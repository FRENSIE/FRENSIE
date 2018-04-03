//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TripletProductionPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The triplet production photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION_HPP

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_StandardGenericAtomicReaction.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"

namespace MonteCarlo{

//! The triplet production photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class TripletProductionPhotoatomicReaction : public StandardGenericAtomicReaction<PhotoatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardGenericAtomicReaction<PhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic Constructor
  TripletProductionPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const unsigned threshold_energy_index,
       const bool use_detailed_electron_emission_physics = true );

  //! Constructor
  TripletProductionPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const unsigned threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const bool use_detailed_electron_emission_physics = true );

  //! Destructor
  ~TripletProductionPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const override;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Return the reaction type
  PhotoatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  void react( PhotonState& photon,
	      ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const override;

protected:

  //! The basic triplet production model
  static void basicInteraction( PhotonState& photon,
                                ParticleBank& bank );

  //! The detailed triplet production model
  static void detailedInteraction( PhotonState& photon,
                                   ParticleBank& bank );

  //! The number of photons emitted from triplet prod. using simple model
  static unsigned basicInteractionPhotonEmission();

  //! The number of photons emitted from triplet prod. using detailed model
  static unsigned detailedInteractionPhotonEmission();

private:

  // Initialize interaction models
  void initializeInteractionModels(
                           const bool use_detailed_electron_emission_physics );

  // The triplet production model
  boost::function<void (PhotonState&,ParticleBank&)> d_interaction_model;

  // The number of photons emitted from the interaction (model dependent)
  boost::function<unsigned (void)> d_interaction_model_emission;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_TripletProductionPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TripletProductionPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
