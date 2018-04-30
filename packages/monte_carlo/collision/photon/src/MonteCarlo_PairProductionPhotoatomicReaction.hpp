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
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

namespace MonteCarlo{

//! The pair production photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class PairProductionPhotoatomicReaction : public StandardReactionBaseImpl<PhotoatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<PhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic constructor
  PairProductionPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const bool use_detailed_electron_emission_physics = true );

  //! Constructor
  PairProductionPhotoatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
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

  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const override;

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
  static void detailedInteraction( PhotonState& photon,
                                   ParticleBank& bank );

private:

  // Sample the polar angle of the emitted electron/positron
  static double sampleEmittedPolarAngle( const double energy );

  // Create the secondary energy distribution
  static Utility::FullyTabularBasicBivariateDistribution*
  initializeSecondaryEnergyDistribution();

  // Initialize interaction models
  void initializeInteractionModels(
                           const bool use_detailed_electron_emission_physics );

  // The pair production secondary energy distribution (in a ratio form)
  static std::unique_ptr<const Utility::FullyTabularBasicBivariateDistribution>
  s_secondary_energy_distribution;

  // Check if a detailed model is being used
  bool d_detailed_electron_emission_model;

  // The pair production model
  boost::function<void (PhotonState&,ParticleBank&)> d_interaction_model;

  // pair production secondary energy distribution (in a ratio form)
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> d_secondary_energy_distribution;
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
