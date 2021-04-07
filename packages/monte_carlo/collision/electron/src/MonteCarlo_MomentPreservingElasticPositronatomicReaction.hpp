//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MomentPreservingElasticPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The single scattering elastic positron-atomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MOMENT_ELASTIC_PRESERVING_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_MOMENT_ELASTIC_PRESERVING_POSITRONATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The moment preserving elastic positron-atomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class MomentPreservingElasticPositronatomicReaction : public StandardReactionBaseImpl<PositronatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<PositronatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! BasicConstructor
  MomentPreservingElasticPositronatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        discrete_scattering_distribution );

  //! Constructor
  MomentPreservingElasticPositronatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        discrete_scattering_distribution );

  //! Destructor
  ~MomentPreservingElasticPositronatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const override;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const override;

  //! Return the reaction type
  PositronatomicReactionType getReactionType() const override;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double scattering_angle_cosine ) const override;

  //! Simulate the reaction
  void react( PositronState& positron,
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

#include "MonteCarlo_MomentPreservingElasticPositronatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_MOMENT_PRESERVING_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MomentPreservingElasticPositronatomicReaction.hpp
//---------------------------------------------------------------------------//
