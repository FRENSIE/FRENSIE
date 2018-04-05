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
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The neutron-in, neutron-out scattering reaction class
class NeutronScatteringReaction : public NuclearReaction
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The scattering distribution type
  typedef NuclearScatteringDistribution<NeutronState,NeutronState> ScatteringDistribution;

  //! Constructor
  NeutronScatteringReaction(
       const NuclearReactionType reaction_type,
       const double temperature,
       const double q_value,
       const unsigned multiplicity,
       const unsigned threshold_energy_index,
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const std::shared_ptr<const ScatteringDistribution>& scattering_distribution );

  //! Destructor
  ~NeutronScatteringReaction()
  { /* ... */ }

  //! Return the number of neutrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedNeutrons( const double energy ) const override;

  //! Simulate the reaction
  void react( NeutronState& neutron, ParticleBank& bank ) const override;

private:

  // The neutron multiplicity
  unsigned d_multiplicity;

  // The scattering distribution
  std::shared_ptr<const ScatteringDistribution> d_scattering_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_SCATTERING_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringReaction.hpp
//---------------------------------------------------------------------------//
