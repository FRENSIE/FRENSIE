//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The hybrid scattering elastic electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HYBRID_ELASTIC_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_HYBRID_ELASTIC_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The hybrid elastic electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class HybridElasticElectroatomicReaction : public StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Basic Constructor
  HybridElasticElectroatomicReaction(
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cutoff_cross_section,
	  const unsigned cutoff_threshold_energy_index,
	  const Teuchos::ArrayRCP<const double>& moment_preserving_cross_section,
	  const unsigned moment_preserving_threshold_energy_index,
      const double cutoff_angle_cosine,
      const std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
            hybrid_distribution );

  //! Constructor
  HybridElasticElectroatomicReaction(
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cutoff_cross_section,
	  const unsigned cutoff_threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
	  const Teuchos::ArrayRCP<const double>& moment_preserving_cross_section,
	  const unsigned moment_preserving_threshold_energy_index,
      const double cutoff_angle_cosine,
      const std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
            hybrid_distribution );


  //! Destructor
  ~HybridElasticElectroatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( ElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the cross section at the given energy (efficient)
  double getCrossSection( const double energy,
                          const unsigned bin_index ) const;

  //! Return the cutoff cross section at the given energy
  double getCutoffCrossSection( const double energy ) const;

  //! Return the cutoff cross section at the given energy (efficient)
  double getCutoffCrossSection( const double energy,
                                const unsigned bin_index ) const;

  //! Return the screened Rutherford cross section at the given energy
  double getMomentPreservingCrossSection( const double energy ) const;

  //! Return the screened Rutherford cross section at the given energy (efficient)
  double getMomentPreservingCrossSection( const double energy,
                                            const unsigned bin_index ) const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the cutoff threshold energy
  double getCutoffThresholdEnergy() const;

  //! Return the screened Rutherford threshold energy
  double getMomentPreservingThresholdEnergy() const;

private:

  // The hybrid elastic scattering distribution
  std::shared_ptr<const HybridElasticElectronScatteringDistribution>
    d_hybrid_distribution;

  // The cutoff cross section values evaluated on the incoming energy grid
  Teuchos::ArrayRCP<const double> d_cutoff_cross_section;

  // The screened rutherford cross section values evaluated on the incoming energy grid
  Teuchos::ArrayRCP<const double> d_moment_preserving_cross_section;

  // The screened rutherford threshold energy index
  unsigned d_cutoff_threshold_energy_index;

  // The screened rutherford threshold energy index
  unsigned d_moment_preserving_threshold_energy_index;
 
  // The cutoff angle cosine
  double d_cutoff_angle_cosine;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_HybridElasticElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
