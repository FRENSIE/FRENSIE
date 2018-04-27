//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledElasticElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The decoupled scattering elastic electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The decoupled (cutoff and screened Rutherford) elastic electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class DecoupledElasticElectroatomicReaction : public StandardReactionBaseImpl<ElectroatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<ElectroatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  DecoupledElasticElectroatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& total_cross_section,
      const std::shared_ptr<const std::vector<double> >& cutoff_cross_section,
      const size_t threshold_energy_index,
      const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
            tabular_distribution,
      const std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
            analytical_distribution );

  //! Constructor
  DecoupledElasticElectroatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& total_cross_section,
      const std::shared_ptr<const std::vector<double> >& cutoff_cross_section,
      const size_t threshold_energy_index,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
            tabular_distribution,
      const std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
            analytical_distribution );


  //! Destructor
  ~DecoupledElasticElectroatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double scattering_angle_cosine ) const;

  //! Return the sampling ratio at the given energy
  double getSamplingRatio( const double energy ) const;

  //! Simulate the reaction
  void react( ElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

private:

  // The tabular Cutoff distribution
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    d_tabular_distribution;

  // The analytical screened Rutherford distribution
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>
    d_analytical_distribution;

  // The cutoff cross sections
  std::shared_ptr<const std::vector<double> > d_cutoff_cross_section;

  // The processed incoming energy grid
  std::shared_ptr<const std::vector<double> > d_incoming_energy_grid;

  // The threshold energy
  unsigned d_threshold_energy_index;

  // The hash-based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double>> d_grid_searcher;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_DecoupledElasticElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledElasticElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
