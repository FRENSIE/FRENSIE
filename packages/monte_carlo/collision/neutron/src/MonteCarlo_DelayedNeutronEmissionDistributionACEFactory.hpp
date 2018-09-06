//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  Delayed neutron emission distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DELAYED_NEUTRON_EMISSION_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_DELAYED_NEUTRON_EMISSION_DISTRIBUTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_ArrayView.hpp"

namespace MonteCarlo{


//! The delayed neutron emission distribution factory class
class DelayedNeutronEmissionDistributionACEFactory
{

public:

  //! Constructor
  DelayedNeutronEmissionDistributionACEFactory(
		          const std::string& table_name,
			  const double atomic_weight_ratio,
			  const Utility::ArrayView<const double>& bdd_block,
			  const Utility::ArrayView<const double>& dnedl_block,
		          const Utility::ArrayView<const double>& dned_block );

  //! Destructor
  ~DelayedNeutronEmissionDistributionACEFactory()
  { /* ... */ }

  //! Create the delayed neutron emission distribution
  void createEmissionDistribution(
       std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >&
       distribution ) const;

protected:

  //! Return the precursor group decay constants
  const std::vector<double>& getPrecursorGroupDecayConsts() const;

  //! Return the precursor group probability distributions
  const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
  getPrecursorGroupProbDists() const;

  //! Return the precursor group emission distributions
  const std::vector<std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> > >&
  getPrecursorGroupEmissionDists() const;

private:

  // Initialize basic delayed neutron data
  void initializeBasicDelayedNeutronData(
			   const std::string& table_name,
			   const Utility::ArrayView<const double>& bdd_block );

  // Initialize the emission distributions
  void initializeEmissionDistributions(
			  const std::string& table_name,
			  const double atomic_weight_ratio,
			  const Utility::ArrayView<const double>& dnedl_block,
		          const Utility::ArrayView<const double>& dned_block );

  // The atomic weight ratio
  double d_atomic_weight_ratio;

  // The precursor group decay constants
  std::vector<double> d_precursor_group_decay_consts;

  // The precursor group probability distributions
  std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >
  d_precursor_group_prob_distributions;

  // The precursor group emission distributions
  std::vector<std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> > >
  d_precursor_group_emission_distributions;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DELAYED_NEUTRON_EMISSION_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
