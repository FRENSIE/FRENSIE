//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CutoffElasticPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The cutoff scattering elastic positron-atomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CUTOFF_ELASTIC_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_CUTOFF_ELASTIC_POSITRONATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The cutoff elastic positron-atomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class CutoffElasticPositronatomicReaction : public StandardReactionBaseImpl<PositronatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<PositronatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  CutoffElasticPositronatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& cross_section,
      const size_t threshold_energy_index,
      const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
      scattering_distribution );

  //! Constructor
  CutoffElasticPositronatomicReaction(
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const size_t threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
    scattering_distribution );


  //! Destructor
  ~CutoffElasticPositronatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const override;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const override;

  //! Return the reaction type
  PositronatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  void react( PositronState& positron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const override;

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const override;

  //! Return the cross section at the given energy (efficient)
  double getCrossSection( const double energy,
                          const size_t bin_index ) const override;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double scattering_angle_cosine ) const override;

private:

  // The cutoff_elastic scattering distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    d_scattering_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CutoffElasticPositronatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_CUTOFF_ELASTIC_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CutoffElasticPositronatomicReaction.hpp
//---------------------------------------------------------------------------//
