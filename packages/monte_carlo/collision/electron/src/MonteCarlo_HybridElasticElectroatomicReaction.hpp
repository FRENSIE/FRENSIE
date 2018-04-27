//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The hybrid scattering elastic electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HYBRID_ELASTIC_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_HYBRID_ELASTIC_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The hybrid elastic electroatomic reaction class
template<typename InterpPolicy,
         bool processed_cross_section = false>
class HybridElasticElectroatomicReaction : public StandardReactionBaseImpl<ElectroatomicReaction,InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
typedef StandardReactionBaseImpl<ElectroatomicReaction,InterpPolicy,processed_cross_section> 
    BaseType;

public:

  //! Basic Constructor
  HybridElasticElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const double cutoff_angle_cosine,
    const std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
            hybrid_distribution );

  //! Constructor
  HybridElasticElectroatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const double cutoff_angle_cosine,
    const std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
            hybrid_distribution );


  //! Destructor
  ~HybridElasticElectroatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const override;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const override;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const override;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double scattering_angle_cosine ) const override;

  //! Simulate the reaction
  void react( ElectronState& electron,
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

#include "MonteCarlo_HybridElasticElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
