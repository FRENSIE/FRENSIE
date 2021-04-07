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
#include "MonteCarlo_StandardNeutronNuclearReaction.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

/*! The energy dependent neutron multiplicity reaction class
 * \details This class may function as an absorption reaction and a
 * scattering reaction depending on the neutron multiplicity at the given
 * energy (e.g. N__N_ANYTHING reaction in O16)
 */
class EnergyDependentNeutronMultiplicityReaction : public StandardNeutronNuclearReaction
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The scattering distribution type
  typedef NuclearScatteringDistribution<NeutronState,NeutronState> ScatteringDistribution;

  //! Basic Constructor
  EnergyDependentNeutronMultiplicityReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const std::shared_ptr<const ScatteringDistribution>&
       scattering_distribution,
       const Utility::ArrayView<const double>& multiplicity_energy_grid,
       const Utility::ArrayView<const double>& multiplicity );

  //! Constructor
  EnergyDependentNeutronMultiplicityReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature,
       const std::shared_ptr<const ScatteringDistribution>&
       scattering_distribution,
       const Utility::ArrayView<const double>& multiplicity_energy_grid,
       const Utility::ArrayView<const double>& multiplicity );

  //! Destructor
  ~EnergyDependentNeutronMultiplicityReaction()
  { /* ... */ }

  //! Return the number of neutrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedParticles( const double energy ) const override;

  //! Return the average number of neutrons emitted from the rxn
  double getAverageNumberOfEmittedParticles( const double energy ) const override;

  //! Simulate the reaction
  void react( NeutronState& neutron, ParticleBank& bank ) const override;

private:

  // The energy grid of the number of secondary particles (of the same type as
  // primary) released
  std::vector<double> d_multiplicity_energy_grid;

  // The number of secondary particles (of the same type as primary) released
  std::vector<double> d_multiplicity;

  // The scattering distribution
  std::shared_ptr<const ScatteringDistribution> d_scattering_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ENERGY_DEPENDENT_NEUTRON_MULTIPLICITY_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EnergyDependentNeutronMultiplicityReaction.hpp
//---------------------------------------------------------------------------//
