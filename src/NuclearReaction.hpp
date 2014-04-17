//---------------------------------------------------------------------------//
//!
//! \file   NuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The nuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NUCLEAR_REACTION_HPP
#define NUCLEAR_REACTION_HPP

// FACEMC Includes
#include "NuclearReactionType.hpp"

namespace FACEMC{

//! The nuclear reaction base class
class NuclearReaction
{

public:

  //! Constructor
  NuclearReaction( 
	 const NuclearReactionType reaction_type,
	 const double Q_value,
	 const unsigned multiplicity,
	 const unsigned threshold_energy_index,
	 const Teuchos::ArrayView<const double>& incoming_energy_grid,
	 const Teuchos::ArrayView<const double>& cross_section,
	 const Teuchos::RCP<ScatteringDistribution>& scattering_distribution );
		   

private:

  // The nuclear reaction type
  NuclearReactionType d_reaction_type;

  // The Q value for the reaction
  double d_Q_value;

  // The number of secondary particles (of the same type as primary) released
  unsigned d_multiplicity;

  // The energy grid index of the reaction threshold
  unsigned d_threshold_energy_index;

  // The incoming energy grid
  Teuchos::ArrayView<double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming energy grid
  Teuchos::Array<double> d_cross_section;

  // The scattering distribution
  Teuchos::RCP<ScatteringDistribution> d_scattering_distribution;
};

} // end FACEMC namespace

#endif // end NUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end NuclearReaction.hpp
//---------------------------------------------------------------------------//
