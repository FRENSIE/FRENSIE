//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticAdjointElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The hybrid scattering elastic adjoint electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The hybrid elastic adjoint electroatomic reaction class
template<typename InterpPolicy,
         bool processed_cross_section = false>
class HybridElasticAdjointElectroatomicReaction : public StandardReactionBaseImpl<AdjointElectroatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<AdjointElectroatomicReaction,InterpPolicy,processed_cross_section> 
    BaseType;

public:

  //! Basic Constructor
  HybridElasticAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const double cutoff_angle_cosine,
    const std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
            hybrid_distribution );

  //! Constructor
  HybridElasticAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const double cutoff_angle_cosine,
    const std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
            hybrid_distribution );


  //! Destructor
  ~HybridElasticAdjointElectroatomicReaction()
  { /* ... */ }

  //! Return the number of adjoint photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointPhotons( const double energy ) const override;

  //! Return the number of adjoint electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointElectrons( const double energy ) const override;

  //! Return the number of adjoint positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointPositrons( const double energy ) const override;

  //! Return the reaction type
  AdjointElectroatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  void react( AdjointElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const override;

private:

  // The hybrid elastic scattering distribution
  std::shared_ptr<const HybridElasticElectronScatteringDistribution>
    d_hybrid_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_HybridElasticAdjointElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticAdjointElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
