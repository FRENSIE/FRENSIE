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
#include "MonteCarlo_StandardNeutronNuclearReaction.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_FissionNeutronMultiplicityDistribution.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The neutron fission reaction base class
class NeutronFissionReaction : public StandardNeutronNuclearReaction
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The scattering distribution type
  typedef NuclearScatteringDistribution<NeutronState,NeutronState> ScatteringDistribution;

  //! Basic Constructor
  NeutronFissionReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const std::shared_ptr<const FissionNeutronMultiplicityDistribution>&
       fission_neutron_multiplicity_distribution,
       const std::shared_ptr<const ScatteringDistribution>&
       prompt_neutron_emission_distribution );

  //! Constructor
  NeutronFissionReaction(
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
       prompt_neutron_emission_distribution );

  //! Destructor
  ~NeutronFissionReaction()
  { /* ... */ }

  //! Return the number of neutrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedParticles( const double energy ) const override;

  //! Return the number of prompt neutrons emitted from the rxn
  unsigned getNumberOfPromptParticles( const double energy ) const;

  //! Return the number of delayed neutrons emitted from the rxn
  unsigned getNumberOfDelayedParticles( const double energy ) const;

  //! Return the average number of neutrons emitted from the rxn
  double getAverageNumberOfEmittedParticles( const double energy ) const override;

  //! Return the average number of prompt neutrons emitted from the rxn
  double getAverageNumberOfPromptParticles( const double energy ) const;

  //! Return the average number of delayed neutrons emitted from the rxn
  double getAverageNumberOfDelayedParticles( const double energy ) const;

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
  std::shared_ptr<const ScatteringDistribution>
  d_prompt_neutron_emission_distribution;
};

// Return the average number of neutrons emitted from the reaction
inline double NeutronFissionReaction::getAverageNumberOfEmittedParticles(
						    const double energy ) const
{
  return
    d_fission_neutron_multiplicity_distribution->getAverageNumberOfEmittedNeutrons(
								      energy );
}

// Return the average number of prompt neutrons emitted from the rxn
inline double NeutronFissionReaction::getAverageNumberOfPromptParticles(
						    const double energy ) const
{
  return
    d_fission_neutron_multiplicity_distribution->getAverageNumberOfPromptNeutrons(
								      energy );
}

// Return the average number of delayed neutrons emitted from the rxn
inline double NeutronFissionReaction::getAverageNumberOfDelayedParticles(
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
