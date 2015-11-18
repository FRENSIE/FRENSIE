//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  The photon production reaction with cross section data class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_CROSS_SECTION_BASED_PHOTON_PRODUCTION_REACTION
#define MONTE_CARLO_DECOUPLED_CROSS_SECTION_BASED_PHOTON_PRODUCTION_REACTION

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"

namespace MonteCarlo{

//! The photon production reaction with cross section data (MFTYPE=13)
class DecoupledCrossSectionBasedPhotonProductionReaction : public DecoupledPhotonProductionReaction
{
 
private:

  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;

public:

  // Constructor
  DecoupledCrossSectionBasedPhotonProductionReaction(
		   const NuclearReactionType base_reaction_type,
		   const unsigned photon_production_id,
		   const double temperature,
		   const unsigned threshold_energy_index,
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,PhotonState> >& 
		   photon_production_distribution,
		   const Teuchos::RCP<NuclearReaction>& total_reaction,
		   const Teuchos::Array<std::shared_ptr<Utility::OneDDistribution> >& total_mt_yield_array );

  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the base reaction cross section at a given enery
  double getBaseReactionCrossSection( const double energy ) const;

  //! Return the crosss section at a given energy
  double getCrossSection( const double energy ) const;

private:

  // The threshold energy index
  unsigned d_threshold_energy_index;

  // The incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section
  Teuchos::ArrayRCP<const double> d_cross_section;
};

// Return the threshold energy
inline double 
DecoupledCrossSectionBasedPhotonProductionReaction::getThresholdEnergy() const
{
  return d_incoming_energy_grid[d_threshold_energy_index];
}


} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_CROSS_SECTION_BASED_PHOTON_PRODUCTION_REACTION

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.hpp
//---------------------------------------------------------------------------//
