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
#include "MonteCarlo_StandardNeutronNuclearReaction.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The neutron-in, neutron-out scattering reaction class
class NeutronScatteringReaction : public StandardNeutronNuclearReaction
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The scattering distribution type
  typedef NuclearScatteringDistribution<NeutronState,NeutronState> ScatteringDistribution;

  //! Basic Constructor
  NeutronScatteringReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const unsigned multiplicity,
       const std::shared_ptr<const ScatteringDistribution>&
       scattering_distribution );

  //! Constructor
  NeutronScatteringReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const unsigned multiplicity,
       const std::shared_ptr<const ScatteringDistribution>&
       scattering_distribution );

  //! Destructor
  ~NeutronScatteringReaction()
  { /* ... */ }

  //! Return the number of neutrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedParticles( const double energy ) const override;

  //! Simulate the reaction
  void react( NeutronState& neutron, ParticleBank& bank ) const override;

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const;

  //! Set the S(a,b) cutoff energy
  void setSABCutoffEnergy( double sab_cutoff_energy );

private:

  // The neutron multiplicity
  unsigned d_multiplicity;

  double d_sab_cutoff_energy;

  // The scattering distribution
  std::shared_ptr<const ScatteringDistribution> d_scattering_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_SCATTERING_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringReaction.hpp
//---------------------------------------------------------------------------//
