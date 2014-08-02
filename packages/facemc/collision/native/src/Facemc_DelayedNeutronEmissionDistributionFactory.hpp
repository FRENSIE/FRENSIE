//---------------------------------------------------------------------------//
//!
//! \file   Facemc_DelayedNeutronEmissionDistributionFactory.hpp
//! \author Alex Robinson
//! \brief  Delayed neutron emission distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_DELAYED_NEUTRON_EMISSION_DISTRIBUTION_FACTORY_HPP
#define FACEMC_DELAYED_NEUTRON_EMISSION_DISTRIBUTION_FACTORY_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_NeutronScatteringDistribution.hpp"

namespace Facemc{


//! The delayed neutron emission distribution factory class
class DelayedNeutronEmissionDistributionFactory
{

public:

  //! Constructor
  DelayedNeutronEmissionDistributionFactory(
		          const std::string& table_name,
			  const double atomic_weight_ratio,
			  const Teuchos::ArrayView<const double>& bdd_block,
			  const Teuchos::ArrayView<const double>& dnedl_block,
		          const Teuchos::ArrayView<const double>& dned_block );

  //! Destructor
  ~DelayedNeutronEmissionDistributionFactory()
  { /* ... */ }

  //! Create the delayed neutron emission distribution
  void createEmissionDistribution(
	     Teuchos::RCP<NeutronScatteringDistribution>& distribution ) const;

private:

  // Initialize basic delayed neutron data
  void initializeBasicDelayedNeutronData( 
			   const std::string& table_name,
			   const Teuchos::ArrayView<const double>& bdd_block );

  // Initialize the emission distributions
  void initializeEmissionDistributions(
			  const std::string& table_name,
			  const double atomic_weight_ratio,
			  const Teuchos::ArrayView<const double>& dnedl_block,
		          const Teuchos::ArrayView<const double>& dned_block );

  // The atomic weight ratio
  double d_atomic_weight_ratio;

  // The precursor group decay constants
  Teuchos::Array<double> d_precursor_group_decay_consts;

  // The precursor group probability distributions
  Teuchos::Array<Teuchos::RCP<Utility::OneDDistribution> >
  d_precursor_group_prob_distributions;

  // The precursor group emission distributions
  Teuchos::Array<Teuchos::RCP<NeutronScatteringDistribution> >
  d_precursor_group_emission_distributions;
};

} // end Facemc namespace

#endif // end FACEMC_DELAYED_NEUTRON_EMISSION_DISTRIBUTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Facemc_DelayedNeutronEmissionDistributionFactory.hpp
//---------------------------------------------------------------------------//
