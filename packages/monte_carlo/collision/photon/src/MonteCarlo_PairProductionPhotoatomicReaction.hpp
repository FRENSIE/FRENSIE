//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PairProductionPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The pair production photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_HPP

// Boost Includes
#include <boost/function.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardGenericAtomicReaction.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

namespace MonteCarlo{

//! The pair production photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class PairProductionPhotoatomicReaction : public StandardGenericAtomicReaction<PhotoatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardGenericAtomicReaction<PhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic constructor
  PairProductionPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const unsigned threshold_energy_index,
       const bool use_detailed_electron_emission_physics = true );

  //! Constructor
  PairProductionPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const unsigned threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const bool use_detailed_electron_emission_physics = true );

  //! Destructor
  ~PairProductionPhotoatomicReaction()
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

  //! The basic pair production model
  static void basicInteraction( PhotonState& photon,
                                ParticleBank& bank );

  //! The detailed pair production model
  void detailedInteraction( PhotonState& photon,
                            ParticleBank& bank ) const;

  //! The number of photons emitted from pair production using simple model
  static unsigned basicInteractionPhotonEmission();

  //! The number of photons emitted from pair production using detailed model
  static unsigned detailedInteractionPhotonEmission();

private:

  // Sample the polar angle of the emitted electron/positron
  static double sampleEmittedPolarAngle( const double energy );

  // Initialize interaction models
  void initializeInteractionModels(
                           const bool use_detailed_electron_emission_physics );

  // Create the secondary energy distribution
  void initializeSecondaryEnergyDistribution();

  // The pair production model
  boost::function<void (PhotonState&,ParticleBank&)> d_interaction_model;

  // The number of photons emitted from the interaction (model dependent)
  boost::function<unsigned (void)> d_interaction_model_emission;

  // pair production secondary energy distribution (in a ratio form)
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> d_secondary_energy_distribution;

  // The photon energy grid
  static std::vector<double> s_photon_energy_grid;

  // The ratios of the available kinetic energy given to the positron/electron
  static std::vector< std::vector<double> > s_outgoing_energy_ratio;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_PairProductionPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PairProductionPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
