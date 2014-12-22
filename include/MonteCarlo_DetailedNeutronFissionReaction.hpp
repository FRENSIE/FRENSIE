//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedNeutronFissionReaction.hpp
//! \author Alex Robinson
//! \brief  The detailed neutron fission reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DETAILED_NEUTRON_FISSION_REACTION_HPP
#define MONTE_CARLO_DETAILED_NEUTRON_FISSION_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NeutronFissionReaction.hpp"

namespace MonteCarlo{

/*! The detailed neutron fission reaction class
 * \details This class adds delayed neutron emission data to the neutron
 * fission reaction base class
 */
class DetailedNeutronFissionReaction : public NeutronFissionReaction
{

public:

  //! Constructor
  DetailedNeutronFissionReaction(
		   const NuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned threshold_energy_index,
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const Teuchos::RCP<FissionNeutronMultiplicityDistribution>&
		   fission_neutron_multiplicity_distribution,
		   const Teuchos::RCP<NeutronScatteringDistribution>&
		   prompt_neutron_emission_distribution,
		   const Teuchos::RCP<NeutronScatteringDistribution>&
		   delayed_neutron_emission_distribution );

  //! Destructor
  ~DetailedNeutronFissionReaction()
  { /* ... */ }

  //! Simulate the reaction
  void react( NeutronState& neutron, ParticleBank& bank ) const;

private:

  // The delayed neutron scattering distribution
  Teuchos::RCP<NeutronScatteringDistribution>
  d_delayed_neutron_emission_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DETAILED_NEUTRON_FISSION_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedNeutronFissionReaction.hpp
//---------------------------------------------------------------------------//
