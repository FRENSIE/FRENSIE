//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NeutronScatteringReaction.hpp
//! \author Alex Robinson
//! \brief  The neutron-in, neutron-out scattering reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NEUTRON_SCATTERING_REACTION_HPP
#define FACEMC_NEUTRON_SCATTERING_REACTION_HPP

// FRENSIE Includes
#include "Facemc_NuclearReaction.hpp"
#include "Facemc_NeutronScatteringDistribution.hpp"

namespace Facemc{

//! The neutron-in, neutron-out scattering reaction class
class NeutronScatteringReaction : public NuclearReaction
{

private:
  
  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  NeutronScatteringReaction( 
		   const NuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned multiplicity,
		   const unsigned threshold_energy_index,
	           const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::RCP<NeutronScatteringDistribution>& 
		   scattering_distribution );

  //! Destructor
  ~NeutronScatteringReaction()
  { /* ... */ }
  
  //! Return the number of neutrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedNeutrons( const double energy ) const;

  //! Simulate the reaction
  void react( NeutronState& neutron, ParticleBank& bank ) const;
		   

private:

  // The number of secondary particles (of the same type as primary) released
  unsigned d_multiplicity;

  // The scattering distribution
  Teuchos::RCP<NeutronScatteringDistribution> d_scattering_distribution;
};

} // end Facemc namespace

#endif // end FACEMC_NEUTRON_SCATTERING_REACTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringReaction.hpp
//---------------------------------------------------------------------------//
