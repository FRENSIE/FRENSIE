//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CrossSectionBasedPhotonProductionReaction.hpp
//! \author Alex Robinson
//! \brief  The photon production reaction with cross section data class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_CROSS_SECTION_BASED_PHOTON_PRODUCTION_REACTION
#define FACEMC_CROSS_SECTION_BASED_PHOTON_PRODUCTION_REACTION

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_PhotonProductionReaction.hpp"

namespace Facemc{

//! The photon production reaction with cross section data (MFTYPE=13)
class CrossSectionBasedPhotonProductionReaction : public PhotonProductionReaction
{
 
private:

  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;

public:

  // Constructor
  CrossSectionBasedPhotonProductionReaction(
		   const NuclearReactionType base_reaction_type,
		   const unsigned photon_production_id,
		   const double temperature,
		   const unsigned threshold_energy_index,
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::RCP<PhotonProductionDistribution>& 
		   photon_production_distribution );

  //! Return the threshold energy
  double getThesholdEnergy() const;

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
CrossSectionBasedPhotonProductionReaction::getThesholdEnergy() const
{
  return d_incoming_energy_grid[d_threshold_energy_index];
}


} // end Facemc namespace

#endif // end FACEMC_CROSS_SECTION_BASED_PHOTON_PRODUCTION_REACTION

//---------------------------------------------------------------------------//
// end Facemc_CrossSectionBasedPhotonProductionReaction.hpp
//---------------------------------------------------------------------------//
