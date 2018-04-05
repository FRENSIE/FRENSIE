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
class DecoupledCrossSectionBasedPhotonProductionReaction : public DecoupledPhotonProductionReaction
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The scattering distribution type
  typedef DecoupledPhotonProductionReaction::ScatteringDistribution ScatteringDistribution;

  //! Constructor
  DecoupledCrossSectionBasedPhotonProductionReaction(
       const NuclearReactionType base_reaction_type,
       const unsigned photon_production_id,
       const double temperature,
       const unsigned threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const std::shared_ptr<const ScatteringDistribution>&
       photon_production_distribution,
       const std::shared_ptr<const NuclearReaction>& total_reaction,
       const std::vector<std::shared_ptr<const Utility::OneDDistribution> >&
       total_mt_yield_array );

  //! Return the threshold energy
  double getThresholdEnergy() const override;

  //! Return the base reaction cross section at a given energy
  double getBaseReactionCrossSection( const double energy ) const override;

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const override;

private:

  // The threshold energy index
  unsigned d_threshold_energy_index;

  // The incoming energy grid
  std::shared_ptr<const std::vector<double> > d_incoming_energy_grid;

  // The cross section
  std::shared_ptr<const std::vector<double> > d_cross_section;
};

// Return the threshold energy
inline double
DecoupledCrossSectionBasedPhotonProductionReaction::getThresholdEnergy() const
{
  return (*d_incoming_energy_grid)[d_threshold_energy_index];
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_CROSS_SECTION_BASED_PHOTON_PRODUCTION_REACTION

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.hpp
//---------------------------------------------------------------------------//
