//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EnergyDependentNeutronMultiplicityReaction.hpp
//! \author Alex Robinson
//! \brief  The energy dependent neutron multiplicity reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ENERGY_DEPENDENT_NEUTRON_MULTIPLICITY_REACTION_HPP
#define MONTE_CARLO_ENERGY_DEPENDENT_NEUTRON_MULTIPLICITY_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearReaction.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"

namespace MonteCarlo{

/*! The energy dependent neutron multiplicity reaction class
 * \details This class may function as an absorption reaction and a 
 * scattering reaction depending on the neutron multiplicity at the given
 * energy (e.g. N__N_ANYTHING reaction in O16)
 */
class EnergyDependentNeutronMultiplicityReaction : public NuclearReaction
{
  
private:

  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;
  
public:

  //! Constructor
  EnergyDependentNeutronMultiplicityReaction(
	      const NuclearReactionType reaction_type,
	      const double temperature,
	      const double q_value,
	      const Teuchos::ArrayView<const double>& multiplicity_energy_grid,
	      const Teuchos::ArrayView<const double>& multiplicity,
	      const unsigned threshold_energy_index,
	      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	      const Teuchos::ArrayRCP<const double>& cross_section,
	      const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> >& 
	      scattering_distribution );

  //! Destructor
  ~EnergyDependentNeutronMultiplicityReaction()
  { /* ... */ }

  //! Return the number of neutrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedNeutrons( const double energy ) const;

  //! Return the average number of neutrons emitted from the rxn
  double getAverageNumberOfEmittedNeutrons( const double energy ) const;

  //! Simulate the reaction
  void react( NeutronState& neutron, ParticleBank& bank ) const;

private:

  // The energy grid of the number of secondary particles (of the same type as 
  // primary) released
  Teuchos::Array<double> d_multiplicity_energy_grid;
  
  // The number of secondary particles (of the same type as primary) released
  Teuchos::Array<double> d_multiplicity;

  // The scattering distribution
  Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> > 
  d_scattering_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ENERGY_DEPENDENT_NEUTRON_MULTIPLICITY_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EnergyDependentNeutronMultiplicityReaction.hpp
//---------------------------------------------------------------------------//
