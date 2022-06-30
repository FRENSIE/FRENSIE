//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  The photon production reaction with cross section data class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_CROSS_SECTION_BASED_PHOTON_PRODUCTION_REACTION
#define MONTE_CARLO_DECOUPLED_CROSS_SECTION_BASED_PHOTON_PRODUCTION_REACTION

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The photon production reaction with cross section data (MFTYPE=13)
class DecoupledCrossSectionBasedPhotonProductionReaction : public StandardReactionBaseImpl<DecoupledPhotonProductionReaction,Utility::LinLin,false>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // The base type
  typedef StandardReactionBaseImpl<DecoupledPhotonProductionReaction,Utility::LinLin,false> BaseType;

public:

  //! The scattering distribution type
  typedef DecoupledPhotonProductionReaction::ScatteringDistribution ScatteringDistribution;

  //! Basic Constructor
  DecoupledCrossSectionBasedPhotonProductionReaction(
       const NuclearReactionType base_reaction_type,
       const unsigned photon_production_id,
       const double temperature,
       const size_t threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const std::shared_ptr<const ScatteringDistribution>&
       photon_production_distribution,
       const std::shared_ptr<NeutronNuclearReaction>& total_reaction,
       const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
       total_mt_yield_array );

  //! Constructor
  DecoupledCrossSectionBasedPhotonProductionReaction(
       const NuclearReactionType base_reaction_type,
       const unsigned photon_production_id,
       const double temperature,
       const size_t threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const std::shared_ptr<const ScatteringDistribution>&
       photon_production_distribution,
       const std::shared_ptr<NeutronNuclearReaction>& total_reaction,
       const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
       total_mt_yield_array );

  //! Return the base reaction cross section at a given energy
  double getReactionCrossSection( const double energy ) const override;

  //! Return the average number of emitted photons
  double getAverageNumberOfEmittedParticles( const double energy ) const final override;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_CROSS_SECTION_BASED_PHOTON_PRODUCTION_REACTION

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.hpp
//---------------------------------------------------------------------------//
