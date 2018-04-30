//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledElasticAdjointElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The coupled scattering elastic adjoint electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The coupled elastic adjoint electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class CoupledElasticAdjointElectroatomicReaction : public StandardReactionBaseImpl<AdjointElectroatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<AdjointElectroatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  CoupledElasticAdjointElectroatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& cross_section,
      const size_t threshold_energy_index,
      const std::shared_ptr<const CoupledElasticElectronScatteringDistribution>&
            scattering_distribution );

  //! Constructor
  CoupledElasticAdjointElectroatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& cross_section,
      const size_t threshold_energy_index,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      const std::shared_ptr<const CoupledElasticElectronScatteringDistribution>&
            scattering_distribution );


  //! Destructor
  ~CoupledElasticAdjointElectroatomicReaction()
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

  // The coupled elastic scattering distribution
  std::shared_ptr<const CoupledElasticElectronScatteringDistribution>
    d_scattering_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CoupledElasticAdjointElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledElasticAdjointElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
