//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronScatteringReaction.hpp
//! \author Alex Robinson
//! \brief  The neutron-in, neutron-out scattering reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_SCATTERING_REACTION_HPP
#define MONTE_CARLO_NEUTRON_SCATTERING_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearReaction.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"

namespace MonteCarlo{

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
		   const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> >& 
		   scattering_distribution,
       const double sab_cutoff_energy = 0.0 );

  //! Destructor
  ~NeutronScatteringReaction()
  { /* ... */ }
  
  //! Return the number of neutrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedNeutrons( const double energy ) const;

  //! Simulate the reaction
  void react( NeutronState& neutron, ParticleBank& bank ) const;

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const;

  //! Set the S(a,b) cutoff energy
  void setSABCutoffEnergy( double sab_cutoff_energy );

private:

  // The neutron multiplicity
  unsigned d_multiplicity;

  double d_sab_cutoff_energy;

  // The scattering distribution
  Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> > 
  d_scattering_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_SCATTERING_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringReaction.hpp
//---------------------------------------------------------------------------//
