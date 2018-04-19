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

  //! The scattering distribution type
  typedef NeutronFissionReaction::ScatteringDistribution ScatteringDistribution;

  //! Basic Constructor
  DetailedNeutronFissionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const std::shared_ptr<const FissionNeutronMultiplicityDistribution>&
       fission_neutron_multiplicity_distribution,
       const std::shared_ptr<const ScatteringDistribution>&
       prompt_neutron_emission_distribution,
       const std::shared_ptr<const ScatteringDistribution>&
       delayed_neutron_emission_distribution );

  //! Constructor
  DetailedNeutronFissionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const std::shared_ptr<const FissionNeutronMultiplicityDistribution>&
       fission_neutron_multiplicity_distribution,
       const std::shared_ptr<const ScatteringDistribution>&
       prompt_neutron_emission_distribution,
       const std::shared_ptr<const ScatteringDistribution>&
       delayed_neutron_emission_distribution );

  //! Destructor
  ~DetailedNeutronFissionReaction()
  { /* ... */ }

  //! Simulate the reaction
  void react( NeutronState& neutron, ParticleBank& bank ) const final override;

private:

  // The delayed neutron scattering distribution
  std::shared_ptr<const ScatteringDistribution>
  d_delayed_neutron_emission_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DETAILED_NEUTRON_FISSION_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedNeutronFissionReaction.hpp
//---------------------------------------------------------------------------//
