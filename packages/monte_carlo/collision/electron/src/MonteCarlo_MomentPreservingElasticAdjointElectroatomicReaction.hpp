//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The single scattering elastic adjoint electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MOMENT_ELASTIC_PRESERVING_ADJOINT_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_MOMENT_ELASTIC_PRESERVING_ADJOINT_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The moment preserving elastic adjoint electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class MomentPreservingElasticAdjointElectroatomicReaction : public StandardReactionBaseImpl<AdjointElectroatomicReaction,InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
typedef StandardReactionBaseImpl<AdjointElectroatomicReaction,InterpPolicy,processed_cross_section> 
    BaseType;

public:

  //! BasicConstructor
  MomentPreservingElasticAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        discrete_scattering_distribution );

  //! Constructor
  MomentPreservingElasticAdjointElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        discrete_scattering_distribution );

  //! Destructor
  ~MomentPreservingElasticAdjointElectroatomicReaction()
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


  // The moment preserving elastic scattering distribution
  std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>
    d_discrete_scattering_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_MOMENT_PRESERVING_ADJOINT_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
