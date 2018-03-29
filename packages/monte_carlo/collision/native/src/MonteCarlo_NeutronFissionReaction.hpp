//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronFissionReaction.hpp
//! \author Alex Robinson
//! \brief  The neutron fission reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_FISSION_REACTION_HPP
#define MONTE_CARLO_NEUTRON_FISSION_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearReaction.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_FissionNeutronMultiplicityDistribution.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The neutron fission reaction base class
class NeutronFissionReaction : public NuclearReaction
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The scattering distribution type
  typedef NuclearScatteringDistribution<NeutronState,NeutronState> ScatteringDistribution;

  //! Constructor
  NeutronFissionReaction(
       const NuclearReactionType reaction_type,
       const double temperature,
       const double q_value,
       const unsigned threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const std::shared_ptr<const FissionNeutronMultiplicityDistribution>&
       fission_neutron_multiplicity_distribution,
       const std::shared_ptr<const ScatteringDistribution>&
       prompt_neutron_emission_distribution );

  //! Destructor
  virtual ~NeutronFissionReaction()
  { /* ... */ }

  //! Return the number of neutrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedNeutrons( const double energy ) const override;

  //! Return the number of prompt neutrons emitted from the rxn
  unsigned getNumberOfPromptNeutrons( const double energy ) const;

  //! Return the number of delayed neutrons emitted from the rxn
  unsigned getNumberOfDelayedNeutrons( const double energy ) const;

  //! Return the average number of neutrons emitted from the rxn
  double getAverageNumberOfEmittedNeutrons( const double energy ) const override;

  //! Return the average number of prompt neutrons emitted from the rxn
  double getAverageNumberOfPromptNeutrons( const double energy ) const;

  //! Return the average number of delayed neutrons emitted from the rxn
  double getAverageNumberOfDelayedNeutrons( const double energy ) const;

  //! Simulate the reaction
  virtual void react( NeutronState& neutron, ParticleBank& bank ) const override;

protected:

  //! Implementation of the reaction simulation
  void reactImplementation( NeutronState& neutron,
			    ParticleBank& bank,
			    const bool increment_collision_number ) const;

private:

  // The fission neutron multiplicity distribution (prompt, delayed, total nu)
  std::shared_ptr<const FissionNeutronMultiplicityDistribution>
  d_fission_neutron_multiplicity_distribution;

  // The prompt neutron scattering distribution
  std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >
  d_prompt_neutron_emission_distribution;
};

// Return the average number of neutrons emitted from the reaction
inline double NeutronFissionReaction::getAverageNumberOfEmittedNeutrons(
						    const double energy ) const
{
  return
    d_fission_neutron_multiplicity_distribution->getAverageNumberOfEmittedNeutrons(
								      energy );
}

// Return the average number of prompt neutrons emitted from the rxn
inline double NeutronFissionReaction::getAverageNumberOfPromptNeutrons(
						    const double energy ) const
{
  return
    d_fission_neutron_multiplicity_distribution->getAverageNumberOfPromptNeutrons(
								      energy );
}

// Return the average number of delayed neutrons emitted from the rxn
inline double NeutronFissionReaction::getAverageNumberOfDelayedNeutrons(
						    const double energy ) const
{
  return
    d_fission_neutron_multiplicity_distribution->getAverageNumberOfDelayedNeutrons(
								      energy );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_FISSION_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronFissionReaction.hpp
//---------------------------------------------------------------------------//
